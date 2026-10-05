//
//  suballocator.h
//  INFOB3 - Suballocator
//
//

#ifndef suballocator_h
#define suballocator_h

#include <stdlib.h>

// Input: none
// Output: none              
//
// If the suballocator is already initialised, this function does nothing.
void suballocator_init();

// Input: n - number of bytes requested
// Output: p - a pointer, or NULL
// Precondition: none
// Postcondition: If a region of size n or greater cannot be found, return NULL 
//                else, p points to a location immediately after a header block
//                      for a newly-allocated region of some size >= 
//                      n + header size. 
void *suballocator_malloc(u_int32_t n);

// Input:  p - a pointer.
// Output: none
// Precondition: p points to a location immediately after a header block
//               within the suballocator's memory.
// Postcondition: The region pointed to by p can be re-allocated by 
//                suballocator_malloc
void suballocator_free(void *p);

// Stop the allocator, so that it can be init'ed again:
void suballocator_exit(void);


#endif
