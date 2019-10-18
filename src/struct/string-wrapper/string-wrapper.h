#ifndef STRING_WRAPPER_H

#define STRING_WRAPPER_H

#include "shared/shared.h"
#include "utils/alloc/alloc.h"

typedef struct StringPrototype StringPrototype;
typedef struct StringWrapper StringWrapper;

struct StringWrapper
{
    string string;
    StringPrototype *proto;
};

struct StringPrototype
{
    int (*length)(StringWrapper *wrapper);
    int (*print)(StringWrapper *wrapper, FILE *output);
    void (*destroy)(StringWrapper *wrapper);
    int (*reduce)(StringWrapper *wrapper, int (*reducer)(int accumulator, char currentValue), int initialValue);
};

StringWrapper *wrapString(string str);
static StringPrototype *getStringProto();
static int StringWrapperLength(StringWrapper *wrapper);
static int StringWrapperPrint(StringWrapper *wrapper, FILE *output);
static void StringWrapperDestroy(StringWrapper *wrapper);
static int StringWrapperReduce(StringWrapper *wrapper, int (*reducer)(int accumulator, char currentValue), int initialValue);

#endif