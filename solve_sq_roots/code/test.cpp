#include "../headers/defines.h"
#include "../headers/test.h"

#include "../headers/mymath.h"
#include "../headers/input_fun.h"
#include "../headers/solve.h"

#include <cassert>
#include <cstdio>

void run_file_tests(char* file_name)
{
    FILE* fp = fopen(file_name, "r");
    if (!fp)
    {
        printf(C_RED_BOX "Can't open file\n" C_RESET);
        return;
    }

    test_case test = {};
    int scanf_result = fscanf(fp, "%lg %lg %lg %d %lg %lg\n",
                                   &test.a, &test.b, &test.c, &test.root_num_ref, &test.x_1ref, &test.x_2ref);

    while (scanf_result == 6)
    {
        if (run_one_test(test))
            printf("%sTest completed\n%s", C_GREEN, C_RESET);
        scanf_result = fscanf(fp, "%lg %lg %lg %d %lg %lg\n",
                                   &test.a, &test.b, &test.c, &test.root_num_ref, &test.x_1ref, &test.x_2ref);
    }

    if (fclose(fp))
        printf(C_RED_BOX "Can't close the file\n" C_RESET);
}


int add_test_file(char* file_name)
{
    FILE* fp = fopen(file_name, "a");
    if (!fp)
    {
        printf(C_RED_BOX "Can't open the file\n" C_RESET);
        return 0;
    }

    int scanf_result = 0;
    while (1)
    {
        char n = '\0';
        test_case test = {};

        printf(C_BLUE "Enter coefficients, number of roots, roots(a b c root_num x_1 x_2)\n" C_RESET);

        scanf_result = scanf("%lg %lg %lg %d %lg %lg%c",
                              &test.a, &test.b, &test.c, &test.root_num_ref, &test.x_1ref, &test.x_2ref, &n);
        
        if (scanf_result == 7 && n == '\n')
        {
            fprintf(fp, "%lg %lg %lg %d %lg %lg\n",
                         test.a, test.b, test.c, test.root_num_ref, test.x_1ref, test.x_2ref);
            return 1;
        }
        else
        {
            print_input_error(n);
            printf(C_RED "Input error. Try again\n" C_RESET);
        }

    if (fclose(fp))
        printf(C_RED_BOX "Can't close the file\n" C_RESET);
    }
}


void run_tests()
{
    int tests_completed = 0;
    const int tests_num = 7;

    test_case tests_all[tests_num] = 
    {{.a = 1, .b = -2, .c = 1, .root_num_ref = ONE_ROOT, .x_1ref = 1},
    {.a = 1, .b = 0, .c = 0, .root_num_ref = ONE_ROOT, .x_1ref = 0},
    {.a = 0, .b = 1, .c = 0, .root_num_ref = ONE_ROOT, .x_1ref = 0},
    {.a = 0, .b = 0, .c = 1, .root_num_ref = NO_ROOTS},
    {.a = 0, .b = 0, .c = 0, .root_num_ref = INF_ROOTS},
    {.a = 1, .b = -5, .c = 6, .root_num_ref = TWO_ROOTS, .x_1ref = 2, .x_2ref = 3},
    {.a = 1, .b = -13, .c = 42, .root_num_ref = TWO_ROOTS, .x_1ref = 6, .x_2ref = 7}};
    
    for (int i = 0; i < tests_num; i++)
    {
        assert(0 <= i && i < tests_num);
        tests_completed += run_one_test(tests_all[i]);
    }

    if (tests_completed == tests_num)
        printf(C_GREEN "All tests completed %d/%d\n" C_RESET, tests_completed, tests_num);
    else
        printf(C_YELLOW "Tests completed %d/%d\n" C_RESET, tests_completed, tests_num);
}


int run_one_test(test_case test)
{
    double x_1 = 0, x_2 = 0;
    int root_num = solve_square_equation(test.a, test.b, test.c, &x_1, &x_2);

    x_1 = remove_minus_zero(x_1);
    x_2 = remove_minus_zero(x_2);

    if (root_num != test.root_num_ref || !(compare_double(x_1, test.x_1ref)) || !(compare_double(x_2, test.x_2ref)))
    {
        printf(C_RED "Test FAILED: a = %lg, b = %lg, c = %lg\n"
            "Expected %d roots, x_1 = %lg, x_2 = %lg\n"
            "Got %d roots, x_1 = %lg, x_2 = %lg\n" C_RESET,
            test.a, test.b, test.c, test.root_num_ref, test.x_1ref, test.x_2ref, root_num, x_1, x_2);
        return 0;
    }
    else
        return 1;
}


void print_structure_testcase(test_case test)
{
    printf("%lg %lg %lg %d %lg %lg\n", test.a, test.b, test.c, test.root_num_ref, test.x_1ref, test.x_2ref);
}