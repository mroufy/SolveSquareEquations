#include "../headers/defines.h"
#include "../headers/input_fun.h"

#include <cassert>
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
            printf(C_RED "%c" C_RESET, c);

        c = char(getchar());
    }
    printf(C_RED " <- not numbers\n" C_RESET);
}

int coef_input(double *a, double *b, double *c)
{
    assert(a);
    assert(b);
    assert(c);

    int scanf_result = 0, tries_count = 0;
    char n = 0;

    printf(C_BLUE "Enter coefficients\n" C_RESET);

    while (1)
    {

        scanf_result = scanf("%lg %lg %lg%c", a, b, c, &n);
        if (scanf_result == 4 && n == '\n')
            return 0;
        else
        {
            print_input_error(n);
            printf(C_RED "Input error. Try again\n" C_RESET);
            scanf_result = 0;
        }

        ++tries_count;
        if (tries_count >= 10)
        {
            printf(C_RED_BOX "Max number of tries reached\n" C_RESET);
            return INPUT_ERROR;
        }
    }
}
