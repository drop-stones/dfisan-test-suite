#ifndef SAFE_ALLOC_H
#define SAFE_ALLOC_H

#include <stddef.h>
#include <stdlib.h>

/// Safe malloc
void *safe_malloc(size_t size) { return malloc(size); };
void *safe_calloc(size_t nmemb, size_t size) { return calloc(nmemb, size); };
void *safe_realloc(void *ptr, size_t size) { return realloc(ptr, size); };

#endif