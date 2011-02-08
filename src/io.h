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

#ifndef OPENCLCC_IO_H_
#define OPENCLCC_IO_H_

#include "opencl.h"

#ifdef __cplusplus
extern "C" {
#endif

int opencl_check_file(const char *name);
int opencl_open_kernel(const char *name, opencl_kernel_t *kernel);
int opencl_release_kernel(opencl_kernel_t *kernel);

#ifdef __cplusplus
}
#endif


#endif
