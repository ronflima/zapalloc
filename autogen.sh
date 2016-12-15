#!/bin/sh

LIBTOOLIZE=libtoolize
if [ -x `which glibtoolize` ]
then
    LIBTOOLIZE=glibtoolize
fi

$LIBTOOLIZE
aclocal
automake
autoconf
