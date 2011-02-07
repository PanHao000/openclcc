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

#include "opencl.h"

#include <stdio.h>

static int opencl_handle_error(cl_int error)
{
    fprintf(stderr, "OpenCL Error: %d\n", error);
    return -1;
}

int opencl_init(cl_context *cl_ctx)
{
    cl_platform_id cl_platform;
    cl_device_id cl_device;
    cl_int ret;

    if((ret = clGetPlatformIDs(1, &cl_platform, NULL)) != CL_SUCCESS)
        return opencl_handle_error(ret);
    if((ret = clGetDeviceIDs(cl_platform, CL_DEVICE_TYPE_ALL, 1, &cl_device, NULL)) != CL_SUCCESS)
        return opencl_handle_error(ret);

    *cl_ctx = clCreateContext(NULL, 1, &cl_device, NULL, NULL, &ret);
    if(ret == CL_SUCCESS) return 0;
    return opencl_handle_error(ret);
}

int opencl_fini(cl_context cl_ctx)
{
    cl_int ret;
    if((ret = clReleaseContext(cl_ctx)) != CL_SUCCESS)
        return opencl_handle_error(ret);
    return 0;
}

int opencl_compile(opencl_kernel_t kernel)
{
    // TODO: Get cl_program and compile kernel
    return 0;
}
