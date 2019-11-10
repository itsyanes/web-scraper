#include "index.c"

int main(int argc, char **argv)
{
    init();
    loop();
    curl_global_cleanup();
    return 0;
}