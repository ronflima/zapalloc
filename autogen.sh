#!/bin/sh

LIBTOOLIZE=glibtoolize
if [ -x "$(command -v libtoolize)" ]
then
    LIBTOOLIZE=libtoolize
fi

$LIBTOOLIZE
aclocal --verbose
automake --verbose 
autoconf --verbose
