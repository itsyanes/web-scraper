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
        proto->add = &ArrayListAdd;
        proto->delete = &ArrayListDelete;
        proto->deleteAt = &ArrayListDeleteAt;
    }
    return proto;
}

void ArrayListExpand(ArrayList *list)
{
    list->list = xrealloc(list->list, list->size + 16, sizeof(void *));
}

ArrayList *ArrayListFill(ArrayList *list, void *value, size_t start, size_t end)
{
    return list;
}

ArrayList *ArrayListAdd(ArrayList *list, void *value)
{
    if (list->contained == list->size)
    {
        ArrayListExpand(list);
    }
    return list;
}

ArrayList *ArrayListDelete(ArrayList *list, void *value)
{
    return list;
}

ArrayList *ArrayListDeleteAt(ArrayList *list, size_t index)
{
    return list;
}
