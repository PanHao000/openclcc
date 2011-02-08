/*
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "log.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char *opencl_log_token = "<program source>";

char *opencl_log_parse(size_t log_size, const char *log, const char *name)
{
    size_t name_size = 0, token_size = 0, final_size = log_size, offset = 0;
    const char *ptr = log, *last_ptr = NULL;
    char *new_log = NULL;
    int n = 0;

    name_size = strlen(name);
    token_size = strlen(opencl_log_token);

    /* First pass, detect strings to be replaced with source file */
    while(ptr != NULL) {
        ptr = strstr(ptr, opencl_log_token);
        if(ptr == NULL) continue;
        final_size += (name_size - token_size);
        ptr += token_size;
    } 

    if((new_log = (char *)malloc(final_size + 1)) == NULL) {
        return NULL;
    }
    
    /* Second pass, replace token with file name */
    ptr = last_ptr = log;
    while(ptr != NULL) {
        ptr = strstr(ptr, opencl_log_token);
        if(ptr == NULL) continue;
        n = ptr - last_ptr;
        if(n > 0) {
            memcpy((void *)&new_log[offset], last_ptr, n);
            offset += n;
        }
        memcpy((void *)&new_log[offset], name, name_size);
        offset += name_size;
        ptr += token_size;
        last_ptr = ptr;
    }
    /* Copy the last part of the string */
    if(offset < final_size) {
        memcpy(&new_log[offset], last_ptr, final_size - offset);
        offset = final_size;
    }
    new_log[offset] = 0; /* End of string */

    return new_log;
}
