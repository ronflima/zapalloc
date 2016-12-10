/* -*-c-*-
   The MIT License (MIT)

   Copyright (c) 2016 - Ronaldo Faria Lima

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all
   copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE.
   
   Created: 2016-12-09 by Ronaldo Faria Lima

   This file purpose: Internal header file. Intended to declare only data types
   that should not be exposed to the public.
*/

#ifndef ZAPALLOC_TYPES_H
#define ZAPALLOC_TYPES_H

#include "zapalloc_macros.h"
#include <stddef.h>
#include "zapalloc.h"

ZPC_BEGIN_DECLS

/*
 * Context. Bookeeps information about all memory arenas. The memory layout is modeled like this:
 * |<---------- arena ------------>| 
 * |[block][block][block]...[block]|
 *
 * |<---------- arena ------------>| 
 * |[block][block][block]...[block]|
 *
 * Arenas are not contiguous. But a block is contiguous inside a given
 * arena. The arena is always aligned to the proper cpu, even when blocks are
 * not.  
 *
 * Blocks always have the same size. Arena's size is a multiple of the block
 * size. 
 */
struct zapalloc_context
{
  size_t narenas;                       /* Number of current arenas */
  size_t nblocks;                       /* Number of blocks per arena */
  size_t block_size;                    /* Block size */
  struct zapalloc_memory_arena *arenas; /* List of arenas */
};

/*
 * Memory arena. Contains a list of blocks organized as a vector.
 */
struct zapalloc_memory_arena
{
  size_t nblocks;                        /* Total number of blocks*/
  size_t fblocks;                        /* Number of free blocks */
  struct zapalloc_context *owner;        /* Points to the context that owns this arena */
  struct zapalloc_memory_block *blocks;  /* List of blocks */
};

/*
 * Memory block. It is mapped into a list of blocks inside an arena
 */
struct zapalloc_memory_block
{
  unsigned char used;                   /* Boolean. 0 if unused. 1 otherwise. */
  struct zapalloc_memory_arena *owner;  /* Arena that owns this block */
  void *block;                          /* Memory block. This is what the library user will receive back */
};

ZPC_END_DECLS

#endif /* ZAPALLOC_TYPES_H */
