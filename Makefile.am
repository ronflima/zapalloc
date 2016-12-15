SUBDIRS=src

ACLOCAL_AMFLAGS=-I m4

check_PROGRAMS = 	\
tests/init_deinit 	\
tests/big_allocations

TESTS = $(check_PROGRAMS)

LDADD=src/libzapalloc.la

AM_CPPFLAGS=-I./include
