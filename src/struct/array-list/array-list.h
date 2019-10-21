#ifndef ARRAY_LIST_H

#define ARRAY_LIST_H

#include "shared/shared.h"
#include "utils/alloc/alloc.h"

typedef struct ArrayListPrototype ArrayListPrototype;
typedef struct ArrayList ArrayList;

struct ArrayListPrototype {
    void (*add)();
    void (*delete)();
    void (*deleteAt)();
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
    void (*reduce)();
    void (*slice)();
    void (*some)();
    void (*sort)();
    void (*destroy)();
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