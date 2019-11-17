#ifndef SCRAPER_H

#define SCRAPER_H

#include "shared/shared.h"
#include "struct/struct.h"
#include "utils/utils.h"
#include "app/download/download.h"
#include "app/html/html.h"

#define SCRAPER_HTTP "http"
#define SCRAPER_DEFAULT_URI "http://localhost/"
#define SCRAPER_DEFAULT_OUTPUT_DIR getenv("PWD")
#define SCRAPER_INDEX_NAME "index.html"
#define HTML_CONTENT_TYPE "text/html"

typedef struct Scraper Scraper;
struct Scraper
{
    string uri;
    u_int8_t maxDepth;
    string outputDir;
    string basePath;
    Map *downloaded;
    void (*options)(Scraper *scraper, string uri, u_int8_t maxDepth, string outputDir);
    void (*scrap)(Scraper *scraper);
    void (*destroy)(Scraper *scraper);
};

Scraper *newScraper();

#endif