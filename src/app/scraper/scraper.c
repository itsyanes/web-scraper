#include "scraper.h"

static void ScraperChangeOptions(Scraper *scraper, string uri, u_int8_t maxDepth, string outputDir);
static void ScraperScrap(Scraper *scraper);
static string ScraperGetDomainName(string uri);
static void ScraperDestroy(Scraper *scraper);
static void ScraperFreeHeaders(string key, void *value);
static string ScraperGetBasePath(string outputDir, string uri);

Scraper *newScraper()
{
    Scraper *scraper = xmalloc(1, sizeof(Scraper));
    scraper->uri = stringFromFormat("%s", SCRAPER_DEFAULT_URI);
    scraper->maxDepth = 0;
    scraper->outputDir = stringFromFormat("%s", SCRAPER_DEFAULT_OUTPUT_DIR);
    scraper->basePath = ScraperGetBasePath(scraper->outputDir, scraper->uri);
    scraper->options = &ScraperChangeOptions;
    scraper->scrap = &ScraperScrap;
    scraper->destroy = &ScraperDestroy;
    return scraper;
}

void ScraperChangeOptions(Scraper *scraper, string uri, u_int8_t maxDepth, string outputDir)
{
    free(scraper->uri);
    free(scraper->outputDir);
    free(scraper->basePath);
    scraper->uri = stringFromFormat("%s", uri);
    scraper->maxDepth = maxDepth;
    scraper->outputDir = stringFromFormat("%s", outputDir);
    scraper->basePath = ScraperGetBasePath(scraper->outputDir, scraper->uri);
}

string ScraperGetBasePath(string outputDir, string uri)
{
    string domainName = ScraperGetDomainName(uri);
    string basePath = stringFromFormat("%s/%s", outputDir, domainName);
    free(domainName);
    return basePath;
}

void ScraperScrap(Scraper *scraper)
{
    String *currentFilePath = newString();
    Map *headers = newMap();
    createDirectory(scraper->basePath);
    currentFilePath->proto->build(currentFilePath, "%s/%s", scraper->basePath, SCRAPER_INDEX_NAME);
    HttpDownloadFile(scraper->uri, SCRAPER_INDEX_NAME, currentFilePath->string, headers);
    for (u_int8_t i = 0; i < scraper->maxDepth; i++)
    {
    }
    headers->proto->destroy(headers, ScraperFreeHeaders);
    currentFilePath->proto->destroy(currentFilePath);
}

void ScraperFreeHeaders(string key, void *value)
{
    free(key);
    free(value);
}

string ScraperGetDomainName(string uri)
{
    String *wrapper = wrapString(uri);

    if (wrapper->proto->includes(wrapper, "//"))
    {
        String *tmp = wrapper->proto->search(wrapper, "//");
        wrapper->proto->destroy(wrapper);
        wrapper = tmp->proto->slice(tmp, 2, tmp->proto->length(tmp));
        tmp->proto->destroy(tmp);
    }

    String *domain = wrapper->proto->slice(wrapper, 0, wrapper->proto->indexOf(wrapper, '/'));
    wrapper->proto->destroy(wrapper);
    string result = domain->proto->toString(domain);
    return result;
}

void ScraperDestroy(Scraper *scraper)
{
    free(scraper->uri);
    free(scraper->outputDir);
    free(scraper->basePath);
    free(scraper);
}