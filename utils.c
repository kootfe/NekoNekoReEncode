#include "headers/utils.h"
#include <stdio.h>
#include <string.h>

int stack_strcpy(char **buff, size_t buff_size, char *text)
{
    int add = strlen(text);
    int bufl = strlen(*buff);

    if (add+bufl > buff_size) {
        return -1;
    }

    snprintf(*buff + bufl, buff_size - bufl, "%s", text);
    return 0;
}
