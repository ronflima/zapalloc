SUBDIRS=src

ACLOCAL_AMFLAGS=-I m4

check_PROGRAMS = 	\
tests/init_deinit 	\
tests/alloc_free	\
tests/big_allocations

TESTS = $(check_PROGRAMS)

LDADD=src/libzapalloc.la

AM_CPPFLAGS=-I./include
