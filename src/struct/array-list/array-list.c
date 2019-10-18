#include "array-list.h"

ArrayList *newArrayList() 
{
    ArrayList *list = xmalloc(1, sizeof(ArrayList));
    list->list = NULL;
    list->size = 0;
    list->_blockSize = 0;
    list->proto = getArrayListPrototype();
    return list;
}

ArrayList *fromArray(void *source, size_t nbBlocks, size_t blockSize)
{
    ArrayList *list = xmalloc(1, sizeof(ArrayList));
    list->list = xmalloc(nbBlocks, blockSize);
    memcpy(list->list, source, nbBlocks * blockSize);
    list->size = nbBlocks;
    list->_blockSize = blockSize;
    list->proto = getArrayListPrototype();
    return list;
}

ArrayListPrototype *getArrayListPrototype()
{
    static ArrayListPrototype *proto = NULL;
    if (!proto)
    {
        proto = xmalloc(1, sizeof(ArrayListPrototype));
    }
    return proto;
}
