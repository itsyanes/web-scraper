#include "download.h"

static void DownloadStart(Download *download);
static void DownloadFreeHeaders(string key, void *value);
static void DownloadDestroy(Download *download);

Download *newDownload(string fileName, string uri, string outputPath)
{
    Download *dl = xmalloc(1, sizeof(Download));
    dl->fileName = stringFromFormat("%s", fileName);
    dl->outputPath = stringFromFormat("%s", outputPath);
    dl->uri = stringFromFormat("%s", uri);
    dl->body = NULL;
    dl->headers = newMap();
    dl->destroy = &DownloadDestroy;
    dl->start = &DownloadStart;
    return dl;
}

void DownloadStart(Download *download)
{
    String *filePath = newString();
    filePath->proto->build(filePath, "%s/%s", download->outputPath, download->fileName);
    HttpDownloadFile(download->uri, download->fileName, filePath->string, download->headers);
    filePath->proto->destroy(filePath);
}

void DownloadFreeHeaders(string key, void *value)
{
    free(key);
    free(value);
}

void DownloadDestroy(Download *download)
{
    download->headers->proto->destroy(download->headers, DownloadFreeHeaders);
    if (download->body)
    {
        download->body->proto->destroy(download->body);
    }
    free(download->outputPath);
    free(download->fileName);
    free(download->uri);
    free(download);
}