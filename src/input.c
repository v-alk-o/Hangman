#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>

#include "input.h"



void flush_input_buffer()
{
    int c = 0;
    while (c != '\n' && c != EOF)
        c = getchar();
}


int read_input(char *str, int count)
{
    char *lineFeedPosition = NULL;
    if (fgets(str, count, stdin) != NULL)
    {
        if((lineFeedPosition = strchr(str, '\n')) != NULL)
        {
            *lineFeedPosition = '\0';
            return 0;
        }

    }
    flush_input_buffer();
    return 1;

}


int read_capital_letter()
{
    int c = -1;
    char str[3];
    while(!(c >= 65 && c <= 90))
    {
        printf("> ");
        if(read_input(str, 3) == 0)
            c = toupper(str[0]);
    }
    return c;
}


int* strtoi(char* str, int* nb)
{
    long temp_long = 0;
    char *endptr = NULL;
    errno = 0;

    for(char* p = str; *p != '\0'; p++)
    {
        if(isspace(*p))
            return NULL;
    }

    temp_long = strtol(str, &endptr, 10);
    
    if(errno == ERANGE || !(INT_MIN <= temp_long && temp_long <= INT_MAX))
        return NULL;

    else if(endptr == str)
        return NULL;

    else if(*endptr != '\0')
        return NULL;

    else
        *nb = (int)temp_long;
    return nb;
}


int* read_integer(int* nb)
{
    char str1[100];
    if(read_input(str1, sizeof(str1)) == 0)
        return strtoi(str1, nb);
    else
        return NULL;
}
