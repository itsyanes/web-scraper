#include "index.c"

int reducer(int accumulator, char currentValue)
{
    return accumulator + currentValue;
}

int main(int argc, char **argv)
{
    String *wrapper = newString();
    wrapper->proto->build(wrapper, "%s%s%s%d%s", "toto", " ", "is ", 12, " years old.");
    puts(wrapper->string);
    wrapper->proto->destroy(wrapper);
}