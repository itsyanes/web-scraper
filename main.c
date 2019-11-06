#include "index.c"

void print(string key, void *value) {
    printf("%s %s\n", key, (char *)value);
}

int main(int argc, char **argv)
{
    init();
    // loop();
    Map *m = newMap();
    m->proto->set(m, "toto", "titi");
    m->proto->set(m, "titi", "toto");
    m->proto->set(m, "tata", "tutu");
    m->proto->set(m, "tutu", "tata");
    m->proto->forEach(m, print);
    return 0;
}