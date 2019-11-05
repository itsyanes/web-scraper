#include "file.h"

bool createDirectory(string path)
{
    if (!fileExists(path))
    {
        int status = mkdir(path, 0777);

        if (status)
        {
            logger.sysError(path);
            return false;
        }
    }
    return true;
}

bool fileExists(string path)
{
    struct stat buffer;
    return stat(path, &buffer) == 0;
}