#include "defines.h"

#include "mymath.h"
#include "solve.h"
#include "test.h"


#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>

int coef_input(double *a, double *b, double *c);
void output_roots(int root_num, double *x_1, double *x_2);


int main(int argc, char *argv[])
{
    
    if (argc > 1 && !strcmp(argv[1], "test"))
    {
        run_tests();
        return 0;
    }

    else if (argc > 2 && !strcmp(argv[1], "testfile"))
    {
        run_file_tests(argv[2]);
        return 0;
    }

    else if (argc > 2 && !strcmp(argv[1], "testadd"))
    {
        add_test_file(argv[2]);
        return 0;
    }

    while (1)
    {
        double x_1 = NAN, x_2 = NAN;
        double a = NAN, b = NAN, c = NAN;
        int root_num = 0, scanf_result = 0;

        if (coef_input(&a, &b, &c) == INPUT_ERROR)
            return INPUT_ERROR;

        root_num = solve_square_equation(a, b, c, &x_1, &x_2);

        output_roots(root_num, &x_1, &x_2);
    }
    return 0;
}


int coef_input(double *a, double *b, double *c)
{
    assert(a);
    assert(b);
    assert(c);

    int scanf_result = 0, tries_count = 0;
    char n = 0;

    printf("%sEnter coefficients\n%s",
             C_BLUE, C_RESET);

    while (1)
    {

        scanf_result = scanf("%lg %lg %lg%c", a, b, c, &n);
        if (scanf_result == 4 && n == '\n')
            return 0;
        else
        {
            print_input_error(n);
            printf("%sInput error. Try again\n%s", C_RED, C_RESET);
            scanf_result = 0;
        }

        ++tries_count;
        if (tries_count >= 10)
        {
            printf("%sMax number of tries reached\n%s", C_RED_BOX, C_RESET);
            return INPUT_ERROR;
        }
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
        printf("%sNo roots\n%s", C_YELLOW, C_RESET);
        break;
    case ONE_ROOT:
        printf("%sx = %lg\n%s", C_GREEN, *x_1, C_RESET);
        
        break;
    case TWO_ROOTS:
        printf("%sx_1 = %lg, x_2 = %lg\n%s", C_GREEN, *x_1, *x_2, C_RESET);
        break;
    case INF_ROOTS:
        printf("%sInfinite amount of roots\n%s", C_GREEN, C_RESET);
        break;
    default:
        printf("%sRoot count error\n%s", C_RED_BOX, C_RESET);
    }
}




