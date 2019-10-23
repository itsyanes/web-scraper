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
    return 0;
}