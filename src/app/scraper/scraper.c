#include "scraper.h"

static void ScraperChangeOptions(Scraper *scraper, string uri, u_int8_t maxDepth, string outputDir);
static void ScraperScrap(Scraper *scraper);
static string ScraperGetDomainName(string uri);
static void ScraperDestroy(Scraper *scraper);
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
    createDirectory(scraper->basePath);

    Download *dl = newDownload(SCRAPER_INDEX_NAME, scraper->uri, scraper->outputDir);
    dl->start(dl);
    string mime = dl->getMimeType(dl);

    // if (stringsAreEqual(mime, HTML_CONTENT_TYPE))
    // {
    //     // getLinks(); -> arrayList of Links
    //     // -> transform Links into Download Objects
    //     // -> 
    // }

    free(mime);
    dl->destroy(dl);

    for (u_int8_t i = 0; i < scraper->maxDepth; i++)
    {
        // ArrayList downloads
        // download foreach
        // getMimeTypes
        // if html
        // getlinks -> merge into links arraylist
        // toDownloads
    }
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