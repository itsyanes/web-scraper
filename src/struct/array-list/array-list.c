#include "array-list.h"

ArrayList *newArrayList()
{
    ArrayList *list = xmalloc(1, sizeof(ArrayList));
    list->_list = NULL;
    list->_blocks = 0;
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
    return list->_list != NULL;
}

void ArrayListExpand(ArrayList *list)
{
    list->_blocks += ARRAY_LIST_SIZE_INCREMENT;
    list->_list = xrealloc(list->_list, list->_blocks + ARRAY_LIST_SIZE_INCREMENT, sizeof(void *));
}

ArrayList *ArrayListFill(ArrayList *list, void *value, size_t start, size_t end)
{
    if (!ArrayListIsAllocated(list) || start > end || end > list->size)
    {
        return list;
    }

    for (int i = start; i < end; i++)
    {
        list->_list[i] = value;
    }

    return list;
}

ArrayList *ArrayListPush(ArrayList *list, void *value)
{
    if (!ArrayListIsAllocated(list))
    {
        return list;
    }

    if (list->size == list->_blocks)
    {
        ArrayListExpand(list);
    }

    list->_list[list->size] = value;
    list->size++;
    return list;
}

void *ArrayListPop(ArrayList *list)
{
    if (!ArrayListIsAllocated(list))
    {
        return NULL;
    }

    list->size--;

    return list->_list[list->size];
}

ArrayList *clone(ArrayList *list)
{
    ArrayList *new = newArrayList();

    for (int i = 0; i < list->size; i++)
    {
        new->proto->push(new, list->_list[i]);
    }

    return new;
}
