#include "string-wrapper.c"
#include "map.c"
#include "utils.c"

int reducer(int accumulator, char currentValue)
{
    return accumulator + currentValue;
}

int main(int argc, char **argv)
{
    StringWrapper *wrapper = newStringWrapper();
    wrapper->fromString(wrapper, "tototiti");
    wrapper->print(wrapper, stdout);
    printf("%d", wrapper->reduce(wrapper, &reducer, 0));
    wrapper->destroy(wrapper);
}