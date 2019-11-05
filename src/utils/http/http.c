#include "http.h"

void fetch(string uri,
           char *resourceName,
           void *data,
           size_t (*callback)(char *ptr, size_t size, size_t nmemb, void *userdata),
           size_t (*headerCallback)(char *ptr, size_t size, size_t nmemb, void *userdata))
{
    CURL *curl = curl_easy_init();

    if (!curl)
    {
        logger.error("Request creation failed!");
    }

    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, uri);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, data);

        if (headerCallback)
        {
            curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, headerCallback);
        }

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