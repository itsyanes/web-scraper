#include "app.h"

#include "scraper/scraper.c"

void init()
{
    curl_global_init(CURL_GLOBAL_DEFAULT);
    initLogger();
    setLogger(stdout, stderr, LOGGER_ALL);
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