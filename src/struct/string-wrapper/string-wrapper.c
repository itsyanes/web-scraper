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
        proto->build = &StringBuild;
        proto->charAt = &StringCharAt;
        proto->indexOf = &StringIndexOf;
        proto->lastIndexOf = &StringLastIndexOf;
        proto->concat = &StringConcat;
        proto->includes = &StringIncludes;
        proto->startsWith = &StringStartsWith;
        proto->endsWith = &StringEndsWith;
    }
    return proto;
}

bool StringIsAllocated(String *wrapper)
{
    return wrapper->string && strlen(wrapper->string) > 0;
}

size_t StringLength(String *wrapper)
{
    return StringIsAllocated(wrapper) ? strlen(wrapper->string) : 0;
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

char StringCharAt(String *wrapper, size_t index)
{
    if (wrapper->proto->length(wrapper) <= index)
    {
        return 0;
    }

    return wrapper->string[index];
}

int StringIndexOf(String *wrapper, char element)
{
    for (int i = 0; i < wrapper->proto->length(wrapper); i++)
    {
        if (wrapper->string[i] == element)
        {
            return i;
        }
    }
    return -1;
}

int StringLastIndexOf(String *wrapper, char element)
{
    int occurence = -1;
    for (int i = 0; i < wrapper->proto->length(wrapper); i++)
    {
        if (wrapper->string[i] == element)
        {
            occurence = i;
        }
    }
    return occurence;
}

String *StringConcat(String *wrapper, string source)
{
    size_t size = strlen(wrapper->string) + strlen(source) + 1;
    string buffer = xmalloc(size, sizeof(char));
    strcpy(buffer, wrapper->string);
    strcat(buffer, source);

    if (StringIsAllocated(wrapper))
    {
        free(wrapper->string);
    }

    wrapper->string = buffer;
    return wrapper;
}

bool StringStartsWith(String *wrapper, string comparator)
{
    return strstr(wrapper->string, comparator) == wrapper->string;
}

bool StringEndsWith(String *wrapper, string comparator)
{
    return strstr(wrapper->string, comparator) == wrapper->string + (strlen(wrapper->string) - strlen(comparator));
}

bool StringIncludes(String *wrapper, string comparator)
{
    return strstr(wrapper->string, comparator) ? true : false;
}

void StringDestroy(String *wrapper)
{
    if (StringIsAllocated(wrapper))
    {
        free(wrapper->string);
    }

    free(wrapper);
}