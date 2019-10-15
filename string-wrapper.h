#ifndef STRING_WRAPPER_H

#define STRING_WRAPPER_H

#include "shared.h"
#include "utils.h"

typedef struct StringWrapper StringWrapper;
struct StringWrapper
{
    string string;
    void (*fromString)(StringWrapper *, string);
    int (*length)(StringWrapper *);
    int (*print)(StringWrapper *, FILE *);
    void (*destroy)(StringWrapper *);
    int (*reduce)(StringWrapper *, int (*)(int, char), int);
};

StringWrapper *newStringWrapper();
static void StringWrapperFromString(StringWrapper *wrapper, string str);
static int StringWrapperLength(StringWrapper *wrapper);
static int StringWrapperPrint(StringWrapper *wrapper, FILE *output);
static void StringWrapperDestroy(StringWrapper *wrapper);
static int StringWrapperReduce(StringWrapper *wrapper, int (*reducer)(int accumulator, char currentValue), int initialValue);

#endif