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
#include "cmd_utils.h"

int main(int argc, char** argv)
{
    char no_argument_options[] = "s,help,w;";
    cmd_init(no_argument_options, 10);
    cmd_process(argc, argv);
    for(size_t i = 0; i < argc; i++)
    {
        printf("%s \n", argv[i]);
    }
    for(size_t i = 0; i < cmd_get_argc(); i++)
    {
        size_t hash = cmd_get_option();
        if(hash == cmd_generate_hash("-t", 2))
            printf("%s \n", cmd_get_argument());
        else
            printf("%s", "Unknown argument!");
        cmd_next_arg();
    }
    printf("%s \n", cmd_get_appdir());
    printf("%s \n", cmd_get_appname());
    printf("%s \n", cmd_get_fullpath());
    return 0;
}
