#include <string.h>
#include <ctype.h>

#include "string-utils.h"



char *strupr(char *str)
{
    for(char *next = str; *next != '\0'; next++)
        *next = toupper((int)*next);
    return str;
}


void replace_line_feed(char* str)
{
    for(char *next = str; *next != '\0'; next++)
    {
        if(*next == '\n')
        {
            *next = '\0';
            break;
        }
    }
}
