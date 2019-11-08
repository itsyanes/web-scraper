#include "http.h"

static size_t HttpWriteFile(string ptr, size_t size, size_t nmemb, void *userdata);
static size_t HttpGetHeaders(string ptr, size_t size, size_t nmemb, void *headerData);

void downloadFile(string uri, string resourceName, string outputDir, Map *headers)
{
    CURL *curl = curl_easy_init();

    if (!curl)
    {
        logger.error("Request creation failed!");
    }

    if (curl)
    {
        Buffer *bodyBuffer = newBuffer();
        Buffer *headersBuffer = newBuffer();

        curl_easy_setopt(curl, CURLOPT_URL, uri);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, HttpFillBuffer);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, bodyBuffer);
        curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, HttpFillBuffer);
        curl_easy_setopt(curl, CURLOPT_HEADERDATA, headersBuffer);

        string message = stringFromFormat("Downloading %s...", resourceName);
        logger.info(message);
        free(message);

        CURLcode res = curl_easy_perform(curl);

        if (res == CURLE_OK)
        {
            message = stringFromFormat("%s was successfully downloaded!", resourceName);
            logger.info(message);
            free(message);
        }

        if (res != CURLE_OK)
        {
            string error = stringFromFormat("Http error occurred: %s", curl_easy_strerror(res));
            logger.error(error);
            free(error);
        }

        curl_easy_cleanup(curl);
    }
}

size_t HttpFillBuffer(string ptr, size_t size, size_t nmemb, void *dataBuffer)
{
    Buffer *b = dataBuffer;
    b->proto->append(b, ptr, size * nmemb);
    return size * nmemb;
}

size_t HttpGetHeaders(string ptr, size_t size, size_t nmemb, void *headerData)
{
}

size_t HttpWriteFile(string ptr, size_t size, size_t nmemb, void *userdata)
{
    size_t writtenBytes = 0;
    FILE *f = fopen((string)userdata, "a");
    if (f)
    {
        writtenBytes = fprintf(f, "%s", ptr);
        fclose(f);
    }
    else
    {
        logger.sysError((string)userdata);
    }
    return writtenBytes;
}