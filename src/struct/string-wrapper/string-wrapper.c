#include "string-wrapper.h"

StringWrapper *wrapString(string str)
{
    StringWrapper *wrapper = xmalloc(1, sizeof(StringWrapper));
    string new = xmalloc(strlen(str) + 1, sizeof(string));
    strcpy(new, str);
    wrapper->string = new;
    wrapper->proto = getStringProto();
    return wrapper;
}

StringPrototype *getStringProto()
{
    static StringPrototype *proto = NULL;
    if (!proto)
    {
        proto = xmalloc(1, sizeof(StringPrototype));
        proto->length = &StringWrapperLength;
        proto->print = &StringWrapperPrint;
        proto->destroy = &StringWrapperDestroy;
        proto->reduce = &StringWrapperReduce;
    }
    return proto;
}

int StringWrapperLength(StringWrapper *wrapper)
{
    return strlen(wrapper->string);
}

int StringWrapperReduce(StringWrapper *wrapper, int (*reducer)(int accumulator, char currentValue), int initialValue)
{
    for (int i = 0; i < strlen(wrapper->string); i++)
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