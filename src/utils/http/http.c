#include "http.h"

void fetch(string uri, size_t (*callback)(char *ptr, size_t size, size_t nmemb, void *userdata))
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

        CURLcode res = curl_easy_perform(curl);

        if (res != CURLE_OK)
        {
            string error = stringFromFormat("Http error occurred: %s", curl_easy_strerror(res));
            logger.error(error);
            free(error);
        }

        curl_easy_cleanup(curl);
    }
}