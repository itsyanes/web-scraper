#include "index.c"

void debug(ArrayList *list)
{
    for (int i = 0; i < list->size; i++)
    {
        puts((char *)list->_list[i]);
    }
    puts("---");
}

void print(void *e, size_t i)
{
    puts(e);
}

bool check(void *e, size_t i)
{
    return strcmp(e, "toto") == 0;
}

int main(int argc, char **argv)
{
    char *toto = "toto";
    char *titi = "titi";
    char *tata = "tata";
    ArrayList *list = newArrayList();
    list->proto->push(list, toto);
    list->proto->push(list, titi);
    list->proto->push(list, tata);
    list->proto->pop(list);
    list->proto->push(list, titi);
    ArrayList *l2 = list->proto->fill(list, tata, 1, 3);
    debug(list);
    debug(l2);
    ArrayList *l3 = list->proto->concat(list, l2);
    debug(l3);
    printf("check : %d\n", list->proto->every(list, check));
    l3->proto->destroy(l3, NULL);
    l3 = list->proto->filter(list, check);
    debug(l3);
    l3->proto->destroy(l3, NULL);
    puts(list->proto->find(list, check));
    printf("index: %ld\n", list->proto->findIndex(list, check));
    list->proto->forEach(list, print);
    printf("includes: %d, indexOf: %ld\n", list->proto->includes(list, toto), list->proto->indexOf(list, titi));
    return 0;
}