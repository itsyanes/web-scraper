#include "index.c"
#include "./test/index.c"
#include <curl/curl.h>

size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata)
{
    return fprintf(stdout, "%s", ptr);
}

int main(int argc, char **argv)
{
    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, "https://example.com");
        /* example.com is redirected, so we tell libcurl to follow redirection */
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);
        /* Check for errors */
        if (res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));
        /* always cleanup */
        curl_easy_cleanup(curl);
    }
    return 0;
}