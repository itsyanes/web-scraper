#include "scraper.h"

static void ScraperChangeOptions(Scraper *scraper, string uri, u_int8_t maxDepth, string outputDir);

Scraper *newScraper()
{
    Scraper *scraper = xmalloc(1, sizeof(Scraper));
    scraper->uri = stringFromFormat("%s", SCRAPER_DEFAULT_URI);
    scraper->maxDepth = 0;
    scraper->outputDir = stringFromFormat("%s", SCRAPER_DEFAULT_OUTPUT_DIR);
    scraper->options = &ScraperChangeOptions;
    return scraper;
}

void ScraperChangeOptions(Scraper *scraper, string uri, u_int8_t maxDepth, string outputDir)
{
    scraper->uri = uri;
    scraper->maxDepth = maxDepth;
    scraper->outputDir = outputDir;
}

void scrap(Scraper *scraper)
{
    String *basePath = newString();
    String *currentFilePath = newString();
    string domainName = getDomainName(scraper->uri);
    basePath->proto->build(basePath, "%s/%s", scraper->outputDir, domainName);
    createDirectory(basePath);
    free(domainName);
    currentFilePath->proto->build(currentFilePath, "%s/%s", basePath, "index.html");
    fetch(scraper->uri, currentFilePath, writeFile);
    for (u_int8_t i = 0; i < scraper->maxDepth; i++)
    {
    }
    basePath->proto->destroy(basePath);
    currentFilePath->proto->destroy(currentFilePath);
}

size_t writeFile(char *ptr, size_t size, size_t nmemb, void *userdata)
{
    size_t size = 0;
    FILE *f = fopen((char *)userdata, "w");
    if (f)
    {
        size = fputs(ptr, f);
        fclose(f);
    }
    else
    {
        perror("[ERROR]");
    }
    return size;
}

void createDirectory(string path)
{
    int status = mkdir(path, 0777);
    if (status)
    {
        perror("[ERROR]");
    }
}

string getDomainName(string uri)
{
    String *wrapper = wrapString(uri);
    return uri;
}