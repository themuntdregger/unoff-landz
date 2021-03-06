/******************************************************************************************************************
	Copyright 2014, 2015, 2016 UnoffLandz

	This file is part of unoff_server_4.

	unoff_server_4 is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	unoff_server_4 is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with unoff_server_4.  If not, see <http://www.gnu.org/licenses/>.
*******************************************************************************************************************/

#ifndef GUILD_H_INCLUDED
#define GUILD_H_INCLUDED

#include <time.h>// support for time_t data type
#include <stdbool.h> // support for bool data type

#include "clients.h" //support for MAX_CHAR_NAME_LEN

#define MAX_GUILDS 10
#define MAX_GUILD_APPLICANTS 10
#define GUILD_OPERATORS 0 //defines the guild id for the Operators guild
#define GUILD_TAG_LENGTH 5
#define MAX_GUILD_MEMBERS 100

#define GUILD_FILE "guilds.lst"

enum{//guild status

    GUILD_ACTIVE,
    GUILD_CLOSED
};

enum{// guild permissions

    PERMISSION_1=1, //player
    PERMISSION_2=2, //developer
    PERMISSION_3=3 //operator
};

enum{// order in which list of guild members is displayed

    GUILD_ORDER_RANK, //list by char rank
    GUILD_ORDER_TIME //list by date char joined guild
};

struct guild_node_type {

    char guild_name[80];
    char guild_tag[GUILD_TAG_LENGTH];
    char guild_description[1024];
    int guild_tag_colour;
    time_t date_guild_created;
    int permission_level;
    int status;

    struct {

        char char_name[MAX_CHAR_NAME_LEN];
        time_t application_date;
    }applicant[MAX_GUILD_APPLICANTS];
};


struct guild_list_type {

    struct guild_node_type guild[MAX_GUILDS];
};
extern struct guild_list_type guilds;


//structs to carry list of guild members (used in #list_guild command)
struct guild_member_type{

    char character_name[80];
    int date_joined_guild;
    int guild_rank;
};

struct guild_member_list_type{

    int guild_member_count;
    struct guild_member_type guild_member[MAX_GUILD_MEMBERS];

};
extern struct guild_member_list_type guild_member_list;


/** RESULT   : creates a guild

    RETURNS  : void

    PURPOSE  : used by function hash_create_guild

    NOTES    :
**/
void create_guild(int actor_node, char *guild_name, char *guild_tag, int permission_level);


/** RESULT   : application from a char for membership of a guild

    RETURNS  : void

    PURPOSE  : used by function hash_apply_guild

    NOTES    :
**/
void apply_guild(int actor_node, char *guild_tag);


/** RESULT   : appoints a char to a guild based on char name and guild tag

    RETURNS  : void

    PURPOSE  : used by function hash_appoint_guild

    NOTES    : This function does the same as join_guild except it accepts strings rather
               that id's. This is in order to facilitate #appoint_guild command.

               This function also bounds checks the input to establish that both the guild
               and the chat exist, and that the char is not already in a guild.
**/
void join_guild(int actor_node, char *char_name, char *guild_tag);


/** RESULT   : removes a char from a guild

    RETURNS  : void

    PURPOSE  : used by function hash_ops_kick_guild_member and #kick_guild_member

    NOTES    :
**/
void kick_guild_member(int actor_node, char *guild_tag, char *char_name);


/** RESULT   : changes a chars guild rank

    RETURNS  : void

    PURPOSE  : used by function hash_change_guild_rank and hash_ops_change_guild_rank

    NOTES    :
**/
void change_guild_rank(int actor_node, char *char_name, char *guild_tag, int guild_rank);


/** RESULT   : changes a guild permission level

    RETURNS  : void

    PURPOSE  : used by function hash_change_guild_permission

    NOTES    : OPS only
**/
void change_guild_permission(int actor_node, char *guild_tag, int permission_level);


/** RESULT   : finds the guild id from the guild tag

    RETURNS  : guild id

    PURPOSE  : used by function apply_guild and hash_guild_details

    NOTES    :
**/
int get_guild_id(char *guild_tag);

/*****************************************************************************************************
***                                   C FUNCTIONS CALLED FROM C++ MODULES                          ***
******************************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/** RESULT   : sends a list of guild members to a character

    RETURNS  : void

    PURPOSE  : used by function hash_change_guild_permission

    NOTES    : used by function process_idle_buffer
**/
void list_guild_members(int actor_node, int order);


/** RESULT   : sends details of a guild

    RETURNS  : void

    PURPOSE  : used by function hash_guild_details

    NOTES    :
**/
void send_guild_details(int actor_node, int guild_id);


#ifdef __cplusplus
}
#endif

#endif // GUILD_H_INCLUDED
