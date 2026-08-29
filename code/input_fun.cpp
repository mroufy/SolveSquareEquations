/*!
    \file
    
    \brief File contains functions for working with input
*/

#include "../headers/defines.h"
#include "../headers/input_fun.h"

#include <cassert>
#include <cctype>
#include <cstdio>

/*!
    \defgroup input_clear_fun Input clearing functions

    \brief Contains functions for clearing input
*/
/*!
    \ingroup input_clear_fun

    \brief Clears input line

    \warning Will ask for input if there is nothing in input line
*/
void input_clear()
{
    int c = 0;
    while (c != EOF && c != '\n')
        c = getchar();
}


/*!
    \ingroup input_clear_fun
    
    \brief Clears input line if symbol that it got in parameters is '\n'

    \param [in] c symbol that it gets
*/
void input_clear_if_no_n(char c)
{
    if (c != '\n')
        input_clear();
}


/*!
    \ingroup input_clear_fun
    
    \brief Clears input line and outputs symbols that not a numbers

    \param [in] c gets a symbol so as not to lose
*/
void print_input_error(char c)
{
    while (c != EOF && c != '\n')
    {
        if (c != ' ' && isdigit(c) == 0 && c != '-' && c != '\0')
            printf(C_RED "%c" C_RESET, c);

        c = char(getchar());
    }

    printf(C_RED " <- not numbers\n" C_RESET);
    printf(C_RED "Input error. Try again:\n" C_RESET);
}

/*!
    \brief Gets coefficients a, b, c from input line

    \param [out] a, b, c coefficients

    \return INPUT_ERROR if number of tries reached MAX_TRIES_COUNT = 10
    \return else returns 0
*/
int coef_input(double *a, double *b, double *c)
{
    assert(a);
    assert(b);
    assert(c);

    int scanf_result = 0;
    char n = 0;

    printf(C_BLUE "Enter coefficients:\n" C_RESET);

    for (unsigned tries_count = 0; tries_count <= MAX_TRIES_COUNT; tries_count++)
    {

        scanf_result = scanf("%lg %lg %lg%c", a, b, c, &n);
        if (scanf_result == 4 && n == '\n')
            return 0;
        else
        {
            print_input_error(n);
            scanf_result = 0;
        }
    }

    printf(C_RED_BOX "Max number of tries reached!\n" C_RESET);
    return INPUT_ERROR;
}
