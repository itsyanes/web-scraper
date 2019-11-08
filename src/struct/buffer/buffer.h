#ifndef BUFFER_H

#define BUFFER_H

#include "shared/shared.h"
#include "utils/alloc/alloc.h"

typedef struct Buffer Buffer;
typedef struct BufferPrototype BufferPrototype;

struct BufferPrototype
{
    Buffer *(*append)(Buffer *buffer, const byte *data, size_t size);
    Buffer *(*clone)(Buffer *buffer);
    void (*destroy)(Buffer *buffer);
};

struct Buffer
{
    byte *data;
    size_t size;
    BufferPrototype *proto;
};

Buffer *newBuffer();

#endif