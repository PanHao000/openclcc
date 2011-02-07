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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <errno.h>

static int usage(const char *name)
{
    fprintf(stdout, "Usage: %s <file.cl>\n");
    return -1;
}

static int handle_error(const char *file)
{
    fprintf(stderr, "%s: Error: %s\n", file, strerror(errno));
    return -1;
}

int main(int argc, char *argv[])
{
    int i;
    char *kernel = NULL;

    if(argc == 1) return usage();

    /* TODO: initialize OpenCL here */

    for(i = 1; i < argc + 1; i++) {
        if(opencl_open_kernel(argv[i], &buffer) < 0) {
            handle_error(argv[i]);   
        }

        /* TODO: compile kernel and show compilation errors (if any) */
        opencl_release_kernel(kernel);
    }

    return 0;
}
