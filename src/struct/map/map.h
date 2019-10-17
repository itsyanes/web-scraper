#ifndef MAP_H

#define MAP_H

#include "utils/alloc.h"
#include "shared/shared.h"

typedef struct Map Map;
struct Map
{
    void *(*get)(Map *, void *key);
    void (*set)(Map *, void *key, void *value);
    void (*clear)(Map *);
    bool (*delete)(Map *, void *key);
    void (*destroy)(Map *);
};

Map *newMap();

#endif