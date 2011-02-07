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

#include "io.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <errno.h>

int opencl_open_kernel(const char *name, char ** buffer)
{
    FILE *fp = NULL;
    struct stat file_stat;
    int ret = 0;

    /* Init buffer to NULL */
    *buffer = NULL;

    /* Get information about the file */
    if(stat(name, &file_stat) < 0) return -1;

    /* Read the kernel from the file */
    if((fp = fopen(name, "rt")) == NULL) return -1;

    /* Allocate the buffer which will contain the kernel */
    if((*buffer = (char *)malloc(file_stat.st_size + 1)) == NULL)
        return -1;

    /* Read the kernel file */
    if(fread((void *)buffer, sizeof(char), file_stat.st_size, fp)
            != file_stat.st_size) {
        free(*buffer);
        *buffer = NULL;
    }
    else (*buffer)[file_stat.st_size] = 0; /* Set end of string */

    fclose(fp);
    
    if(*buffer == NULL) return -1;
    return 0;
}


int opencl_release_kernel(char *buffer)
{
    if(buffer != NULL) free(buffer);
    return 0;
}    
