#ifndef ALLOC_H

#define ALLOC_H

#include "shared/shared.h"
#include "utils/logger/logger.h"

void *xmalloc(size_t nbBlocks, size_t blockSize);
void *xcalloc(size_t nbBlocks, size_t blockSize);
void *xrealloc(void *ptr, size_t nbBlocks, size_t blockSize);

#endif