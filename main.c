#include "index.c"

size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata)
{
    return fprintf(stdout, "%s", ptr);
}

int main(int argc, char **argv)
{
    init();
    fetch("https://example.com", write_callback);
    return 0;
}