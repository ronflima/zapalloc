# zapalloc

Fast memory allocation routines for fixed size memory blocks. This small library
is intended to provide fast allocation and memory reusage when there are fixed
size memory blocks wanted. This assumption makes this library not suitable for
general usage and is specific for several small scenarios where memory is needed
in blocks of the same size.
