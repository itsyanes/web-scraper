#ifndef SHARED_H

#define SHARED_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>

typedef char byte;
typedef char *string;

#ifndef __MINGW32__

typedef unsigned long size_t;

#endif

#endif