#include "database_functions.h"

#include <sqlite3.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// DB Upgrade helper functions
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


static bool fexist(const char *dbname) {
    FILE *fp = fopen(dbname,"r");
    if(!fp)
        return false;
    fclose(fp);
    return true;
}
static int fcopy(const char *dbname,const char *newdbname) {
    FILE *fsrc;
    FILE *ftgt;
    char buf[1024];

    fsrc = fopen(dbname,"r");
    if(!fsrc) {
        return -1;
    }
    ftgt = fopen(newdbname,"w");
    if(!ftgt) {
        return -1;
    }
    size_t sz;
    while((sz=fread(buf,1,1024,fsrc))==1024) {
        if(sz!=fwrite(buf,1,sz,ftgt)) {
            goto ERROR;
        }
        if(ferror(fsrc)||ferror(ftgt)) {
            goto ERROR;
        }
    }
    if(sz>0 && (sz!=fwrite(buf,1,sz,ftgt))) {
        goto ERROR;
    }
    return 0;
ERROR:
    fclose(fsrc);
    fclose(ftgt);
    return -1;
}

static char *create_backup_name(const char *dbname,int ver) {
    char buf[4096];
    snprintf(buf,sizeof(buf),"ver_%d_of_%s",ver,dbname);
    char *res = (char *)malloc(strlen(buf));
    strncpy(res,buf,strlen(buf));
    return res;
}
static int create_backup(const char *dbname,int ver) {
    char *bak_fname;
    bak_fname = create_backup_name(dbname,ver);
    if(-1==fcopy(dbname,bak_fname))
        return -1;
    return 0;
}
static int callback(void *unused, int argc, char **argv, char **azColName){

    (void)unused; // suppress warning
    for(int i=0; i<argc; i++){
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}
static int set_db_version(sqlite3 *db,int new_version) {
    char *err_msg = NULL;
    int rc = sqlite3_exec(db,"UPDATE GAME_DATA_TABLE SET db_version = 1 WHERE true",callback,0,&err_msg);
    if( rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return -1;
    }
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Upgrade functions go here
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


static int upgrade_v0_to_v1(const char *dbname) {
    sqlite3 *db;
    int rc;
    char *err_msg = NULL;

    if(-1==create_backup(dbname,0))
        return -1;

    rc = sqlite3_open(dbname, &db);

    if( rc !=SQLITE_OK ) {
        return -1;
    }
    rc = sqlite3_exec(db,"ALTER TABLE GAME_DATA_TABLE ADD COLUMN db_version int",callback,0,&err_msg);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return -1;
    }
    set_db_version(db,1);
    return 0;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Array of upgrade procedures with their associated db versions
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef int (*upgrade_function)(const char *dbname);

struct upgrade_array_entry {
    uint32_t from_version;
    uint32_t to_version;
    upgrade_function fn;
};

struct upgrade_array_entry entries[] = {
    { 0, 1, upgrade_v0_to_v1},
    { 0, 0, NULL}
};


static const struct upgrade_array_entry *find_upgrade_entry(uint32_t old_version) {
    int idx=0;
    while(entries[idx].fn!=NULL) {
        if(entries[idx].from_version==old_version)
            return &entries[idx];
        ++idx;
    }
    return NULL;
}

extern int current_database_version(const char *dbaname);
int upgrade_database(const char *dbname) {

    int old_version;
    int new_version;
    if(!fexist(dbname)) {
        return -1;
    }
    old_version = current_database_version(dbname);
    new_version = CURRENT_DB_VERSION;

    while(old_version!=new_version) {
        const struct upgrade_array_entry *entry = find_upgrade_entry(old_version);
        if(!entry)
            return -1;
        printf("DB version update %d to %d:",entry->from_version,entry->to_version);
        if(0==entry->fn(dbname)) {
            old_version = entry->to_version; // version upgrade successful
            printf("OK\n");
        }
        else {
            printf("FAILED\n");
            return -1;
        }
    }
    return 0;
}