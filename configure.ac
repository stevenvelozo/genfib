#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.61])
AC_INIT([genfib], [0.1], [steven@velozo.com])
AM_INIT_AUTOMAKE
AC_CONFIG_SRCDIR([src/main.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC
AC_PROG_RANLIB
AC_PROG_INSTALL
AM_PROG_CC_C_O

# Checks for header files (1).
AC_HEADER_STDC

# Checks for command line options
AC_ARG_ENABLE([async-exec],
	[AS_HELP_STRING([--disable-async-exec], 
		[disable asynchronous execution @<:@default: no@:>@])],
	[async_exec=${enableval}],
	[async_exec=yes])

if test "x${async_exec}" = xyes; then
	have_pthreads=no
	AC_SEARCH_LIBS([pthread_create], [pthread], 
		[have_pthreads=yes])

	if test "x${have_pthreads}" = xyes; then
		AC_CHECK_HEADERS([pthread.h], [], 
			[have_pthreads=no])
	fi

	if test "x${have_pthreads}" = xno; then
		echo "---------------------------------------"
		echo "Unable to find pthreads on this system."
		echo "Building a single-threaded version.    "
		echo "---------------------------------------"
		async_exec=no
	fi
fi

if test "x${async_exec}" = xyes; then
	AC_DEFINE([ASYNC_EXEC], 1, [async exec enabled])
fi

# Checks for header files (2).
AC_CHECK_HEADERS([stdlib.h])

# Checks for libraries.
# Checks for typedefs, structures, and compiler characteristics.
# Checks for library functions.

AC_CONFIG_FILES([Makefile
		 common/Makefile
		 rendering/Makefile
		 src/Makefile])
AC_OUTPUT

echo \
"-------------------------------------------------

 ${PACKAGE_NAME} Version ${PACKAGE_VERSION}

 Prefix: '${prefix}'.
 Compiler: '${CC} ${CFLAGS} ${CPPFLAGS}'

 Package features:
	 Async Execution: ${async_exec}

 Now type 'make @<:@<target>@:>@'
	 where the optional <target> is:
		 all                - build all binaries
		 install            - install everything

--------------------------------------------------"
