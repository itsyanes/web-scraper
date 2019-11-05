#ifndef MAP_H

#define MAP_H

#include "utils/utils.h"
#include "struct/struct.h"
#include "shared/shared.h"

#define MAP_LOAD_FACTOR 0.75f
#define MAP_CAPACITY_EXP 4
#define MAP_GETSIZE(A) ((int)pow(2, A))

typedef struct Map Map;
struct Map
{
    size_t _capacity;
    ArrayList *_buckets;
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