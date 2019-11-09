#include "core.h"

size_t getFormatLength(const string format, ...)
{
    va_list args;
    va_start(args, format);
    size_t res = vsnprintf(NULL, 0, format, args);
    va_end(args);
    return res;
}

size_t VGetFormatLength(const string format, va_list args)
{
    return vsnprintf(NULL, 0, format, args);
}

string stringFromFormat(const string format, ...)
{
    va_list args, copy;
    va_start(args, format);
    va_copy(copy, args);
    size_t size = VGetFormatLength(format, args);
    string destination = xmalloc(size + 1, sizeof(char));
    vsprintf(destination, format, copy);
    va_end(copy);
    va_end(args);
    return destination;
}

string VStringFromFormat(const string format, va_list args)
{
    va_list copy;
    va_copy(copy, args);
    size_t size = VGetFormatLength(format, args);
    string destination = xmalloc(size + 1, sizeof(char));
    vsprintf(destination, format, copy);
    va_end(copy);
    return destination;
}

string Stringify(byte *data, size_t bytes)
{
    string new = xmalloc(bytes + 1, 1);
    memcpy(new, data, bytes);
    new[bytes] = '\0';
    return new;
}