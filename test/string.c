#include "struct/string-wrapper/string-wrapper.h"

static void printStr(void *e, size_t i)
{
    String *str = e;
    puts(str->string);
}

static void freeStr(void *e)
{
    String *str = e;
    str->proto->destroy(str);
}

void testString()
{
    String *wrapper3 = newString();
    String *wrapper = wrapper3->proto->clone(wrapper3);
    wrapper3->proto->destroy(wrapper3);
    wrapper->proto->build(wrapper, "%s%s%s%d%s", "toto", " ", "is ", 12, " years old.");
    puts(wrapper->string);
    printf("length: %lu, charAt: %d %d\n", wrapper->proto->length(wrapper), wrapper->proto->charAt(wrapper, 1000), wrapper->proto->charAt(wrapper, 14));
    printf("indexOf: %ld, lastIndexOf: %ld\n", wrapper->proto->indexOf(wrapper, 'i'), wrapper->proto->lastIndexOf(wrapper, 'o'));
    wrapper->proto->concat(wrapper, " or is he?");
    puts(wrapper->string);
    printf("length: %lu\n", wrapper->proto->length(wrapper));
    printf("includes: %d, includes: %d\n", wrapper->proto->includes(wrapper, "toto"), wrapper->proto->includes(wrapper, "titi"));
    printf("startsWith: %d, startsWith: %d\n", wrapper->proto->startsWith(wrapper, "toto"), wrapper->proto->startsWith(wrapper, "years"));
    printf("endsWith: %d, endsWith: %d\n", wrapper->proto->endsWith(wrapper, "old."), wrapper->proto->endsWith(wrapper, "he?"));
    wrapper->proto->replace(wrapper, "o", "atm");
    printf("%s\nlength: %lu\n", wrapper->string, wrapper->proto->length(wrapper));
    wrapper->proto->destroy(wrapper);
    wrapper = wrapString("elancourt");
    wrapper->proto->reverse(wrapper);
    wrapper->proto->reverse(wrapper);
    puts(wrapper->string);
    String *wrapper2 = wrapper->proto->slice(wrapper, 4, 6);
    puts(wrapper2->string);
    wrapper->proto->destroy(wrapper);
    wrapper2->proto->destroy(wrapper2);
    wrapper = wrapString(" elancourt");
    puts(wrapper->string);
    wrapper->proto->trim(wrapper);
    string str = wrapper->proto->toString(wrapper);
    puts(str);
    free(str);
    wrapper = newString();
    wrapper->proto->build(wrapper, "%s%s%s%d%s", "toto", " ", "is ", 12, " years old.");
    puts(wrapper->string);
    wrapper2 = wrapper->proto->search(wrapper, "12");
    puts(wrapper2->string);
    wrapper->proto->destroy(wrapper);
    wrapper2->proto->destroy(wrapper2);
    wrapper = wrapString(":toto:titi:tata:tyty!:");
    ArrayList *list = wrapper->proto->split(wrapper, ":|;<");
    list->proto->forEach(list, printStr);
    printf("length: %lu--\n", list->size);
    list->proto->destroy(list, freeStr);
}