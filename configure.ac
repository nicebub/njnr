#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.71])
AC_INIT([njnr], [0.01], [njnr@github.com])
AM_INIT_AUTOMAKE([subdir-objects -Wall -Werror foreign])

# these two lines didn't work, without them does
AC_CONFIG_SRCDIR([src])
AC_CONFIG_HEADERS([config.h:config.h.in])
# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_YACC([noyylwrap])
AC_PROG_LEX([noyywrap])
AS_IF([test "x$LEX" = "x:"],AC_MSG_ERROR([could not find flex]),[])
AC_PATH_PROG(BISON, bison, nobison)
AS_IF([test "$ac_cv_path_BISON" = "nobison"],AC_MSG_ERROR([could not find bison]),[])
AC_CHECK_PROG([FLEX], [flex lex], [flex])
# Force the use of `missing' to wrap Flex invocations.
AM_MISSING_PROG([LEX], [$FLEX])
# Perform all the tests Automake and Autoconf need.
AM_PROG_LEX
# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_SIZE_T

#add lint-er option
AC_PATH_PROG([CPPLINT], [cpplint], [true])
AS_IF([test "x$CPPLINT" = x],
    [AC_MSG_WARN([We recommend cpplint for developing this package.])])

# Checks for library functions.
AC_FUNC_ERROR_AT_LINE

AC_CONFIG_FILES([Makefile
                 src/Makefile])
AC_OUTPUT
