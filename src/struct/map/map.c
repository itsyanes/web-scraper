#include "map.h"

static u_int32_t MapHash(const u_int8_t *key, size_t length);
static void MapResize(Map *map);
static ArrayList *MapGetBucket(Map *map, string key);
static bool MapSizeExceedsLoadFactor(Map *map);
static void *MapSet(Map *map, string key, void *value);
static void *MapGet(Map *map, string key);
static bool MapHas(Map *map, string key);
static MapPrototype *getMapProto();
static KeyValuePair *MapFindKeyValuePairInList(ArrayList *list, string key);
static void MapForEach(Map *map, void (*callback)(string key, void *value));
static bool MapDelete(Map *map, string key, void (*hook)(string key, void *value));
static void MapFree(KeyValuePair *kv, void (*hook)(string key, void *value));
static void MapClear(Map *map, void (*hook)(string key, void *value));
static size_t MapGetBucketIndex(Map *map, string key);
static void MapDestroy(Map *map, void (*hook)(string key, void *value));

Map *newMap()
{
    Map *map = xmalloc(1, sizeof(Map));
    map->_capacityExp = MAP_CAPACITY_EXP;
    map->_buckets = xmalloc(MAP_GETSIZE(map->_capacityExp), sizeof(ArrayList *));
    map->proto = getMapProto();
    map->size = 0;
    for (size_t i = 0; i < MAP_GETSIZE(map->_capacityExp); i++)
    {
        map->_buckets[i] = newArrayList();
    }
    return map;
}

MapPrototype *getMapProto()
{
    static MapPrototype proto;
    proto.set = &MapSet;
    proto.get = &MapGet;
    proto.has = &MapHas;
    proto.forEach = &MapForEach;
    proto.delete = &MapDelete;
    proto.clear = &MapClear;
    proto.destroy = &MapDestroy;
    return &proto;
}

void *MapGet(Map *map, string key)
{
    ArrayList *l = MapGetBucket(map, key);
    KeyValuePair *kv = MapFindKeyValuePairInList(l, key);
    return kv ? kv->value : NULL;
}

void *MapSet(Map *map, string key, void *value)
{
    if (MapSizeExceedsLoadFactor(map))
    {
        MapResize(map);
    }

    ArrayList *l = MapGetBucket(map, key);
    KeyValuePair *kv = MapFindKeyValuePairInList(l, key);

    if (kv)
    {
        void *temp = kv->value;
        kv->value = value;
        return temp;
    }

    kv = xmalloc(1, sizeof(KeyValuePair));
    kv->key = key;
    kv->value = value;
    l->proto->push(l, kv);
    map->size++;
    return NULL;
}

void MapForEach(Map *map, void (*callback)(string key, void *value))
{
    for (size_t i = 0; i < MAP_GETSIZE(map->_capacityExp); i++)
    {
        ArrayList *current = map->_buckets[i];
        for (size_t j = 0; j < current->size; j++)
        {
            KeyValuePair *kv = current->proto->get(current, j);
            callback(kv->key, kv->value);
        }
    }
}

KeyValuePair *MapFindKeyValuePairInList(ArrayList *list, string key)
{
    for (size_t i = 0; i < list->size; i++)
    {
        KeyValuePair *kv = list->proto->get(list, i);
        if (strlen(kv->key) == strlen(key) && memcmp(kv->key, key, strlen(key)) == 0)
        {
            return kv;
        }
    }
    return NULL;
}

bool MapHas(Map *map, string key)
{
    ArrayList *l = MapGetBucket(map, key);
    KeyValuePair *kv = MapFindKeyValuePairInList(l, key);
    return kv ? true : false;
}

bool MapSizeExceedsLoadFactor(Map *map)
{
    return (double)(map->size + 1) / MAP_GETSIZE(map->_capacityExp) > MAP_LOAD_FACTOR;
}

ArrayList *MapGetBucket(Map *map, string key)
{
    return map->_buckets[MapGetBucketIndex(map, key)];
}

size_t MapGetBucketIndex(Map *map, string key)
{
    u_int32_t hash = MapHash((u_int8_t *)key, strlen(key));
    return hash % MAP_GETSIZE(map->_capacityExp);
}

void MapResize(Map *map)
{
    map->_capacityExp++;
    ArrayList **temp = map->_buckets;
    map->_buckets = xmalloc(MAP_GETSIZE(map->_capacityExp), sizeof(ArrayList *));
    for (size_t i = 0; i < MAP_GETSIZE(map->_capacityExp); i++)
    {
        map->_buckets[i] = newArrayList();
    }
    for (size_t i = 0; i < MAP_GETSIZE(map->_capacityExp - 1); i++)
    {
        for (size_t j = 0; j < temp[i]->size; j++)
        {
            KeyValuePair *kv = temp[i]->proto->get(temp[i], j);
            ArrayList *l = MapGetBucket(map, kv->key);
            l->proto->push(l, kv);
        }
        temp[i]->proto->destroy(temp[i], NULL);
    }
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

bool MapDelete(Map *map, string key, void (*hook)(string key, void *value))
{
    ArrayList *l = MapGetBucket(map, key);
    KeyValuePair *kv = MapFindKeyValuePairInList(l, key);

    if (!kv)
    {
        return false;
    }

    size_t index = l->proto->indexOf(l, kv);

    MapFree(kv, hook);

    ArrayList *new = newArrayList();
    for (size_t i = 0; i < l->size; i++)
    {
        if (i != index)
        {
            new->proto->push(new, l->proto->get(l, i));
        }
    }

    l->proto->destroy(l, NULL);
    map->_buckets[MapGetBucketIndex(map, key)] = new;
    map->size--;
    return true;
}

void MapFree(KeyValuePair *kv, void (*hook)(string key, void *value))
{
    if (hook)
    {
        hook(kv->key, kv->value);
    }
    free(kv);
}

void MapClear(Map *map, void (*hook)(string key, void *value))
{
    for (size_t i = 0; i < MAP_GETSIZE(map->_capacityExp); i++)
    {
        ArrayList *current = map->_buckets[i];
        for (size_t j = 0; j < current->size; j++)
        {
            KeyValuePair *kv = current->proto->get(current, j);
            MapFree(kv, hook);
        }
        current->proto->destroy(current, NULL);
        map->_buckets[i] = newArrayList();
    }
    map->size = 0;
}

void MapDestroy(Map *map, void (*hook)(string key, void *value))
{
    for (size_t i = 0; i < MAP_GETSIZE(map->_capacityExp); i++)
    {
        ArrayList *current = map->_buckets[i];
        for (size_t j = 0; j < current->size; j++)
        {
            KeyValuePair *kv = current->proto->get(current, j);
            MapFree(kv, hook);
        }
        current->proto->destroy(current, NULL);
    }
    free(map->_buckets);
    free(map);
}