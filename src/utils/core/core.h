#ifndef CORE_H

#define CORE_H

#include "shared/shared.h"
#include "utils/utils.h"

#define stringsAreEqual(A, B) (strcmp(A, B) == 0)
#define stringFindChar(A, B) strchr(A, B)
#define stringFindSubstr(A, B) strstr(A, B)

size_t getFormatLength(const string format, ...);
size_t VGetFormatLength(const string format, va_list args);
string stringFromFormat(const string format, ...);
string VStringFromFormat(const string format, va_list args);
string Stringify(byte *data, size_t bytes);

#endif