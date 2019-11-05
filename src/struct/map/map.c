#include "map.h"

Map *newMap()
{
    Map *map = xmalloc(1, sizeof(Map));
    map->_capacity = MAP_CAPACITY_EXP;
    map->_buckets = xmalloc(MAP_GETSIZE(map->_capacity), sizeof(ArrayList));
    return map;
}

void MapResize()
{
}

u_int32_t MapHash(const u_int8_t *key, size_t length)
{
    size_t i = 0;
    u_int32_t hash = 0;
    while (i != length)
    {
        hash += key[i++];
        hash += hash << 10;
        hash ^= hash >> 6;
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    return hash;
}

void MapRehash(Map *map)
{
}