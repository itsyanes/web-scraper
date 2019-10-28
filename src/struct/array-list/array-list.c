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
        proto->clone = &ArrayListClone;
        proto->get = &ArrayListGet;
        proto->set = &ArrayListSet;
        proto->concat = &ArrayListConcat;
        proto->every = &ArrayListEvery;
        proto->filter = &ArrayListFilter;
        proto->destroy = &ArrayListDestroy;
        proto->forEach = &ArrayListForEach;
        proto->find = &ArrayListFind;
        proto->findIndex = &ArrayListFindIndex;
        proto->includes = &ArrayListIncludes;
        proto->indexOf = &ArrayListIndexOf;
        proto->map = &ArrayListMap;
        proto->reduce = &ArrayListReduce;
        proto->slice = &ArrayListSlice;
        proto->some = &ArrayListSome;
        proto->sort = &ArrayListSort;
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

    ArrayList *new = list->proto->clone(list);

    for (int i = start; i < end; i++)
    {
        new->proto->set(new, i, value);
    }

    return new;
}

ArrayList *ArrayListPush(ArrayList *list, void *value)
{
    if (list->size == list->_blocks)
    {
        ArrayListExpand(list);
    }

    list->size++;
    list->proto->set(list, list->size - 1, value);

    return list;
}

void *ArrayListPop(ArrayList *list)
{
    if (!ArrayListIsAllocated(list))
    {
        return NULL;
    }

    void *element = list->proto->get(list, list->size - 1);
    list->size--;

    return element;
}

ArrayList *ArrayListClone(ArrayList *list)
{
    ArrayList *new = newArrayList();

    for (int i = 0; i < list->size; i++)
    {
        new->proto->push(new, list->proto->get(list, i));
    }

    return new;
}

void *ArrayListGet(ArrayList *list, size_t index)
{
    if (!ArrayListIsAllocated(list) || index >= list->size)
    {
        return NULL;
    }

    return list->_list[index];
}

void ArrayListSet(ArrayList *list, size_t index, void *value)
{
    if (!ArrayListIsAllocated(list) || index >= list->size)
    {
        return;
    }

    list->_list[index] = value;
}

ArrayList *ArrayListConcat(ArrayList *list, ArrayList *list2)
{
    ArrayList *new = list->proto->clone(list);

    for (int i = 0; i < list2->size; i++)
    {
        new->proto->push(new, list2->proto->get(list2, i));
    }

    return new;
}

bool ArrayListEvery(ArrayList *list, bool (*predicate)(void *element, size_t index))
{
    for (int i = 0; i < list->size; i++)
    {
        if (!predicate(list->proto->get(list, i), i))
        {
            return false;
        }
    }
    return true;
}

ArrayList *ArrayListFilter(ArrayList *list, bool (*predicate)(void *element, size_t index))
{
    ArrayList *new = newArrayList();
    for (int i = 0; i < list->size; i++)
    {
        if (predicate(list->proto->get(list, i), i))
        {
            new->proto->push(new, list->proto->get(list, i));
        }
    }
    return new;
}

void *ArrayListFind(ArrayList *list, bool (*predicate)(void *element, size_t index))
{
    for (int i = 0; i < list->size; i++)
    {
        if (predicate(list->proto->get(list, i), i))
        {
            return list->proto->get(list, i);
        }
    }
    return NULL;
}

long ArrayListFindIndex(ArrayList *list, bool (*predicate)(void *element, size_t index))
{
    for (int i = 0; i < list->size; i++)
    {
        if (predicate(list->proto->get(list, i), i))
        {
            return i;
        }
    }
    return -1;
}

void ArrayListForEach(ArrayList *list, void (*callback)(void *element, size_t index))
{
    for (int i = 0; i < list->size; i++)
    {
        callback(list->proto->get(list, i), i);
    }
}

bool ArrayListIncludes(ArrayList *list, void *element)
{
    for (int i = 0; i < list->size; i++)
    {
        if (list->proto->get(list, i) == element)
        {
            return true;
        }
    }
    return false;
}

long ArrayListIndexOf(ArrayList *list, void *element)
{
    for (int i = 0; i < list->size; i++)
    {
        if (list->proto->get(list, i) == element)
        {
            return i;
        }
    }
    return -1;
}

ArrayList *ArrayListMap(ArrayList *list, void *(*mapper)(void *element, size_t index))
{
    ArrayList *res = newArrayList();

    for (int i = 0; i < list->size; i++)
    {
        res->proto->push(res, mapper(list->proto->get(list, i), i));
    }

    return res;
}

void *ArrayListReduce(ArrayList *list, void *(*reducer)(void *accumulator, void *currentValue), void *initialValue)
{
    for (int i = 0; i < list->size; i++)
    {
        initialValue = reducer(initialValue, list->proto->get(list, i));
    }

    return initialValue;
}

ArrayList *ArrayListSlice(ArrayList *list, size_t start, size_t end)
{
    if (!ArrayListIsAllocated(list) || start > end || end > list->size)
    {
        return list;
    }

    ArrayList *new = newArrayList();

    for (int i = start; i < end; i++)
    {
        new->proto->push(new, list->proto->get(list, i));
    }

    return new;
}

bool ArrayListSome(ArrayList *list, bool (*predicate)(void *element, size_t index))
{
    return true;
}

ArrayList *ArrayListSort(ArrayList *list, size_t (*sortFunc)(void *element))
{
    return list;
}

void ArrayListDestroy(ArrayList *list, void (*hook)(void *element))
{
    if (hook)
    {
        for (int i = 0; i < list->size; i++)
        {
            hook(list->proto->get(list, i));
        }
    }

    if (ArrayListIsAllocated(list))
    {
        free(list->_list);
    }

    free(list);
}
