#ifndef MAP_H

#define MAP_H

#include "utils/utils.h"
#include "struct/struct.h"
#include "shared/shared.h"

#define MAP_LOAD_FACTOR 0.75f
#define MAP_CAPACITY_EXP 4
#define MAP_GETSIZE(A) ((size_t)pow(2, A))

typedef struct KeyValuePair KeyValuePair;
struct KeyValuePair
{
    string key;
    void *value;
};

typedef struct Map Map;
typedef struct MapPrototype MapPrototype;

struct MapPrototype
{
    void *(*get)(Map *map, string key);
    void *(*set)(Map *map, string key, void *value);
    bool (*has)(Map *map, string key);
    void (*forEach)(Map *map, void (*callback)(string key, void *value));
    void (*clear)(Map *map);
    bool (*delete)(Map *map, string key);
    void (*destroy)(Map *map, void (*hook)(string key, void *value));
};

struct Map
{
    u_int8_t _capacityExp;
    ArrayList **_buckets;
    size_t size;
    MapPrototype *proto;
};

Map *newMap();

#endif