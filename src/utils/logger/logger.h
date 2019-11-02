#ifndef LOGGER_H

#define LOGGER_H

#include "shared/shared.h"

enum LoggingLevel
{
    LOGGER_DEFAULT_LEVEL = 1,
    LOGGER_ALL = 0,
    LOGGER_ERROR = 1
};
typedef enum LoggingLevel LoggingLevel;

struct Logger
{
    FILE *output;
    FILE *errOutput;
    LoggingLevel level;
    void (*info)(const char *message);
    void (*error)(const char *message);
};
typedef struct Logger Logger;

extern Logger logger;

void initLogger();
void setLogger(FILE *output, FILE *errOutput, LoggingLevel loggingLevel);

#endif