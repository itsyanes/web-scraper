#include "app.h"

#include "scraper/scraper.c"
#include "task/task.c"

void init()
{
    curl_global_init(CURL_GLOBAL_DEFAULT);
    initLogger();
    setLogger(stdout, stderr, LOGGER_ALL);
}

void MapHook(string key, void *value) {
    free(key);
    free(value);
}

void loop()
{
    // ArrayList *tasks = getTasks();
    // ArrayList *scrapers = newArrayList();
    // Scraper *s = newScraper();
    // s->options(s, "https://developer.mozilla.org/fr/docs/Web/HTTP/CORS", 0, getenv("PWD"));
    // scrapers->proto->push(scrapers, s);
    // Task *t = newTask(10, scrapers);
    // t->start(t);
    // int status;
    // wait(&status);
    // t->stop(t);
    Buffer *b = newBuffer();
    Map *m = newMap();
    HttpFetch("https://example.com", "index.html", b, m);
    string t = m->proto->get(m, "content-type");
    if (t) {
        puts(t);
        string u = Stringify(b->data, b->size);
        puts(u);
        free(u);
    }
    b->proto->destroy(b);
    m->proto->destroy(m, MapHook);
}

// ArrayList *getTasks()
// {
// }