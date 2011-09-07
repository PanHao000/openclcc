AC_INIT([OpenCLcc], [11.8], [igelado@illinois.edu],[openclcc])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_CONFIG_MACRO_DIR([m4])
AC_USE_SYSTEM_EXTENSIONS

AC_PROG_INSTALL
AC_PROG_CC
AC_PROG_LIBTOOL
LT_PATH_LD
AUTOCONF_ENV="SHELL=/bin/sh"
LT_INIT

AC_ARG_WITH([include],
            [AS_HELP_STRING([--with-include],
                            [Add include directory path])],
                            [CPPFLAGS="$CPPFLAGS -I$withval"],
                            [])


AC_CHECK_HEADERS(CL/cl.h, [], [
    AC_CHECK_HEADERS(OpenCL/cl.h, [], [
        echo "OpenCL header files not found in your system"
        exit -1
    ])
])


AC_MSG_CHECKING(whether host is Mac OS)
case "${host_os}" in
    darwin* )
        LDFLAGS="$LDFLAGS -framework OpenCL"
        AC_MSG_RESULT(yes)
    ;;
    *)
        AC_MSG_RESULT(no)
        AC_CHECK_LIB(OpenCL, clGetPlatformIDs, [],[ 
            echo "OpenCL library not found in your system"
            exit -1
        ])
esac

AC_MSG_CHECKING(whether to enable debug mode)
debug_default="no"
AC_ARG_ENABLE(debug,
        AS_HELP_STRING([--enable-debug],[turn on debug mode [[default=no]]])
        , , enable_debug=$debug_default)
if test "$enable_debug" = "yes"; then
    AC_MSG_RESULT(yes)
    CFLAGS="-Wall -Werror -g -O0 -fno-inline"
    AC_DEFINE(DEBUG)
else
    AC_MSG_RESULT(no)
    CFLAGS="-Wall -O3 -fomit-frame-pointer"
fi

AC_CONFIG_FILES([
    Makefile
    src/Makefile
    embed/Makefile
    embed/openclcc-embed
])
AC_OUTPUT
