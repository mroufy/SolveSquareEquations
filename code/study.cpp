/*!
    \file

    \brief Contains functions for study mode
*/
#include "../headers/defines.h"
#include "../headers/study.h"
#include "../headers/test.h"
#include "../headers/input_fun.h"
#include "../headers/mymath.h"
#include "../headers/solve.h"

#include <cmath>
#include <cstdio>


/*!
    \defgroup study_mode Study mode
    \brief Study mode asks user to enter number of roots and roots himself, and checks if one did it correct.
    It asks for coefficients, solves equation, but doesn't output them
*/
/*!
    \ingroup study_mode

    \brief Links the Study mode group.

    \return INPUT_ERROR if maximum of attempts for input reached
    \return else returns 0
*/
int study_mode()
{
    test_case ans = {.a = NAN, .b = NAN, .c = NAN, .root_num_ref = INPUT_ERROR, .x_1ref = NAN, .x_2ref = NAN};

    if (coef_input(&ans.a, &ans.b, &ans.c) == INPUT_ERROR)
        return INPUT_ERROR;

    ans.root_num_ref = solve_square_equation(ans.a, ans.b, ans.c, &ans.x_1ref, &ans.x_2ref);

    if (check_root_num(ans.root_num_ref) == INPUT_ERROR)
        return INPUT_ERROR;
    
    if (check_roots(ans.root_num_ref, ans.x_1ref, ans.x_2ref) == INPUT_ERROR)
        return INPUT_ERROR;

    printf(C_GREEN "NICE! You did it!\n" C_RESET);
    return 0;    
}


/*!
    \ingroup study_mode

    \brief Gets number of roots from user and checks if it correct

    User answers till he guess root number.

    \param [in] root_num_ref right amount of roots
*/
int check_root_num(int root_num_ref)
{
    int root_num = INPUT_ERROR;
    char n = '\0';
    int scanf_result = 0;

    printf(C_BLUE "Let's check if you solve it right. "
                  "How much roots did you got "
                  "(\"-1\" for infinite amount):\n" C_RESET);

    //scanf("%d%c", &root_num, &n);

    for (unsigned tries_count = 0; tries_count <= MAX_TRIES_COUNT; tries_count++)
        {
            scanf_result = scanf("%d%c", &root_num, &n);

            if (scanf_result == 2
                && n == '\n'
                && root_num == root_num_ref)

                return 0;
        
            else
            {
                printf(C_YELLOW "Nope! Try again:\n" C_RESET);
                input_clear_if_no_n(n);
                n = '\0';
                scanf_result = 0;
                root_num = INPUT_ERROR;
            }
        }

        printf(C_RED_BOX "Max number of tries reached!\n" C_RESET);
        return INPUT_ERROR;

    /*while (scanf("%d%c", &root_num, &n) != 2
           || n != '\n'
           || root_num != root_num_ref)
    {
        printf(C_YELLOW "Nope! Try again:\n" C_RESET);

        input_clear_if_no_n(n);
    }*/
}


/*!
    \ingroup study_mode

    \brief Gets roots from user and checks if they are correct

    If there is no roots to input it does nothing.
    User answers till he guess it.

    \param [in] root_num number of roots
    \param [in] x_1ref, x_2ref right roots

    \return INPUT_ERROR if number of tries reached MAX_TRIES_COUNT = 10
    \return else returns 0
*/
int check_roots(int root_num, double x_1ref, double x_2ref)
{
    double x_1 = NAN, x_2 = NAN;
    char n = '\0';
    int scanf_result = 0;

    switch (root_num)
    {
        case ONE_ROOT:
            printf(C_BLUE "Good job! Now, enter this single root\n" C_RESET);

            for (unsigned tries_count = 0; tries_count <= MAX_TRIES_COUNT; tries_count++)
            {
                scanf_result = scanf("%lg%c", &x_1, &n);

                if (scanf_result == 2
                    && n == '\n'
                    && compare_double(x_1, x_1ref))

                    return 0;
        
                else
                {
                    printf(C_YELLOW "Nope! Try again:\n" C_RESET);
                    input_clear_if_no_n(n);
                    n = '\0';
                    scanf_result = 0;
                    x_1 = NAN;
                }
            }

            printf(C_RED_BOX "Max number of tries reached!\n" C_RESET);
            return INPUT_ERROR;

            break;

        case TWO_ROOTS:
            printf(C_BLUE "Nice work! Enter these roots:\n" C_RESET);

            for (unsigned tries_count = 0; tries_count <= MAX_TRIES_COUNT; tries_count++)
            {
                scanf_result = scanf("%lg %lg%c", &x_1, &x_2, &n);
                my_sort(&x_1, &x_2);

                if (scanf_result == 3
                    && n == '\n'
                    && compare_double(x_1, x_1ref)
                    && compare_double(x_2, x_2ref))

                    return 0;
        
                else
                {
                    printf(C_YELLOW "Nope! Try again:\n" C_RESET);
                    input_clear_if_no_n(n);
                    n = '\0';
                    scanf_result = 0;
                    x_1 = NAN;
                    x_2 = NAN;
                }
            }

            printf(C_RED_BOX "Max number of tries reached!\n" C_RESET);
            return INPUT_ERROR;

            break;

        default:
            return 0;
            break;
    }
}
