#include "index.c"

void debug(ArrayList *list)
{
    for (int i = 0; i < list->size; i++)
    {
        puts(((char *)list->list) + i);
    }
}

int main(int argc, char **argv)
{
    char *array[3] = {"toto", "titi", "tata"};
    ArrayList *list = fromArray(array, 3, 4);
    debug(list);
    return 0;
}