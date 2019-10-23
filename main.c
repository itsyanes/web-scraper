#include "index.c"

void debug(ArrayList *list)
{
    for (int i = 0; i < list->size; i++)
    {
        puts(((char *)list->list) + i);
    }
}

void debugInt(ArrayList *list)
{
    for (int i = 0; i < list->size; i++)
    {
        printf("%d\n", (*(int *)list->list[i]));
    }
}

int main(int argc, char **argv)
{
    int tab[] = { 0, 1, 2 };
    char *array[3] = {"toto", "titi", "tata"};
    printf("%p %p %p %lu\n", array, array + 1, array + 2, sizeof(char *));
    ArrayList *list = fromArray(tab, 3, sizeof(int));
    debugInt(list);
    ArrayList *list2 = fromArray(array, 3, sizeof(char *));
    debug(list2);
    return 0;
}