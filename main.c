#include "index.c"

void print(string key, void *value) {
    printf("%s %s\n", key, (char *)value);
}

int main(int argc, char **argv)
{
    init();
    loop();
    return 0;
}