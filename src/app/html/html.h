#ifndef HTML_H

#define HTML_H

#include "shared/shared.h"
#include "utils/utils.h"
#include "struct/struct.h"

#define ATTR_SRC "src=\""
#define ATTR_HREF "href=\""
#define VALUE_DELIMITER '"'

ArrayList *HTMLGetLinks(string htmlBody);

#endif