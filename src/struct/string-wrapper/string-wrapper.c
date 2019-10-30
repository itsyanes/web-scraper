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
        proto->replace = &StringReplace;
        proto->reverse = &StringReverse;
        proto->trim = &StringTrim;
        proto->slice = &StringSlice;
        proto->toString = &StringToString;
        proto->clone = &StringClone;
        proto->search = &StringSearch;
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

long StringIndexOf(String *wrapper, char element)
{
    for (size_t i = 0; i < wrapper->proto->length(wrapper); i++)
    {
        if (wrapper->string[i] == element)
        {
            return i;
        }
    }
    return -1;
}

long StringLastIndexOf(String *wrapper, char element)
{
    long occurence = -1;
    for (size_t i = 0; i < wrapper->proto->length(wrapper); i++)
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
    if (!StringIsAllocated(wrapper))
    {
        return wrapper;
    }

    size_t size = wrapper->proto->length(wrapper) + strlen(source) + 1;
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
    return strstr(wrapper->string, comparator) == wrapper->string + (wrapper->proto->length(wrapper) - strlen(comparator));
}

bool StringIncludes(String *wrapper, string comparator)
{
    return strstr(wrapper->string, comparator) ? true : false;
}

String *StringReplace(String *wrapper, string substr, string newSubstr)
{
    if (!StringIsAllocated(wrapper))
    {
        return wrapper;
    }

    size_t destLength = wrapper->proto->length(wrapper);
    size_t substrLength = strlen(substr);
    size_t newSubstrLength = strlen(newSubstr);
    size_t occurenceCount = 0;
    string occurence = wrapper->string;

    while ((occurence = strstr(occurence, substr)))
    {
        occurenceCount++;
        occurence++;
    }

    size_t nbBlocks = destLength - substrLength * occurenceCount + newSubstrLength * occurenceCount + 1;
    string newString = xmalloc(nbBlocks, sizeof(char));

    string head = wrapper->string;
    string tail = wrapper->string;
    string cursor = newString;

    while ((head = strstr(head, substr)))
    {
        strncpy(cursor, tail, head - tail);
        cursor += head - tail;
        strcpy(cursor, newSubstr);
        cursor += newSubstrLength;
        head++;
        tail = head;
    }

    strcpy(cursor, tail);

    free(wrapper->string);
    wrapper->string = newString;

    return wrapper;
}

String *StringReverse(String *wrapper)
{
    if (!StringIsAllocated(wrapper))
    {
        return wrapper;
    }

    string newString = xmalloc(wrapper->proto->length(wrapper) + 1, sizeof(char));

    for (size_t i = 0; i < wrapper->proto->length(wrapper); i++)
    {
        newString[i] = wrapper->string[wrapper->proto->length(wrapper) - 1 - i];
    }
    newString[wrapper->proto->length(wrapper)] = '\0';

    free(wrapper->string);
    wrapper->string = newString;

    return wrapper;
}

String *StringTrim(String *wrapper)
{
    size_t start = 0;
    size_t end = wrapper->proto->length(wrapper) - 1;

    for (size_t i = 0; i < wrapper->proto->length(wrapper); i++)
    {
        if (wrapper->string[i] > 33 && wrapper->string[i] < 127)
        {
            break;
        }
        start++;
    }

    for (size_t i = wrapper->proto->length(wrapper) - 1; i > 0; i--)
    {
        if (wrapper->string[i] > 33 && wrapper->string[i] < 127)
        {
            break;
        }
        end--;
    }

    String *new = wrapper->proto->slice(wrapper, start, end + 1);
    strcpy(wrapper->string, new->string);
    new->proto->destroy(new);

    return wrapper;
}

String *StringSlice(String *wrapper, size_t start, size_t end)
{
    if (!StringIsAllocated(wrapper) || start >= wrapper->proto->length(wrapper) || end <= start)
    {
        return newString();
    }

    if (end > wrapper->proto->length(wrapper))
    {
        end = wrapper->proto->length(wrapper);
    }

    String *newWrapper = newString();
    string new = xmalloc(end - start + 1, sizeof(char));

    strncpy(new, wrapper->string + start, end - start);
    new[end - start] = '\0';

    newWrapper->string = new;
    return newWrapper;
}

string StringToString(String *wrapper)
{
    if (!StringIsAllocated(wrapper))
    {
        return xcalloc(1, sizeof(char));
    }

    string str = wrapper->string;
    free(wrapper);

    return str;
}

String *StringClone(String *wrapper)
{
    if (!StringIsAllocated(wrapper))
    {
        return newString();
    }

    return wrapString(wrapper->string);
}

String *StringSearch(String *wrapper, string pattern)
{
    string occurence = strstr(wrapper->string, pattern);
    return occurence ? wrapString(occurence) : newString();
}

void StringDestroy(String *wrapper)
{
    if (StringIsAllocated(wrapper))
    {
        free(wrapper->string);
    }

    free(wrapper);
}