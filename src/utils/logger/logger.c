#include "logger.h"

static void LoggerInfo(const string message);
static void LoggerError(const string message);
static void LoggerSysError(const string message);

Logger logger;

void initLogger()
{
    logger.output = stdout;
    logger.errOutput = stderr;
    logger.level = LOGGER_DEFAULT_LEVEL;
    logger.info = &LoggerInfo;
    logger.error = &LoggerError;
    logger.sysError = &LoggerSysError;
}

void setLogger(FILE *output, FILE *errOutput, LoggingLevel loggingLevel)
{
    logger.errOutput = errOutput;
    logger.output = output;
    logger.level = loggingLevel;
}

void LoggerInfo(const string message)
{
    if (logger.level == LOGGER_ALL)
    {
        fprintf(logger.output, "[INFO] %s\n", message);
    }
}

void LoggerError(const string message)
{
    fprintf(logger.errOutput, "[ERROR] %s\n", message);
}

void LoggerSysError(const string message)
{
    fprintf(stderr, "[ERROR] ");
    perror(message);
}