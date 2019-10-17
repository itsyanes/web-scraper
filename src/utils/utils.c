#include "utils.h"

void *xmalloc(size_t nbBlocks, size_t blockSize)
{
    void *ptr = malloc(nbBlocks * blockSize);
    if (ptr == NULL) {
        fprintf(stderr, "Memory allocation failure");
        exit(EXIT_FAILURE);
    }
    return ptr;
}