#include "defines.h"
#include "input_fun.h"

#include <cctype>
#include <cstdio>


void input_clear()
{
    int c = 0;
    while (c != EOF && c != '\n')
        c = getchar();
}

void print_input_error(char c)
{
    while (c != EOF && c != '\n')
    {
        if (c != ' ' && isdigit(c) == 0 && c != '-' && c != '\0')
            printf("%s%c%s", C_RED, c, C_RESET);
        c = getchar();
    }
    printf("%s <- not numbers\n%s", C_RED, C_RESET);
}