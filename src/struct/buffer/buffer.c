#include "buffer.h"

static BufferPrototype *getBufferProto();
static bool BufferIsAllocated(Buffer *buffer);
static void BufferDestroyBuffer(Buffer *buffer);
static Buffer *BufferClone(Buffer *buffer);
static Buffer *BufferAppend(Buffer *buffer, const byte *data, size_t size);

Buffer *newBuffer()
{
    Buffer *buffer = xmalloc(1, sizeof(Buffer));
    buffer->size = 0;
    buffer->data = NULL;
    buffer->proto = getBufferProto();
    return buffer;
}

bool BufferIsAllocated(Buffer *buffer)
{
    return buffer->size > 0 && buffer->data != NULL;
}

BufferPrototype *getBufferProto()
{
    static BufferPrototype *proto = NULL;
    if (!proto)
    {
        proto = xmalloc(1, sizeof(BufferPrototype));
        proto->destroy = &BufferDestroyBuffer;
        proto->clone = &BufferClone;
        proto->append = &BufferAppend;
    }
    return proto;
}

Buffer *BufferClone(Buffer *buffer)
{
    Buffer *new = xmalloc(1, sizeof(Buffer));
    new->size = buffer->size;
    new->data = xmalloc(new->size, 1);
    memcpy(new->data, buffer->data, new->size);
    new->proto = getBufferProto();
    return new;
}

Buffer *BufferAppend(Buffer *buffer, const byte *data, size_t size)
{
    buffer->data = xrealloc(buffer->data, buffer->size + size, 1);
    memcpy(buffer->data + buffer->size, data, size);
    buffer->size += size;
    return buffer;
}

void BufferDestroyBuffer(Buffer *buffer)
{
    if (BufferIsAllocated(buffer))
    {
        free(buffer->data);
    }
    free(buffer);
}