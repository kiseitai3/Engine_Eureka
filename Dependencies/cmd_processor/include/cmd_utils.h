/*
    Copyright (C) 2015 Luis M. Santos
    Contact: luismigue1234@hotmail.com

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with This program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef CMD_UTILS_H_INCLUDED
#define CMD_UTILS_H_INCLUDED

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus


#define CMD_YES 1
#define CMD_NO 0

typedef unsigned int size_t;

size_t cmd_generate_hash(const char* arg, size_t size);
void cmd_init(const char* noarg_options, size_t strSize);
void cmd_process(int argc, char** argv);
size_t cmd_get_option();
size_t cmd_get_arg_size();
size_t cmd_get_argc();
const char* cmd_get_error();
const char* cmd_get_appname();
const char* cmd_get_fullpath();
const char* cmd_get_appdir();
const char* cmd_get_argument();
void cmd_next_arg();
void cmd_reset_cursor_beg();
void cmd_reset_cursor_end();

#ifdef __cplusplus
}
#endif // __cplusplus


#endif // CMD_UTILS_H_INCLUDED
