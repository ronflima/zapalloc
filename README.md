# zapalloc
[![Build Status][travis-badge]][travis-url]
[![License][mit-badge]][mit-url]

## The irresponsible memory allocator
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
debugging, no memory protection, no thread protection, no nothing. So, if your
software invade memory, it will crash. So, be careful.

# Simple, stupid

This library was built over STDC malloc/calloc/realloc functions at this
version. In the future, it will replace, internally, STDC functions in favor of
system calls that can be faster. It was designed to minimize system calls when
returning memory to the user. Algorithms are really simple and are designed for
speed.

# Concepts

All memory is attached to a _context_. A context manages a certain amount of
memory which is defined during its initialization. If you request more memory
than it was initialized, the library will increase the internal memory in order
to return to you more memory, but using its initial definitions.

During its initialization, you must provide the number of blocks and the size of
each block. ZapAlloc will initialize your context with so much memory already
allocated inside. For instance, let's say you asked for 1024 blocks of 2048
bytes each. During initialization, ZapAlloc will create a poll of 1024 blocks,
with 2048 bytes each. Each call to alloc function will return to you a block
containing 2048 bytes. When you request the 1025th block, ZapAlloc will create a
new poll containing more 1024 blocks of 2048 bytes each and return a 2048 bytes
block to you.

The ideia behind the scenes is to:

- centralize all memory management on a single manageable place (the _context_);
- request a lot of memory at once, but fewer times to the system, reducing the
quantity of system calls, since system calls are too expensive.

## Why don't rely on malloc itself?

The STDC _malloc_ function is great for general memory allocation. Some
implementations do change the process's core size in order to return memory to
the system, which is great for general purpose. However, if you want
performance, it is a great idea avoiding to call the system too many times. Each
system call will cost you a lot of processing time, since your process will be
interrupted by the operating system in order to have it's core resized.

So, _zapalloc_ try to avoid those many system calls by allocating a lot of
memory at once and then managing the memory blocks in a simple fashion, so you
can have a great performance at the end.

# License

This project is released under the MIT license. See [LICENSE](LICENSE) for details.

[mit-badge]: https://img.shields.io/badge/License-MIT-blue.svg?style=flat
[mit-url]: https://tldrlegal.com/license/mit-license
[travis-badge]: https://travis-ci.org/ronflima/zapalloc.svg?branch=master
[travis-url]: https://travis-ci.org/nineteen-apps/zapalloc
