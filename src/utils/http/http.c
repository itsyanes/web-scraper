#include "http.h"

static CURL *HttpPrepare();
static CURLcode HttpExecute(CURL *curl, string uri, string resourceName, Buffer *body, Buffer *headers);
static void HttpFinalize(CURLcode code, string resourceName, Buffer *headersBuffer, Map *headers);
static size_t HttpFillBuffer(string ptr, size_t size, size_t nmemb, void *dataBuffer);
static bool HttpIsHeader(void *e, size_t i, void *data);
static void *HttpExtractHeaderKey(void *e, size_t i, void *data);
static void *HttpExtractHeaderValue(void *e, size_t i, void *data);
static void HttpFreeDataList(void *e);
static void HttpRetrieveHeaders(Map *headersBuffer, Buffer *headers);
static size_t HttpWriteFile(string output, Buffer *data);

string HttpDownloadFile(string uri, string resourceName, string outputDir, Map *headers)
{
    Buffer *body = newBuffer();
    HttpFetch(uri, resourceName, body, headers);
    HttpWriteFile(outputDir, body);
    string stringifiedBody = Stringify((byte *)body->data, body->size);
    body->proto->destroy(body);
    return stringifiedBody;
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

bool HttpIsHeader(void *e, size_t i, void *data)
{
    return ((String *)e)->proto->includes((String *)e, ":");
}

void *HttpExtractHeaderKey(void *e, size_t i, void *data)
{
    String *key = ((String *)e)->proto->slice((String *)e, 0, ((String *)e)->proto->indexOf((String *)e, ':'));
    return key->proto->trim(key);
}

void *HttpExtractHeaderValue(void *e, size_t i, void *data)
{
    String *value = ((String *)e)->proto->slice((String *)e, ((String *)e)->proto->indexOf((String *)e, ':') + 1, ((String *)e)->proto->length((String *)e));
    return value->proto->trim(value);
}

void HttpFreeDataList(void *e)
{
    ((String *)e)->proto->destroy((String *)e);
}

void HttpRetrieveHeaders(Map *headers, Buffer *headersBuffer)
{
    string headerData = Stringify(headersBuffer->data, headersBuffer->size);
    String *wrapper = wrapString(headerData);
    free(headerData);

    ArrayList *splitLines = wrapper->proto->split(wrapper, "\n");
    ArrayList *headersLines = splitLines->proto->filter(splitLines, HttpIsHeader, NULL);
    ArrayList *headersKeys = headersLines->proto->map(headersLines, HttpExtractHeaderKey, NULL);
    ArrayList *headersValues = headersLines->proto->map(headersLines, HttpExtractHeaderValue, NULL);

    wrapper->proto->destroy(wrapper);
    splitLines->proto->destroy(splitLines, HttpFreeDataList);
    headersLines->proto->destroy(headersLines, NULL);

    size_t length = headersKeys->size;
    for (size_t i = 0; i < length; i++)
    {
        String *keyWrapper = headersKeys->proto->pop(headersKeys);
        string key = keyWrapper->proto->toString(keyWrapper);
        String *valueWrapper = headersValues->proto->pop(headersValues);
        string value = valueWrapper->proto->toString(valueWrapper);
        headers->proto->set(headers, key, value);
    }

    headersKeys->proto->destroy(headersKeys, NULL);
    headersValues->proto->destroy(headersValues, NULL);
}

size_t HttpWriteFile(string output, Buffer *data)
{
    size_t writtenBytes = 0;
    FILE *f = fopen(output, "w");
    if (f)
    {
        writtenBytes = fwrite(data->data, 1, data->size, f);
        fclose(f);
    }
    else
    {
        logger.sysError(output);
    }
    return writtenBytes;
}