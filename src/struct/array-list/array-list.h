#ifndef ARRAY_LIST_H

#define ARRAY_LIST_H

#include "shared/shared.h"
#include "utils/alloc/alloc.h"

typedef struct ArrayListPrototype ArrayListPrototype;
typedef struct ArrayList ArrayList;

struct ArrayListPrototype {
    void (*concat)();
    void (*fill)();
    void (*every)();
    void (*filter)();
    void (*find)();
    void (*findIndex)();
    void (*forEach)();
    void (*includes)();
    void (*indexOf)();
    void (*map)();
    void (*pop)();
    void (*push)();
    void (*reduce)();
    void (*shift)();
    void (*slice)();
    void (*unshift)();
    void (*some)();
    void (*sort)();
    void (*desroy)();
};

struct ArrayList {
    void *list;
    size_t size;
    size_t _blockSize;
    ArrayListPrototype *proto;
};

ArrayList *newArrayList();
ArrayList *fromArray(void *source, size_t nbBlocks, size_t blockSize);

#endif