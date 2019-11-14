#include "html.h"

static ArrayList *HTMLGetLinkAttributesList();
static void *HTMLGetLinksForAttribute(void *attribute, size_t index, void *htmlBody);

ArrayList *HTMLGetLinks(string htmlBody)
{
    String *wrapper = wrapString(htmlBody);

    ArrayList *attributes = HTMLGetLinkAttributesList();
    ArrayList *links = attributes->proto->flatMap(attributes, HTMLGetLinksForAttribute, wrapper);

    wrapper->proto->destroy(wrapper);
    attributes->proto->destroy(attributes, NULL);

    return links;
}

ArrayList *HTMLGetLinkAttributesList()
{
    ArrayList *attr = newArrayList();
    attr->proto->push(attr, ATTR_SRC);
    attr->proto->push(attr, ATTR_HREF);
    return attr;
}

void *HTMLGetLinksForAttribute(void *attribute, size_t index, void *htmlBody)
{
    ArrayList *current = newArrayList();
    String *wrapper = htmlBody;
    string ptr = wrapper->string;

    while ((ptr = stringFindSubstr(ptr, (string)attribute)))
    {
        string valueStart = stringFindChar(ptr, VALUE_DELIMITER);
        size_t start = valueStart - wrapper->string + 1;
        string valueEnd = stringFindChar(valueStart + 1, VALUE_DELIMITER);
        size_t end = valueEnd - wrapper->string;

        String *l = wrapper->proto->slice(wrapper, start, end);
        current->proto->push(current, l->proto->toString(l));

        ptr++;
    }

    return current;
}