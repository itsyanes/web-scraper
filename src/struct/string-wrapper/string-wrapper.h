#ifndef STRING_WRAPPER_H

#define STRING_WRAPPER_H

#include "shared/shared.h"
#include "utils/alloc/alloc.h"

typedef struct StringPrototype StringPrototype;
typedef struct StringWrapper String;

struct StringWrapper
{
    string string;
    StringPrototype *proto;
};

struct StringPrototype
{
    int (*length)(String *wrapper);
    void (*destroy)(String *wrapper);
    int (*reduce)(String *wrapper, int (*reducer)(int accumulator, char currentValue), int initialValue);
    String *(*build)(String *wrapper, string format, ...);
    char (*charAt)();
    void (*concat)(String *wrapper, ...);
    void (*endsWith)();
    void (*startsWith)();
    void (*includes)();
    void (*indexOf)();
    void (*lastIndexOf)();
    void (*replace)();
    void (*slice)();
    void (*split)();
    void (*subString)();
    void (*toString)();
};

String *newString();
String *wrapString(string str);
static StringPrototype *getStringProto();
static bool StringIsAllocated(String *wrapper);
static int StringLength(String *wrapper);
static int StringReduce(String *wrapper, int (*reducer)(int accumulator, char currentValue), int initialValue);
static String *StringBuild(String *wrapper, string format, ...);
static void StringDestroy(String *wrapper);

#endif