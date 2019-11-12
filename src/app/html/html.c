#include "html.h"

ArrayList *HTMLGetLinks(string htmlBody)
{
    ArrayList *links = newArrayList();
    String *wrapper = wrapString(htmlBody);
    string ptr = wrapper->string;

    while ((ptr = stringFindSubstr(ptr, "href=")))
    {
        string valueStart = stringFindChar(ptr, VALUE_DELIMITER);
        size_t start = valueStart - wrapper->string + 1;
        string valueEnd = stringFindChar(valueStart + 1, VALUE_DELIMITER);
        size_t end = valueEnd - wrapper->string;

        String *l = wrapper->proto->slice(wrapper, start, end);
        links->proto->push(links, l->proto->toString(l));

        ptr++;
    }

    wrapper->proto->destroy(wrapper);
    return links;
}

ArrayList *HTMLGetLinkAttributesList()
{
    ArrayList *attr = newArrayList();
    attr->proto->push(attr, ATTR_SRC);
    attr->proto->push(attr, ATTR_HREF);
    return attr;
}