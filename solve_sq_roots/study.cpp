#include "defines.h"
#include "study.h"

#include "input_fun.h"
#include "mymath.h"
#include "solve.h"

#include <cmath>
#include <cstdio>

int study_mode()
{
    double a = 0, b = 0, c = 0;
    double x_1ref = NAN, x_2ref = NAN;

    if (coef_input(&a, &b, &c) == INPUT_ERROR)
        return INPUT_ERROR;
    
    int root_num_ref = solve_square_equation(a, b, c, &x_1ref, &x_2ref);

    double x_1 = NAN, x_2 = NAN;
    int root_num = 0;

    printf(C_BLUE "Let's check if you solve it right. "
                  "How much roots did you got "
                  "(\"-1\" for infinite amount):\n" C_RESET);
    scanf("%d", &root_num);

    while (root_num != root_num_ref)
    {
        printf(C_YELLOW "Nope! Try again:\n" C_RESET);
        scanf("%d", &root_num);
    }

    switch (root_num)
    {
        case ONE_ROOT:
            printf(C_BLUE "Good job! Now, enter this single root\n" C_RESET);
            scanf("%lg", &x_1);
            while (!compare_double(x_1, x_1ref))
            {
                printf(C_YELLOW "Nope! Try again:\n" C_RESET);
                scanf("%lg", &x_1);
            }
        case TWO_ROOTS:
            printf(C_BLUE "Nice work! Enter these roots:\n" C_RESET);
            scanf("%lg %lg", &x_1, &x_2);
            while (!compare_double(x_1, x_1ref) || !compare_double(x_2, x_2ref))
            {
                printf(C_YELLOW "Nope! Try again:\n" C_RESET);
                scanf("%lg %lg", &x_1, &x_2);
            }
        default:;
    }
    printf(C_GREEN "NICE! You did it!\n" C_RESET);
    return 1;
}
