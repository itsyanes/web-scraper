#include "index.c"

int reducer(int accumulator, char currentValue)
{
    return accumulator + currentValue;
}

int main(int argc, char **argv)
{
    StringWrapper *wrapper = wrapString("tototiti");
    wrapper->proto->print(wrapper, stdout);
    printf("%d", wrapper->proto->reduce(wrapper, &reducer, 0));
    wrapper->proto->destroy(wrapper);
}