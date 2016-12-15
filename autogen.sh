#!/bin/sh

LIBTOOLIZE=glibtoolize
if [ -x "$(command -v libtoolize)" ]
then
    LIBTOOLIZE=libtoolize
fi

$LIBTOOLIZE --version
aclocal --version
automake --version
autoconf --version

$LIBTOOLIZE
aclocal
automake
autoconf
