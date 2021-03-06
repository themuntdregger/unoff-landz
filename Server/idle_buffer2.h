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


#ifndef IDLE_BUFFER2_H_INCLUDED
#define IDLE_BUFFER2_H_INCLUDED

#include <stdlib.h> //support size_t data type

#ifdef __cplusplus
extern "C" {
#endif

void push_idle_buffer2(int actor_node, int process_type, const unsigned char *packet, size_t packet_len);


void push_sql_command(const char *fmt, ...);


void process_idle_buffer2();


void push_command(int actor_node, int process_type, char *char_name, int guild_id);


#ifdef __cplusplus
}
#endif

enum{//database buffer processing types
    IDLE_BUFFER_PROCESS_SQL,
    IDLE_BUFFER_PROCESS_HASH_DETAILS,
    IDLE_BUFFER_PROCESS_CHECK_NEWCHAR,
    IDLE_BUFFER_PROCESS_ADD_NEWCHAR,
    IDLE_BUFFER_PROCESS_LOGIN,
    IDLE_BUFFER_PROCESS_LIST_GUILD_BY_RANK,
    IDLE_BUFFER_PROCESS_LIST_GUILD_BY_TIME,
    IDLE_BUFFER_PROCESS_GUILD_DETAILS,
    IDLE_BUFFER_PROCESS_UPDATE_INVENTORY
};

#endif // IDLE_BUFFER2_H_INCLUDED
