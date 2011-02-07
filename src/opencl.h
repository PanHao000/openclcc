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

#ifndef OPENCLCC_OPENCL_H_
#define OPENCLCC_OPENCL_H_

#include <CL/cl.h>

typedef struct opencl_kernel {
    char *buffer;
    size_t size;
} opencl_kernel_t;

#ifdef __cplusplus
extern "C" {
#endif

int opencl_init(cl_context *cl_ctx);
int opencl_fini(cl_context cl_ctx);
int opencl_compile(opencl_kernel_t kernel);

#ifdef __cplusplus
}
#endif


#endif
