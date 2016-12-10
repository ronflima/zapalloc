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

   Created: 2016-12-10 by Ronaldo Faria Lima

   This file purpose: Initializes the memory allocation context.
*/

#include <stdlib.h>
#include <assert.h>
#include "zapalloc.h"
#include "zapalloc_types.h"

static void
initialize_memory_blocks(struct zapalloc_memory_arena *, size_t);

zapalloc_error_t
zapalloc_init (zapalloc_context_t *context, size_t nblocks, size_t bsize)
{
  assert(context != NULL);
  assert(nblocks > 0);
  assert(bsize > 0);
  *context = (zapalloc_context_t)malloc(sizeof(struct zapalloc_context));
  if (*context == NULL)
    {
      return E_ZPC_NOMEM;
    }
  (*context)->narenas = 0x1;
  (*context)->block_size = bsize;
  (*context)->arenas = (struct zapalloc_memory_arena *)
    malloc(sizeof(struct zapalloc_memory_arena));
  if ((*context)->arenas == NULL)
    {
      free(*context);
      return E_ZPC_NOMEM;
    }
  (*context)->arenas->nblocks = (*context)->arenas->fblocks = nblocks;
  (*context)->arenas->blocks = (struct zapalloc_memory_block *)
    calloc(nblocks, bsize + sizeof(struct zapalloc_memory_block));
  if ((*context)->arenas->blocks == NULL)
    {
      free ((*context)->arenas);
      free (*context);
      return E_ZPC_NOMEM;
    }  
  initialize_memory_blocks((*context)->arenas, nblocks);
  return E_ZPC_OK;
}

static void
initialize_memory_blocks(struct zapalloc_memory_arena *arena, size_t nblocks)
{
  assert (blocks != NULL);
  assert (nblocks > 0);
  struct zapalloc_memory_block *block;
  for (block = arena->blocks; block - arena->blocks < nblocks; ++block)
    {
      block->used = '\0x0';
      block->arena = arena;
      block->block = (void *)(((char *)block) + sizeof(struct zapalloc_memory_block)); 
    }
}
