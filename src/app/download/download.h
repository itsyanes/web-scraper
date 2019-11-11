#ifndef DOWNLOAD_H

#define DOWNLOAD_H

#include "shared/shared.h"
#include "utils/utils.h"
#include "struct/struct.h"

typedef struct Download Download;

struct Download
{
    string fileName;
    string uri;
    string outputPath;
    Map *headers;
    Buffer *body;
    void (*start)(Download *download);
    void (*destroy)(Download *download);
};

Download *newDownload(string fileName, string uri, string outputPath);

#endif