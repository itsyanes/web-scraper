#ifndef HTTP_H

#define HTTP_H

#include "shared/shared.h"
#include "utils/utils.h"
#include "struct/buffer/buffer.h"
#include "struct/map/map.h"

void HttpDownloadFile(string uri, string resourceName, string outputDir, Map *headers);
void HttpFetch(string uri, string resourceName, Buffer *body, Map *headers);

#endif