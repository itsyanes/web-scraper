#include "http.h"

static CURL *HttpPrepare();
static CURLcode HttpExecute(CURL *curl, string uri, string resourceName, Buffer *body, Buffer *headers);
static void HttpFinalize(CURLcode code, string resourceName, Buffer *headersBuffer, Map *headers);
static size_t HttpFillBuffer(string ptr, size_t size, size_t nmemb, void *dataBuffer);
static size_t HttpRetrieveHeaders(Map *headersBuffer, Buffer *headers);

void HttpDownloadFile(string uri, string resourceName, string outputDir, Map *headers)
{

}

void HttpFetch(string uri, string resourceName, Buffer *body, Map *headers)
{
    CURL *curl = HttpPrepare();

    if (curl)
    {
        Buffer *headersBuffer = newBuffer();
        CURLcode code = HttpExecute(curl, uri, resourceName, body, headersBuffer);
        HttpFinalize(code, resourceName, headersBuffer, headers);
        headersBuffer->proto->destroy(headersBuffer);
    }
}

CURL *HttpPrepare()
{
    CURL *curl = curl_easy_init();

    if (!curl)
    {
        logger.error("Request creation failed!");
    }

    return curl;
}

CURLcode HttpExecute(CURL *curl, string uri, string resourceName, Buffer *body, Buffer *headers)
{
    curl_easy_setopt(curl, CURLOPT_URL, uri);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, HttpFillBuffer);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, body);
    curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, HttpFillBuffer);
    curl_easy_setopt(curl, CURLOPT_HEADERDATA, headers);

    string message = stringFromFormat("Fetching %s...", resourceName);
    logger.info(message);
    free(message);

    CURLcode res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    return res;
}

void HttpFinalize(CURLcode code, string resourceName, Buffer *headersBuffer, Map *headers)
{
    if (code == CURLE_OK)
    {
        string message = stringFromFormat("%s was successfully fetched!", resourceName);
        logger.info(message);
        free(message);
    }

    if (code != CURLE_OK)
    {
        string error = stringFromFormat("Http error occurred: %s", curl_easy_strerror(code));
        logger.error(error);
        free(error);
    }

    HttpRetrieveHeaders(headers, headersBuffer);
}

size_t HttpFillBuffer(string ptr, size_t size, size_t nmemb, void *dataBuffer)
{
    Buffer *b = dataBuffer;
    b->proto->append(b, ptr, size * nmemb);
    return size * nmemb;
}

size_t HttpRetrieveHeaders(Map *headersBuffer, Buffer *headers)
{
    string h = Stringify(headers->data, headers->size);

    puts(h);

    return headers->size;
}

// size_t HttpWriteFile(string ptr, size_t size, size_t nmemb, void *userdata)
// {
//     size_t writtenBytes = 0;
//     FILE *f = fopen((string)userdata, "a");
//     if (f)
//     {
//         writtenBytes = fprintf(f, "%s", ptr);
//         fclose(f);
//     }
//     else
//     {
//         logger.sysError((string)userdata);
//     }
//     return writtenBytes;
// }