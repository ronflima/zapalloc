# zapalloc

Fast memory allocation routines for fixed size memory blocks. This small library
is intended to provide fast allocation and memory reusage when fixed size memory
blocks are needed. This assumption makes this library not suitable for general
usage and is specific for several small scenarios where memory is needed in
blocks of the same size.

You can create several contexts, however, each one taking care of a block of a
different size.

This is not a memory debugger, but an attempt to optimize memory allocations by
given the opportunity to alloc large amounts of memory and manage usage for you.

## Fast or Crash

This library was created with this in mind: be fast or crash. There is no memory
debugging, no memory protection, no nothing. So, if your software invade memory,
it will crash. So, be careful.

# Simple, stupid

This library was built over STDC malloc/calloc/realloc functions. It was
designed to minimize system calls when returning memory to the user. Algorithms
are really simple and are designed for speed. 
