#ifndef STRING_WRAPPER_H

#define STRING_WRAPPER_H

#include "shared/shared.h"
#include "utils/alloc/alloc.h"
#include "struct/array-list/array-list.h"

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
    bool (*startsWith)(String *wrapper, string comparator);
    bool (*endsWith)(String *wrapper, string comparator);
    bool (*includes)(String *wrapper, string comparator);
    String *(*replace)(String *wrapper, string substr, string newSubstr);
    String *(*reverse)(String *wrapper);
    String *(*trim)(String *wrapper);
    String *(*slice)(String *wrapper, size_t start, size_t end);
    ArrayList *(*split)();
    void (*subString)();
    void (*toString)();
    void (*clone)();
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
static bool StringStartsWith(String *wrapper, string comparator);
static bool StringEndsWith(String *wrapper, string comparator);
static bool StringIncludes(String *wrapper, string comparator);
static String *StringReplace(String *wrapper, string substr, string newSubstr);
static String *StringReverse(String *wrapper);
static String *StringTrim(String *wrapper);
static String *StringSlice(String *wrapper, size_t start, size_t end);
static void StringDestroy(String *wrapper);

#endif