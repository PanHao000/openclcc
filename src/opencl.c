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

static void opencl_print_compilation_log(size_t log_size, char *log, opencl_kernel_t kernel)
{
    fprintf(stderr, "%s", log);
}

static int opencl_handle_compilation_errors(cl_program program, opencl_kernel_t kernel)
{
    cl_int ret, num_devices;
    cl_device_id *devices = NULL;
    int i;
    cl_build_status build_status = CL_BUILD_NONE;
    char * log = NULL;
    size_t log_size = 0;

    /* Get the number of devices associated to the program, allocate memory
     * and get the associated devices */
    if((ret = clGetProgramInfo(program, CL_PROGRAM_NUM_DEVICES,
            sizeof(num_devices), &num_devices, NULL)) != CL_SUCCESS) {
        return opencl_handle_error(ret);
    }

    if((devices = (cl_device_id *)malloc(num_devices * sizeof(cl_device_id))) == NULL)
        return -1;

    if((ret = clGetProgramInfo(program, CL_PROGRAM_DEVICES,
            num_devices * sizeof(cl_device_id), devices, NULL)) != CL_SUCCESS) {
        free(devices);
        return opencl_handle_error(ret);
    }

    /* Check the output for each device */
    for(i = 0; i < num_devices; i++) {
        /* If there are no compilation errors for the device, continue */
        if((ret = clGetProgramBuildInfo(program, devices[i], CL_PROGRAM_BUILD_STATUS,
                sizeof(build_status), &build_status, NULL)) != CL_SUCCESS) {
            return opencl_handle_error(ret);
        }
        if(build_status != CL_BUILD_ERROR) continue;

        /* Get the compilation log, and show it to the user */
        if((ret = clGetProgramBuildInfo(program, devices[i], CL_PROGRAM_BUILD_LOG,
                0, NULL, &log_size)) != CL_SUCCESS) {
            return opencl_handle_error(ret);
        }
        if(log_size == 0) {
            fprintf(stderr,"%s: Undefined compilation error\n", kernel.name);
            continue;
        }
        if((log = (char *)malloc(log_size * sizeof(char))) == NULL) {
            return -1;
        }

        if((ret = clGetProgramBuildInfo(program, devices[i], CL_PROGRAM_BUILD_LOG,
                log_size, log, NULL)) != CL_SUCCESS) {
            free(log);
            return opencl_handle_error(ret);
        }

        opencl_print_compilation_log(log_size, log, kernel);

        free(log);
    }

    return 0;
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

int opencl_compile(cl_context cl_ctx, opencl_kernel_t kernel, const char *args)
{
    cl_program program;
    cl_int ret;

    program = clCreateProgramWithSource(cl_ctx, 1, (const char **)&kernel.buffer, &kernel.size, &ret);
    if(ret != CL_SUCCESS)
        return opencl_handle_error(ret);

    if((ret = clBuildProgram(program, 0, NULL, args, NULL, NULL)) != CL_SUCCESS) {
        opencl_handle_compilation_errors(program, kernel);
    }
    else {
        fprintf(stdout, "%s: Compilation succeded!\n", kernel.name);
    }

    if((ret = clReleaseProgram(program)) != CL_SUCCESS)
        return opencl_handle_error(ret);

    return 0;
}