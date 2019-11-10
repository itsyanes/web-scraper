#include "scraper.h"

static void ScraperChangeOptions(Scraper *scraper, string uri, u_int8_t maxDepth, string outputDir);
static void ScraperScrap(Scraper *scraper);
static string ScraperGetDomainName(string uri);
static void ScraperDestroy(Scraper *scraper);
static void ScraperFreeHeaders(string key, void *value);

Scraper *newScraper()
{
    Scraper *scraper = xmalloc(1, sizeof(Scraper));
    scraper->uri = stringFromFormat("%s", SCRAPER_DEFAULT_URI);
    scraper->maxDepth = 0;
    scraper->outputDir = stringFromFormat("%s", SCRAPER_DEFAULT_OUTPUT_DIR);
    scraper->options = &ScraperChangeOptions;
    scraper->scrap = &ScraperScrap;
    scraper->destroy = &ScraperDestroy;
    return scraper;
}

void ScraperChangeOptions(Scraper *scraper, string uri, u_int8_t maxDepth, string outputDir)
{
    free(scraper->uri);
    free(scraper->outputDir);
    scraper->uri = stringFromFormat("%s", uri);
    scraper->maxDepth = maxDepth;
    scraper->outputDir = stringFromFormat("%s", outputDir);
}

void ScraperScrap(Scraper *scraper)
{
    String *basePath = newString();
    String *currentFilePath = newString();
    Map *headers = newMap();
    string domainName = ScraperGetDomainName(scraper->uri);
    basePath->proto->build(basePath, "%s/%s", scraper->outputDir, domainName);
    createDirectory(basePath->string);
    free(domainName);
    currentFilePath->proto->build(currentFilePath, "%s/%s", basePath->string, SCRAPER_INDEX_NAME);
    HttpDownloadFile(scraper->uri, SCRAPER_INDEX_NAME, currentFilePath->string, headers);
    for (u_int8_t i = 0; i < scraper->maxDepth; i++)
    {
    }
    headers->proto->destroy(headers, ScraperFreeHeaders);
    basePath->proto->destroy(basePath);
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
    free(scraper);
}