#include "array-list.h"

ArrayList *newArrayList()
{
    ArrayList *list = xmalloc(1, sizeof(ArrayList));
    list->list = NULL;
    list->size = 0;
    list->proto = getArrayListProto();
    return list;
}

ArrayListPrototype *getArrayListProto()
{
    static ArrayListPrototype *proto = NULL;
    if (!proto)
    {
        proto = xmalloc(1, sizeof(ArrayListPrototype));
        proto->fill = &ArrayListFill;
        proto->push = &ArrayListPush;
        proto->pop = &ArrayListPop;
    }
    return proto;
}

bool ArrayListIsAllocated(ArrayList *list)
{
    return list->list != NULL;
}

void ArrayListExpand(ArrayList *list)
{
    list->size += ARRAY_LIST_SIZE_INCREMENT;
    list->list = xrealloc(list->list, list->size + ARRAY_LIST_SIZE_INCREMENT, sizeof(void *));
}

ArrayList *ArrayListFill(ArrayList *list, void *value, size_t start, size_t end)
{
    if (!ArrayListIsAllocated(list) || start > end || end > list->contained)
    {
        return list;
    }

    for (int i = start; i < end; i++)
    {
        list->list[i] = value;
    }

    return list;
}

ArrayList *ArrayListPush(ArrayList *list, void *value)
{
    if (list->contained == list->size)
    {
        ArrayListExpand(list);
    }

    list->list[list->contained] = value;
    list->contained++;
    return list;
}

void *ArrayListPop(ArrayList *list)
{
    list->contained--;
    return list->list[list->contained];
}
