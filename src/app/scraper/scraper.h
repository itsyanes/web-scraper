#ifndef SCRAPER_H

#define SCRAPER_H

#include "shared/shared.h"
#include "struct/struct.h"

#define SCRAPER_DEFAULT_URI "https://example.com"
#define SCRAPER_DEFAULT_OUTPUT_DIR getenv("PWD")

typedef struct Scraper Scraper;
struct Scraper
{
    string uri;
    u_int8_t maxDepth;
    string outputDir;
    void (*options)(Scraper *scraper, string uri, u_int8_t maxDepth, string outputDir);
    void (*scrap)(Scraper *scraper);
};

Scraper *newScraper();

#endif