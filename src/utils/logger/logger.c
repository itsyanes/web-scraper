#include "logger.h"

static void LoggerInfo(const char *message);
static void LoggerError(const char *message);

Logger logger;

void initLogger()
{
    logger.output = stdout;
    logger.errOutput = stderr;
    logger.level = LOGGER_DEFAULT_LEVEL;
    logger.info = &LoggerInfo;
    logger.error = &LoggerError;
}

void setLogger(FILE *output, FILE *errOutput, LoggingLevel loggingLevel)
{
    logger.errOutput = errOutput;
    logger.output = output;
    logger.level = loggingLevel;
}

void LoggerInfo(const char *message)
{
    if (logger.level == LOGGER_ALL)
    {
        fprintf(logger.output, "[INFO] %s\n", message);
    }
}

void LoggerError(const char *message)
{
    fprintf(logger.errOutput, "[ERROR] %s\n", message);
}