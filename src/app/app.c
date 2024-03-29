#include "app.h"

#include "scraper/scraper.c"
#include "task/task.c"
#include "download/download.c"
#include "html/html.c"
#include "config/config.c"

void init()
{
    curl_global_init(CURL_GLOBAL_DEFAULT);
    initLogger();
    setLogger(stdout, stderr, LOGGER_ALL);
}

void loop()
{
    // ArrayList *tasks = getTasks();
    ArrayList *scrapers = newArrayList();
    Scraper *s = newScraper();
    s->options(s, "http://localhost/", 3, getenv("PWD"));
    scrapers->proto->push(scrapers, s);
    Task *t = newTask(2, scrapers);
    t->start(t);
    int status;
    wait(&status);
    t->stop(t);
}

// ArrayList *getTasks()
// {
// }