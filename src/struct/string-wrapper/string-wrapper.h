#ifndef STRING_WRAPPER_H

#define STRING_WRAPPER_H

#include "shared/shared.h"
#include "utils/alloc.h"

typedef struct StringPrototype StringPrototype;
typedef struct StringWrapper StringWrapper;

struct StringWrapper
{
    string string;
    StringPrototype *proto;
};

struct StringPrototype
{
    int (*length)(StringWrapper *);
    int (*print)(StringWrapper *, FILE *);
    void (*destroy)(StringWrapper *);
    int (*reduce)(StringWrapper *, int (*)(int, char), int);
};

StringWrapper *wrapString(string str);
static StringPrototype *getStringProto();
static int StringWrapperLength(StringWrapper *wrapper);
static int StringWrapperPrint(StringWrapper *wrapper, FILE *output);
static void StringWrapperDestroy(StringWrapper *wrapper);
static int StringWrapperReduce(StringWrapper *wrapper, int (*reducer)(int accumulator, char currentValue), int initialValue);

#endif