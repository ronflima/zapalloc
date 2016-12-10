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
   
   This file purpose: Main header file
*/

#ifndef ZAPALLOC_H
#define ZAPALLOC_H

#include <stddef.h>
#include "zapalloc_macros.h"

ZPC_BEGIN_DECLS

extern struct zapalloc_context;

typedef struct zapalloc_context *zapalloc_context_t;

/* Error handling */
typedef enum
  {
    E_ZPC_OK = 0x0,  /* Operation concluded correctly */
    E_ZPC_NOMEM,     /* No memory to conclude operation */
    E_ZPC_INVAL      /* Invalid argument */
  } zapalloc_error_t;

/* Main Interfaces */

zapalloc_error_t (zapalloc_init)   __P((zapalloc_context_t *, size_t, size_t));
zapalloc_error_t (zapalloc_alloc)  __P((zapalloc_context_t, size_t, void **));
zapalloc_error_t (zapalloc_free)   __P((zapalloc_context_t, void *));
zapalloc_error_t (zapalloc_deinit) __P((zapalloc_context_t));

ZPC_END_DECLS
                                  
#endif /* ZAPALLOC_H */
