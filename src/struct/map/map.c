#include "map.h"

Map *newMap()
{
    Map* map = xmalloc(1, sizeof(Map));
    return map;
}