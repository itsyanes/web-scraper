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
    printf("length: %lu, charAt: %d %d\n", wrapper->proto->length(wrapper), wrapper->proto->charAt(wrapper, 1000), wrapper->proto->charAt(wrapper, 14));
    printf("indexOf: %d, lastIndexOf: %d\n", wrapper->proto->indexOf(wrapper, 'i'), wrapper->proto->lastIndexOf(wrapper, 'o'));
    wrapper->proto->concat(wrapper, " or is he?");
    puts(wrapper->string);
    printf("length: %lu\n", wrapper->proto->length(wrapper));
    wrapper->proto->destroy(wrapper);
}