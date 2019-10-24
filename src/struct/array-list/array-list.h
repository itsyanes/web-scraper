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
    ArrayList *(*concat)(ArrayList *list, ArrayList *list2);
    bool (*every)(ArrayList *list, bool (*test)(void *element, size_t index));
    ArrayList *(*filter)(ArrayList *list, bool (*test)(void *element, size_t index));
    void *(*find)(ArrayList *list, bool (*test)(void *element, size_t index));
    size_t (*findIndex)(ArrayList *list, bool (*test)(void *element, size_t index));
    void (*forEach)(ArrayList *list, void (*callback)(void *element, size_t index));
    bool (*includes)(ArrayList *list, void *element);
    size_t (*indexOf)(ArrayList *list, void *element);
    ArrayList *(*map)(ArrayList *list, void *(*callback)(void *element, size_t index));
    void *(*reduce)(ArrayList *list, void *(*reducer)(void *accumulator, void *currentValue), void *initialValue);
    ArrayList *(*slice)(ArrayList *list, size_t start, size_t end);
    bool (*some)(ArrayList *list, bool (*test)(void *element, size_t index));
    ArrayList *(*sort)(ArrayList *list, size_t (*sortFunc)(void *element));
    ArrayList *(*clone)(ArrayList *list);
    void (*destroy)(ArrayList *list, void (*hook)(void *element));
};

struct ArrayList
{
    void **list;
    size_t size;
    size_t contained;
    ArrayListPrototype *proto;
};

ArrayList *newArrayList();
static ArrayListPrototype *getArrayListProto();
static bool ArrayListIsAllocated(ArrayList *list);
static void ArrayListExpand(ArrayList *list);
static ArrayList *ArrayListFill(ArrayList *list, void *value, size_t start, size_t end);
static ArrayList *ArrayListPush(ArrayList *list, void *value);
static void *ArrayListPop(ArrayList *list);

#endif