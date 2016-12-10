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

   This file purpose: Returns a memory block to the caller and mark it as "in use"
*/

#include <stdlib.h>
#include "zapalloc.h"
#include "zapalloc_types.h"

static struct zapalloc_memory_arena *
find_free_arena(struct zapalloc_memory_arena *, size_t);

static struct zapalloc_memory_arena *
append_new_arena(zapalloc_context_t);

static struct zapalloc_memory_block *
find_free_block(struct zapalloc_memory_arena *);

zapalloc_error_t
zapalloc_alloc(zapalloc_context_t context, void **data)
{
  struct zapalloc_memory_arena *arena;
  struct zapalloc_memory_block *block;
  
  /* First: Search an arena with free blocks */
  arena = find_free_arena(context->arenas, context->narenas);
  if (arena == NULL)
    {
      /* No available arenas. Need to create a brand new one, adding it to the
         context. */
      arena = append_new_arena(context);
    }
  if (arena == NULL)
    {
      return E_ZPC_NOMEM;
    }
  /* Second: Search for a free block within an arena */
  block = find_free_block(arena);
  if (block == NULL)
    {
      return E_ZPC_NOMEM;
    }
  block->used = (unsigned char) 0x1;
  *data = block->block;
  return E_ZPC_OK;
}

/* TODO: Optmize this routine. It makes a linear search. It is not expected to
   have big lists of arenas and in this scenario a linear search is simple
   enough. But it could be better. */
static struct zapalloc_memory_arena *
find_free_arena(struct zapalloc_memory_arena *arenas, size_t narenas)
{
  struct zapalloc_memory_arena *arena;
  for (arena = arenas; arena - arenas < narenas; ++arena)
    {
      if (arena->fblocks > 0x0)
        {
          return arena;
        }
    }
  return NULL;
}

static struct zapalloc_memory_arena *
append_new_arena(zapalloc_context_t context)
{
  struct zapalloc_memory_arena *arena;
  struct zapalloc_memory_block *block;
  arena = (struct zapalloc_memory_arena *)
    realloc (context->arenas, sizeof(struct zapalloc_memory_arena) * (context->narenas + 1));
  if (arena == NULL)
    {
      return NULL;
    }
  ++(context->narenas);
  context->arenas = arena;
  arena = context->arenas + context->narenas - 1;
  arena->nblocks = arena->fblocks = context->nblocks;
  arena->blocks = (struct zapalloc_memory_block *) calloc(context->nblocks, sizeof(struct zapalloc_memory_block) + context->block_size);
  arena->owner = context;
  if (arena->blocks == NULL)
    {
      --(context->narenas);
      return NULL;
    }
  for (block = arena->blocks; block - arena->blocks < arena->nblocks; ++block)
    {
      block->used = (unsigned char) 0x0;
      block->owner = arena;
      block->block = (void *)((char *)block + sizeof(struct zapalloc_memory_block));
    }
  return arena;
}

static struct zapalloc_memory_block *
find_free_block(struct zapalloc_memory_arena *arena)
{
  struct zapalloc_memory_block *block;
  for (block = arena->blocks; block - arena->blocks < arena->nblocks; ++block)
    {
      if (!block->used)
        {
          return block;
        }
    }
  return block;
}
