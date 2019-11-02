#include "app.h"

void init()
{
    curl_global_init(CURL_GLOBAL_DEFAULT);
    initLogger();
}