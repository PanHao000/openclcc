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

#include <errno.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "io.h"
#include "opencl.h"

static int usage(const char *name)
{
    fprintf(stdout, "Usage: %s <file.cl>\n", name);
    return -1;
}

static int handle_standard_error(const char *file)
{
    fprintf(stderr, "%s: Error: %s\n", file, strerror(errno));
    return -1;
}


int main(int argc, char *argv[])
{
    int i, ret;
    opencl_kernel_t buffer;
    cl_context cl_ctx;

    if(argc == 1) return usage(argv[0]);

    if(opencl_init(&cl_ctx) < 0) return -1;


    for(i = 1; i < argc; i++) {
        if(opencl_open_kernel(argv[i], &buffer) < 0) {
            handle_standard_error(argv[i]);   
        }

        ret = opencl_compile(cl_ctx, buffer, "");

        opencl_release_kernel(&buffer);
        if(ret < 0) return -1;
    }

    opencl_fini(cl_ctx);
    return 0;
}
