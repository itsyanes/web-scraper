#ifndef HTTP_H

#define HTTP_H

#include "shared/shared.h"
#include "utils/utils.h"
#include "struct/struct.h"

void downloadFile(string uri, string resourceName, string outputDir, Map *headers);

#endif