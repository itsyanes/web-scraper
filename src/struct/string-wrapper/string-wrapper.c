#include "string-wrapper.h"

String *newString()
{
    String *wrapper = xmalloc(1, sizeof(String));
    wrapper->string = "";
    wrapper->proto = getStringProto();
    return wrapper;
}

String *wrapString(string str)
{
    String *wrapper = xmalloc(1, sizeof(String));
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
        proto->length = &StringLength;
        proto->destroy = &StringDestroy;
        proto->reduce = &StringReduce;
        proto->build = &StringBuild;
    }
    return proto;
}

bool StringIsAllocated(String *wrapper)
{
    return wrapper->string && strlen(wrapper->string) > 0;
}

int StringLength(String *wrapper)
{
    return StringIsAllocated(wrapper) ? strlen(wrapper->string) : 0;
}

int StringReduce(String *wrapper, int (*reducer)(int accumulator, char currentValue), int initialValue)
{
    for (int i = 0; i < wrapper->proto->length(wrapper); i++)
    {
        initialValue = reducer(initialValue, wrapper->string[i]);
    }
    return initialValue;
}

String *StringBuild(String *wrapper, string format, ...)
{
    va_list args, copy;
    va_start(args, format);
    va_copy(copy, args);
    size_t size = vsnprintf(NULL, 0, format, args);
    string buffer = xmalloc(size + 1, sizeof(char));
    vsprintf(buffer, format, copy);
    va_end(copy);
    va_end(args);

    if (StringIsAllocated(wrapper))
    {
        free(wrapper->string);
    }

    wrapper->string = buffer;
    return wrapper;
}

void StringDestroy(String *wrapper)
{
    if (StringIsAllocated(wrapper))
    {
        free(wrapper->string);
    }

    free(wrapper);
}