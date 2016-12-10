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

   This file purpose: Deinitializes a given context
*/


#include <stdlib.h>
#include <assert.h>
#include "zapalloc.h"
#include "zapalloc_types.h"

static int
have_used_blocks(zapalloc_context_t);

zapalloc_error_t
zapalloc_deinit(zapalloc_context_t context)
{
  struct zapalloc_arena *arena;
  assert(context != NULL);
  assert(context->arenas != NULL);
  if (have_used_blocks(context))
    {
      return E_ZPC_BUSY;
    }
  for (arena = context->arenas; arena - context->arenas < context->narenas; ++arena)
    {
      free(arena->blocks);
    }
  free(context->arenas);
  free(context);
  return E_ZPC_OK;
}

static int have_used_blocks(zapalloc_context_t context)
{
  struct zapalloc_arena *arena;
  for (arena = context->arenas; arena - context->arenas < context->narenas; ++arena)
    {
      /* Optimization: if the number of free blocks is different from the number
         of blocks, then we have blocks still being used. */
      if (arena->nblocks != arena->fblocks)
        {
          return 0x1;
        }
    }
  return 0x0;
}
