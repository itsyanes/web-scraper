#ifndef MAP_H

#define MAP_H

#include "utils/alloc/alloc.h"
#include "shared/shared.h"

typedef struct Map Map;
struct Map
{
    void *(*get)(Map *map, void *key);
    void (*set)(Map *map, void *key, void *value);
    bool (*has)(Map *map, void *key);
    void (*forEach)(Map *map, void (*callback)(void *key, void *value));
    void (*clear)(Map *map);
    bool (*delete)(Map *map, void *key);
    void (*destroy)(Map *map);
};

Map *newMap();

#endif