#ifndef ARRAY_LIST_H

#define ARRAY_LIST_H

#include "shared/shared.h"

typedef struct ArrayList ArrayList;
struct ArrayList {
    void(*from)(void *, size_t);
    void (*concat)();
    void (*fill)();
    void (*length)();
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
};

#endif