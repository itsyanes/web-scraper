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
    bool (*every)(ArrayList *list, bool (*predicate)(void *element, size_t index, void *data), void *data);
    ArrayList *(*filter)(ArrayList *list, bool (*predicate)(void *element, size_t index, void *data), void *data);
    void *(*find)(ArrayList *list, bool (*predicate)(void *element, size_t index, void *data), void *data);
    long (*findIndex)(ArrayList *list, bool (*predicate)(void *element, size_t index, void *data), void *data);
    void (*forEach)(ArrayList *list, void (*callback)(void *element, size_t index, void *data), void *data);
    bool (*includes)(ArrayList *list, void *element);
    long (*indexOf)(ArrayList *list, void *element);
    ArrayList *(*map)(ArrayList *list, void *(*mapper)(void *element, size_t index, void *data), void *data);
    void *(*reduce)(ArrayList *list, void *(*reducer)(void *accumulator, void *currentValue, void *data), void *initialValue, void *data);
    ArrayList *(*slice)(ArrayList *list, size_t start, size_t end);
    bool (*some)(ArrayList *list, bool (*predicate)(void *element, size_t index, void *data), void *data);
    ArrayList *(*sort)(ArrayList *list, size_t (*sortFunc)(void *element, void *data), void *data);
    ArrayList *(*flat)(ArrayList *list);
    ArrayList *(*flatMap)(ArrayList *list, void *(*mapper)(void *element, size_t index, void *data), void *data);
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

#endif