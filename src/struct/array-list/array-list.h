#ifndef ARRAY_LIST_H

#define ARRAY_LIST_H

#include "shared/shared.h"
#include "utils/alloc/alloc.h"

typedef struct ArrayListPrototype ArrayListPrototype;
typedef struct ArrayList ArrayList;

#define ARRAY_LIST_SIZE_INCREMENT 16

struct ArrayListPrototype
{
    ArrayList *(*fill)(ArrayList *list, void *value, size_t start, size_t end);
    ArrayList *(*push)(ArrayList *list, void *value);
    void *(*pop)(ArrayList *list);
    ArrayList *(*clone)(ArrayList *list);
    void *(*get)(ArrayList *list, size_t index);
    void (*set)(ArrayList *list, size_t index, void *value);
    ArrayList *(*concat)(ArrayList *list, ArrayList *list2);
    bool (*every)(ArrayList *list, bool (*predicate)(void *element, size_t index));
    ArrayList *(*filter)(ArrayList *list, bool (*predicate)(void *element, size_t index));
    void *(*find)(ArrayList *list, bool (*predicate)(void *element, size_t index));
    long (*findIndex)(ArrayList *list, bool (*predicate)(void *element, size_t index));
    void (*forEach)(ArrayList *list, void (*callback)(void *element, size_t index));
    bool (*includes)(ArrayList *list, void *element);
    long (*indexOf)(ArrayList *list, void *element);
    ArrayList *(*map)(ArrayList *list, void *(*mapper)(void *element, size_t index));
    void *(*reduce)(ArrayList *list, void *(*reducer)(void *accumulator, void *currentValue), void *initialValue);
    ArrayList *(*slice)(ArrayList *list, size_t start, size_t end);
    bool (*some)(ArrayList *list, bool (*predicate)(void *element, size_t index));
    ArrayList *(*sort)(ArrayList *list, size_t (*sortFunc)(void *element));
    void (*destroy)(ArrayList *list, void (*hook)(void *element));
};

struct ArrayList
{
    void **_list;
    size_t _blocks;
    size_t size;
    ArrayListPrototype *proto;
};

ArrayList *newArrayList();
static ArrayListPrototype *getArrayListProto();
static bool ArrayListIsAllocated(ArrayList *list);
static void ArrayListExpand(ArrayList *list);
static ArrayList *ArrayListFill(ArrayList *list, void *value, size_t start, size_t end);
static ArrayList *ArrayListPush(ArrayList *list, void *value);
static void *ArrayListPop(ArrayList *list);
static ArrayList *ArrayListClone(ArrayList *list);
static void *ArrayListGet(ArrayList *list, size_t index);
static void ArrayListSet(ArrayList *list, size_t index, void *value);
static ArrayList *ArrayListConcat(ArrayList *list, ArrayList *list2);
static bool ArrayListEvery(ArrayList *list, bool (*predicate)(void *element, size_t index));
static ArrayList *ArrayListFilter(ArrayList *list, bool (*predicate)(void *element, size_t index));
static void *ArrayListFind(ArrayList *list, bool (*predicate)(void *element, size_t index));
static long ArrayListFindIndex(ArrayList *list, bool (*predicate)(void *element, size_t index));
static void ArrayListForEach(ArrayList *list, void (*callback)(void *element, size_t index));
static void ArrayListDestroy(ArrayList *list, void (*hook)(void *element));
static bool ArrayListIncludes(ArrayList *list, void *element);
static long ArrayListIndexOf(ArrayList *list, void *element);
static ArrayList *ArrayListMap(ArrayList *list, void *(*mapper)(void *element, size_t index));
static void *ArrayListReduce(ArrayList *list, void *(*reducer)(void *accumulator, void *currentValue), void *initialValue);
static ArrayList *ArrayListSlice(ArrayList *list, size_t start, size_t end);
static bool ArrayListSome(ArrayList *list, bool (*predicate)(void *element, size_t index));
static ArrayList *ArrayListSort(ArrayList *list, size_t (*sortFunc)(void *element));

#endif