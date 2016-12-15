#                                               -*- Autoconf -*-
#   The MIT License (MIT)
#   
#   Copyright (c) 2016 - Ronaldo Faria Lima
#   
#   Permission is hereby granted, free of charge, to any person obtaining a copy
#   of this software and associated documentation files (the "Software"), to deal
#   in the Software without restriction, including without limitation the rights
#   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
#   copies of the Software, and to permit persons to whom the Software is
#   furnished to do so, subject to the following conditions:
#
#   The above copyright notice and this permission notice shall be included in all
#   copies or substantial portions of the Software.
#
#   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
#   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
#   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
#   SOFTWARE.
#   
#   Created: 2016-12-09 by Ronaldo Faria Lima
#   
#   This file is part of ZapAlloc memory allocation library

AC_PREREQ([2.6])
AC_INIT([ZapAlloc], [1.0.0], [contato@nineteenapps.com])
AM_INIT_AUTOMAKE([subdir-objects])
AM_SILENT_RULES([yes])
LT_INIT
AC_CONFIG_SRCDIR([include/zapalloc.h])
AC_CONFIG_MACRO_DIR([m4])

# Checks for programs.
AC_PROG_CC
AC_PROG_LIBTOOL

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([stddef.h stdlib.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC

# Create the ability to put debugging code into the library
AC_ARG_ENABLE(debug,
[  --enable-debug          Turn on debugging of the library],
[case "${enableval}" in
  yes) debug=true;;
  no) debug=false;;
  *) AC_MSG_ERROR(bad value ${enableval} for --enable-debug);;
esac], [debug=false])
AM_CONDITIONAL(DEBUG, test x$debug = xtrue)
if test x$debug = xtrue; then
  AC_SUBST([CFLAGS], [-g])
else
  AC_SUBST([CFLAGS], [-DNDEBUG])
fi

# Disable assertions for debugging purposes
AC_ARG_ENABLE(assertions,
[  --disable-assertions    Disable assertions in the code],
[case "${enableval}" in
  no) assertions=true;;
  yes) assertions=false;;
  *) AC_MSG_ERROR(bad value ${enableval} for --disable-assertions);;
esac], [assertions=false])
AM_CONDITIONAL(DEBUG, test x$assertions = xtrue)
if test x$assertions = xtrue; then
  AC_SUBST([CFLAGS], [-DNDEBUG])
fi

# Create the ability to profile the library
AC_ARG_ENABLE(profiling,
[  --enable-profiling      Turn on profiling of the library],
[case "${enableval}" in
  yes) profiling=true;;
  no) profiling=false;;
  *) AC_MSG_ERROR(bad value ${enableval} for --enable-profiling);;
esac], [profiling=false])
AM_CONDITIONAL(DEBUG, test x$profiling = xtrue)
if test x$profiling = xtrue; then
  AC_SUBST([CFLAGS], [-pg])
fi


AC_CONFIG_FILES([Makefile
                 src/Makefile])
AC_OUTPUT
