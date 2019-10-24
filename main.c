#include "index.c"

void debug(ArrayList *list)
{
    for (int i = 0; i < list->contained; i++)
    {
        puts((char *)list->list[i]);
    }
}

void debugInt(ArrayList *list)
{
    for (int i = 0; i < list->contained; i++)
    {
        printf("%d\n", (*(int *)list->list[i]));
    }
}

int main(int argc, char **argv)
{
    char *toto = "toto";
    char *titi = "titi";
    ArrayList *list = newArrayList();
    list->proto->push(list, toto);
    list->proto->push(list, titi);
    debug(list);
    puts(list->proto->pop(list));
    debug(list);
    return 0;
}