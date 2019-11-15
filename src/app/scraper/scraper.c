#include "scraper.h"

static void ScraperChangeOptions(Scraper *scraper, string uri, u_int8_t maxDepth, string outputDir);
static void ScraperScrap(Scraper *scraper);
static string ScraperGetDomainName(string uri);
static void ScraperDestroy(Scraper *scraper);
static string ScraperGetBasePath(string outputDir, string uri);
static void *ScraperDownloadFromLink(void *element, size_t index, void *data);
static string ScraperGetResourceName(string uri);
static void ScraperDestroyLinks(void *link);
static void ScraperStartAllDownloads(void *e, size_t i, void *data);
static bool ScraperDownloadIsMimeHtml(void *e, size_t i, void *data);
static void *ScraperDownloadGetLinks(void *e, size_t i, void *data);
static void ScraperEndAllDownloads(void *download);

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

    Download *dl = newDownload(SCRAPER_INDEX_NAME, scraper->uri, scraper->basePath);
    dl->start(dl);
    ArrayList *links = HTMLGetLinks(dl->body);
    dl->destroy(dl);

    for (u_int8_t i = 0; i < scraper->maxDepth; i++)
    {
        ArrayList *dls = links->proto->map(links, ScraperDownloadFromLink, scraper);
        links->proto->destroy(links, ScraperDestroyLinks);
        dls->proto->forEach(dls, ScraperStartAllDownloads, NULL);
        ArrayList *htmls = dls->proto->filter(dls, ScraperDownloadIsMimeHtml, NULL);
        links = htmls->proto->flatMap(htmls, ScraperDownloadGetLinks, NULL);
        htmls->proto->destroy(htmls, NULL);
        dls->proto->destroy(dls, ScraperEndAllDownloads);
    }

    links->proto->destroy(links, ScraperDestroyLinks);
}

string ScraperGetDomainName(string uri)
{
    String *wrapper = wrapString(uri);

    if (wrapper->proto->includes(wrapper, "//"))
    {
        String *tmp = wrapper->proto->searchAndCut(wrapper, "//");
        wrapper->proto->destroy(wrapper);
        wrapper = tmp->proto->slice(tmp, 2, tmp->proto->length(tmp));
        tmp->proto->destroy(tmp);
    }

    String *domain = wrapper->proto->slice(wrapper, 0, wrapper->proto->indexOf(wrapper, '/'));
    wrapper->proto->destroy(wrapper);
    string result = domain->proto->toString(domain);
    return result;
}

void *ScraperDownloadFromLink(void *element, size_t index, void *data)
{
    string uri = element;
    Scraper *scraper = data;
    string resourceName = ScraperGetResourceName(uri);

    Download *dl = newDownload(resourceName, uri, scraper->basePath);

    free(resourceName);
    return dl;
}

string ScraperGetResourceName(string uri)
{
    String *wrapper = wrapString(uri);
    String *res;

    if (wrapper->proto->includes(wrapper, "/"))
    {
        res = wrapper->proto->slice(
            wrapper,
            wrapper->proto->lastIndexOf(wrapper, '/'),
            wrapper->proto->length(wrapper));
    }
    else
    {
        res = wrapper->proto->clone(wrapper);
    }

    wrapper->proto->destroy(wrapper);
    return res->proto->toString(res);
}

void ScraperDestroyLinks(void *link)
{
    free(link);
}

void ScraperStartAllDownloads(void *e, size_t i, void *data)
{
    Download *dl = e;
    dl->start(dl);
}

bool ScraperDownloadIsMimeHtml(void *e, size_t i, void *data)
{
    Download *dl = e;
    string mime = dl->getMimeType(dl);
    bool res = stringsAreEqual(mime, HTML_CONTENT_TYPE) || stringLength(mime) == 0;
    free(mime);
    return res;
}

void *ScraperDownloadGetLinks(void *e, size_t i, void *data)
{
    return HTMLGetLinks(((Download *)e)->body);
}

void ScraperEndAllDownloads(void *download)
{
    ((Download *)download)->destroy((Download *)download);
}

void ScraperDestroy(Scraper *scraper)
{
    free(scraper->uri);
    free(scraper->outputDir);
    free(scraper->basePath);
    free(scraper);
}