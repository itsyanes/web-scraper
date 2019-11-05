#ifndef HTTP_H

#define HTTP_H

#include "shared/shared.h"
#include "utils/utils.h"

void fetch(string uri,
           char *resourceName,
           void *data,
           size_t (*callback)(char *ptr, size_t size, size_t nmemb, void *userdata),
           size_t (*headerCallback)(char *ptr, size_t size, size_t nmemb, void *userdata));

#endif