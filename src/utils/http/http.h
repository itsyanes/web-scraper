#ifndef HTTP_H

#define HTTP_H

#include "shared/shared.h"
#include "utils/utils.h"

void fetch(string uri,
           string resourceName,
           void *data,
           size_t (*callback)(string ptr, size_t size, size_t nmemb, void *userdata),
           size_t (*headerCallback)(string ptr, size_t size, size_t nmemb, void *userdata));

#endif