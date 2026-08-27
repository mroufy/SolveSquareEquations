#include "../headers/defines.h"

#include "../headers/plot.h"
#include "../headers/mymath.h"
#include "../headers/solve.h"
#include "../headers/test.h"
#include "../headers/input_fun.h"
#include "../headers/study.h"


#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>

int regular_solve();
void output_roots(int root_num, double *x_1, double *x_2);


int main(int argc, char *argv[])
{
    if (argc > 1 && !strcmp(argv[1], "help"))
    {
        printf(C_BLUE "study - practice in solving equations\n"
               "test - to run preprogrammed tests\n"
               "testfile - to run tests from your file\n"
               "testadd - to add tests to file\n"
               "plot - draw plot of the function\n"
               "plotwobuf - draw plot w/o buffering\n"
               "do not type anything if you just want to solve equation\n" C_RESET);
        return 0;
    }

    else if (argc > 1 && !strcmp(argv[1], "study"))
    {
        study_mode();
        return 0;
    }

    else if (argc > 1 && !strcmp(argv[1], "test"))
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

    else if (argc > 2 && !strcmp(argv[1], "plot"))
    {
        draw_plot(argv[2]);
        return 0;
    }

    else if (argc > 2 && !strcmp(argv[1], "plotwobuf"))
    {
        draw_plot_wo_buffering(argv[2]);
        return 0;
    }

    else
    {
        regular_solve();
        return 0;
    }
}


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



/*
переделать цвета +
убрать основную программу из мэйн +
сделать документацию (doxigen)
график +
fclose сделать +
NAN in textcase
help +

do study mode +

*/
