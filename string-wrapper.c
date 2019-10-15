#include "string-wrapper.h"

StringWrapper *newStringWrapper()
{
    StringWrapper *wrapper = xmalloc(1, sizeof(StringWrapper));
    wrapper->fromString = &StringWrapperFromString;
    wrapper->length = &StringWrapperLength;
    wrapper->print = &StringWrapperPrint;
    wrapper->destroy = &StringWrapperDestroy;
    wrapper->reduce = &StringWrapperReduce;
    return wrapper;
}

void StringWrapperFromString(StringWrapper *wrapper, string str)
{
    string new = xmalloc(strlen(str) + 1, sizeof(string));
    strcpy(new, str);
    wrapper->string = new;
}

int StringWrapperLength(StringWrapper *wrapper)
{
    return strlen(wrapper->string);
}

int StringWrapperReduce(StringWrapper *wrapper, int (*reducer)(int accumulator, char currentValue), int initialValue)
{
    for (int i = 0; i < wrapper->length(wrapper); i++)
    {
        initialValue = reducer(initialValue, wrapper->string[i]);
    }
    return initialValue;
}

int StringWrapperPrint(StringWrapper *wrapper, FILE *output)
{
    return fprintf(output, "%s\n", wrapper->string);
}

void StringWrapperDestroy(StringWrapper *wrapper)
{
    free(wrapper->string);
    free(wrapper);
}