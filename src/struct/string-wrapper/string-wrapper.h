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
    size_t (*length)(String *wrapper);
    void (*destroy)(String *wrapper);
    String *(*build)(String *wrapper, string format, ...);
    char (*charAt)(String *wrapper, size_t index);
    int (*indexOf)(String *wrapper, char element);
    int (*lastIndexOf)(String *wrapper, char element);
    String *(*concat)(String *wrapper, string source);
    bool (*startsWith)();
    bool (*endsWith)();
    bool (*includes)();
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
static size_t StringLength(String *wrapper);
static String *StringBuild(String *wrapper, string format, ...);
static char StringCharAt(String *wrapper, size_t index);
static int StringIndexOf(String *wrapper, char element);
static int StringLastIndexOf(String *wrapper, char element);
static String *StringConcat(String *wrapper, string source);
static void StringDestroy(String *wrapper);

#endif