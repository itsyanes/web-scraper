#include "alloc.h"

void *xmalloc(size_t nbBlocks, size_t blockSize)
{
    void *ptr = malloc(nbBlocks * blockSize);
    if (ptr == NULL)
    {
        fprintf(stderr, "Memory allocation failure");
        exit(EXIT_FAILURE);
    }
    return ptr;
}

void *xcalloc(size_t nbBlocks, size_t blockSize)
{
    void *ptr = xmalloc(nbBlocks, blockSize);
    memset(ptr, 0, nbBlocks * blockSize);
    return ptr;
}

void *xrealloc(void *src, size_t nbBlocks, size_t blockSize)
{
    void *dest = realloc(src, nbBlocks * blockSize);
    if (dest == NULL)
    {
        fprintf(stderr, "Memory allocation failure");
        exit(EXIT_FAILURE);
    }
    return dest;
}