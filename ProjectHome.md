One of the pains of developing OpenCL applications are run-time compilation errors, which are as descriptive as getting a `CL_BUILD_PROGRAM_FAILURE` after calling `clBuildProgram()`. Of course, you can include the code to handle compilation errors, get the compilation log, and print it on the screen. I do not like this approach because most of the time, my application users do not care about these sort of errors and adding this code to each application I develop is boring.

OpenCLcc is a compiler wrapper that performs a static null compilation of OpenCL kernels. Basically, openclcc is just the code to set up a minimum OpenCL context, load one or more text files containing OpenCL kernel code, compile those files and show the OpenCL compiler output to the user. This simple piece of code eases OpenCL development, because you can compile your OpenCL kernels in an isolated way, and get descriptive compilation errors.

This little tool is quite helpful for me, I hope you find OpenCLcc as useful as I do.

**Mac OS X is now supported!**

If you have any suggestion on how to improve OpenCLcc, just add a new Issue to the project.

A experimental feature in OpenCLcc is the ability of embedding OpenCL kernels within executable (ELF) file. Check the (primitive) [documentation](openclccembed.md).

## How to Compile ##
OpenCLcc uses [Autotools](http://www.gnu.org/software/autoconf/) as configuration and build system. The `configure` script expects `CL/cl.h` to be in the include path, so if your installation of OpenCL is not in a standard directory, you need to add it to the include path at configuration time.
```
$ tar -zxf openclcc-0.0.1.tar.gz
$ mkdir build; cd build
$ CPPFLAGS=-I<path to CL/cl.h> ../openclcc-0.0.1/configure
$ make; make install
```

If you are getting the code from the mercurial repository, you need to run the `setup.sh` script to create the `configure` script.
```
$ hg clone https://openclcc.googlecode.com/hg/ openclcc
$ (cd openclcc; ./setup.sh)
$ mkdir build; cd build
$ ../openclcc/configure
$ make; make install
```
