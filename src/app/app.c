#include "app.h"

void init()
{
    curl_global_init(CURL_GLOBAL_DEFAULT);
    initLogger();
}

void loop()
{
    // ArrayList *tasks = getTasks();
    Scraper *s = newScraper();
}

// ArrayList *getTasks()
// {
// }