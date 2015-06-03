Learn how to use openclcc-embed to embed your OpenCL files in your application's executable.

# Introduction #

With openclcc-embed you can embed files with OpenCL code in your executable. openclcc-embed allows you to distribute your programs as a single file and to remove all the error control code associated to file I/O (check that the file exists, open/close, read, ...). Moreover, openclcc-embed uses openclcc to check your OpenCL code before embedding them in the executable.

Currently, openclcc-embed works for executables in ELF format, the standard format in POSIX-compliant systems like Unix and GNU/Linux.

# Details #

openclcc-embed creates an object file that contains an ELF section with the embedded OpenCL files and their compilation flags, and defines two symbols that point to the start and end addresses of the section. This object file can be linked with the rest of your object files to build the executable.

## How to use openclcc-embed ##

Usage:
```
> openclcc-embed <outputfile> <inputfile1> [-f "<compilation flags for file1>"] [<inputfile2> [-f "<compilation flags for file2>"]] ...
```

Note that the quotes surrounding the flags are mandatory if more than one compilation parameter is specified.

Example:
```
> openclcc-embed kernel-cl.o kernel1.cl -f "-O2" kernel2.cl -f "-O3"
File: kernel1.cl
- Checking... OK
- Embedding... OK
File: kernel2.cl
- Checking... OK
- Embedding... OK

> gcc -o myprogram file.o kernel-cl.o
```

## How to compile the embedded OpenCL code in your program ##

openclcc-embed defines two link-time symbols that point to the start and end addresses of the code. To access this symbols, you have to add this to your application:

```
extern char __ocl_code_start, __ocl_code_end;
```

And the address of the symbols is obtained:

```
   char *code_start = &__ocl_code_start;
   char *code_end   = &__ocl_code_end;
```

The section can contain several OpenCL files and their respective compilation flags. openclcc-embed inserts a "magic number" between the files and their parameters to let the programmer process them easily. The magic number is !@#~ The contents of the section are organized as follows:

Code of the file 1 !@#~ Compilation flags for file 1 !@#~ ...

Future versions will add some code to ease the parsing of this section.