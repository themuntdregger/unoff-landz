/******************************************************************************************************************
    Copyright 2014, 2015 UnoffLandz

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

#ifndef LOG_IN_H_INCLUDED
#define LOG_IN_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

/** RESULT  : processes a log in request from the client

    RETURNS : void

    PURPOSE : reduce need for code in client_protocol_handler.c

    NOTES   :
*/
void process_log_in(int connection, const unsigned char *packet);

#ifdef __cplusplus
}
#endif



#endif // LOG_IN_H_INCLUDED
