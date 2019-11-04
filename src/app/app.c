#include "app.h"

#include "scraper/scraper.c"

void init()
{
    curl_global_init(CURL_GLOBAL_DEFAULT);
    initLogger();
}

void loop()
{
    // ArrayList *tasks = getTasks();
    Scraper *s = newScraper();
    s->scrap(s);
}

// ArrayList *getTasks()
// {
// }