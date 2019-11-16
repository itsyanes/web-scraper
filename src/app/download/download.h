#ifndef DOWNLOAD_H

#define DOWNLOAD_H

#include "shared/shared.h"
#include "utils/utils.h"
#include "struct/struct.h"

#define DOWNLOAD_HEADER_MIME_TYPE "content-type"

typedef struct Download Download;

struct Download
{
    string fileName;
    string uri;
    string outputPath;
    Map *headers;
    string body;
    bool status;
    void (*start)(Download *download);
    string (*getMimeType)(Download *download);
    void (*destroy)(Download *download);
};

Download *newDownload(string fileName, string uri, string outputPath);

#endif