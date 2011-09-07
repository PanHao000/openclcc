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

#include <unistd.h>

#include "io.h"
#include "opencl.h"

static int usage(const char *name)
{
    fprintf(stdout, "Usage: %s [-o <binary_file>] <file.cl> [compilation_flags...]\n", name);
    return -1;
}

static int handle_standard_error(const char *file)
{
    fprintf(stderr, "%s: Error: %s\n", file, strerror(errno));
    return -1;
}

static char *build_args_string(int argc, char *argv[])
{
    int i, args_size = 1, ptr = 0;
    char *args = NULL;

    /* First pass; calculate the argument string size */
    for(i = 1; i < argc; i++) {
        if(*argv[i] != '-' && opencl_check_file(argv[i]) == 0) continue;
        args_size += strlen(argv[i]) + 1;
    }

    /* Second pass; allocate argument string and build it */
    if((args = (char *)malloc(args_size)) == NULL) return args;
    *args = 0; /* End of String */
    for(i = 0; i < argc; i++) {
        if(*argv[i] != '-' && opencl_check_file(argv[i]) == 0) continue;
        ptr += snprintf(&args[ptr], (args_size - ptr), "%s ", argv[i]);
    }
    
    return args;
}

typedef enum {
    PARAM_EQUAL,
    PARAM_DIFFERENT
} param_result;
static int
check_param(const char *user, const char *expected)
{
    if ((strlen(user) == strlen(expected)) &&
        (strncmp(user, expected, strlen(expected)) == 0)) {
        return PARAM_EQUAL;
    } else {
        return PARAM_DIFFERENT;
    }
}

#define OUTPUT_FILE_FLAG "-o"

int main(int argc, char *argv[])
{
    int i, ret;
    opencl_kernel_t kernel;
    cl_context cl_ctx;
    char *args = NULL;
    char *file_out = NULL;
    unsigned offset = 0;

    if(argc == 1) return usage(argv[0]);
    if(argc >= 4) {
        if (check_param(argv[1], OUTPUT_FILE_FLAG) == PARAM_EQUAL) {
            file_out = argv[2];
            offset = 2;
        }
    }
    argc -= offset;
    argv += offset;

    if(file_out != NULL) {
        if(opencl_check_file(file_out) == 0) {
            unlink(file_out);
        }
    }

    if((args = build_args_string(argc, argv)) == NULL) return -1;

    if(opencl_init(&cl_ctx) < 0) return -1;
    fprintf(stdout, "Compiler flags: %s\n", args);

    for(i = 1; i < argc; i++) {
        if(*argv[i] == '-' || opencl_check_file(argv[i]) < 0)
            continue; /* Skip compiler flags */
        if(opencl_open_kernel(argv[i], &kernel) < 0) {
            handle_standard_error(argv[i]);   
        }

        ret = opencl_compile(cl_ctx, kernel, file_out, args);

        opencl_release_kernel(&kernel);
        if(ret < 0) return -1;
    }

    opencl_fini(cl_ctx);
    return 0;
}
