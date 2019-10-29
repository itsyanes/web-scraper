#include "struct/array-list/array-list.h"

void debug(ArrayList *list)
{
    for (int i = 0; i < list->size; i++)
    {
        puts((char *)list->_list[i]);
    }
    puts("---");
}

void debugInt(ArrayList *list)
{
    for (int i = 0; i < list->size; i++)
    {
        printf("%d\n", *(int *)list->_list[i]);
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

bool check2(void *e, size_t i)
{
    return strcmp(e, "tata") == 0;
}

size_t sortFunc(void *e)
{
    return (size_t)*(int *)e;
}

void *mapper(void *e, size_t i)
{
    char *new = malloc(10);
    sprintf(new, "%s%s", (char *)e, "ta");
    return new;
}

void *reducer(void *acc, void *e)
{
    *(int *)acc = *(int *)acc + *(int *)e;
    return acc;
}

void hook(void *e)
{
    free(e);
}

void testList()
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
    l2 = list->proto->map(list, mapper);
    debug(l2);
    l2->proto->destroy(l2, hook);
    int t = 3;
    int u = 4;
    int v = 5;
    l2 = newArrayList();
    l2->proto->push(l2, &t);
    l2->proto->push(l2, &u);
    l2->proto->push(l2, &v);
    debugInt(l2);
    int *res = malloc(sizeof(int));
    *res = 0;
    l2->proto->reduce(l2, reducer, res);
    printf("%d\n", *res);
    l3 = l2->proto->slice(l2, 0, 1);
    printf("length :%lu-0:%d\n", l3->size, *(int *)l3->proto->get(l3, 0));
    list->proto->destroy(list, NULL);
    list = newArrayList();
    list->proto->push(list, toto);
    list->proto->push(list, titi);
    list->proto->push(list, titi);
    printf("some:%d %d\n", list->proto->some(list, check), list->proto->some(list, check2));
    l2->proto->push(l2, &v);
    l2->proto->push(l2, &u);
    l2->proto->push(l2, &t);
    debugInt(l2);
    l2->proto->sort(l2, sortFunc);
    debugInt(l2);
}