#include "index.c"

void debug(ArrayList *list)
{
    for (int i = 0; i < list->size; i++)
    {
        puts((char *)list->_list[i]);
    }
}

void debugInt(ArrayList *list)
{
    for (int i = 0; i < list->size; i++)
    {
        printf("%d\n", (*(int *)list->_list[i]));
    }
}

int main(int argc, char **argv)
{
    char *toto = "toto";
    char *titi = "titi";
    ArrayList *list = newArrayList();
    list->proto->push(list, toto);
    list->proto->push(list, titi);
    list->proto->pop(list);
    list->proto->push(list, titi);
    ArrayList *l2 = list->proto->fill(list, toto, 0, 2);
    debug(l2);
    return 0;
}