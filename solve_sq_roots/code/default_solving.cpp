#include "../headers/defines.h"
#include "../headers/default_solving.h"

#include "../headers/solve.h"
#include "../headers/mymath.h"
#include "../headers/input_fun.h"

#include <cassert>
#include <cmath>
#include <cstdio>


int regular_solve()
{
    while (1)
    {
        double x_1 = NAN, x_2 = NAN;
        double a = NAN, b = NAN, c = NAN;
        int root_num = 0;

        if (coef_input(&a, &b, &c) == INPUT_ERROR)
            return INPUT_ERROR;

        root_num = solve_square_equation(a, b, c, &x_1, &x_2);

        output_roots(root_num, &x_1, &x_2);
        return 0;
    }
}


void output_roots(int root_num, double *x_1, double *x_2)
{
    assert(x_1);
    assert(x_2);

    *x_1 = remove_minus_zero(*x_1);
    *x_2 = remove_minus_zero(*x_2);

    switch (root_num)
    {
    case NO_ROOTS:
        printf(C_YELLOW "No roots\n" C_RESET);
        break;
    case ONE_ROOT:
        printf(C_GREEN "x = %lg\n" C_RESET, *x_1);
        
        break;
    case TWO_ROOTS:
        printf(C_GREEN "x_1 = %lg, x_2 = %lg\n" C_RESET, *x_1, *x_2);
        break;
    case INF_ROOTS:
        printf(C_GREEN "Infinite amount of roots\n" C_RESET);
        break;
    default:
        printf(C_RED_BOX "Root count error\n" C_RESET);
    }
}
