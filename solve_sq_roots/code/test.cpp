#include "../headers/defines.h"
#include "../headers/test.h"

#include "../headers/mymath.h"
#include "../headers/input_fun.h"
#include "../headers/solve.h"

#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>


void run_file_tests(char* file_name)
{
    assert(file_name);
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
    assert(file_name);
    unsigned tests_cnt = 0;
    printf(C_BLUE "How much tests would you like to add?\n" C_RESET);

    scan_tests_count(&tests_cnt);

    test_case* tests = (test_case*) calloc(tests_cnt, sizeof(test_case));

    for (unsigned ind = 0; ind < tests_cnt; ind++)
    {        
        printf(C_GREEN "Test %u\n" C_RESET, ind + 1);

        if (coef_input(&tests[ind].a, &tests[ind].b, &tests[ind].c) == INPUT_ERROR)
            return INPUT_ERROR;

        printf(C_BLUE "Enter number of roots (enter \"-1\" for infinite amount of roots):\n" C_RESET);
        
        scan_root_num(&tests[ind].root_num_ref);
        
        //printf("%d\n", tests[ind].root_num_ref);

        input_roots(tests[ind].root_num_ref, &tests[ind].x_1ref, &tests[ind].x_2ref);
    }

    write_tests_in_file(tests, file_name, tests_cnt);

    return 0;
}


void scan_tests_count(unsigned* tests_cnt)
{
    assert(tests_cnt);
    char n = '\0';
    
    while (!(scanf("%u%c", tests_cnt, &n) == 2 && n == '\n'))
        {
            print_input_error(n);
            printf(C_RED "Input error. Try again\n" C_RESET);
        }
}


void scan_root_num(int* root_num_ref)
{
    assert(root_num_ref);
    char n = '\0';
    while (!(scanf("%d%c", root_num_ref, &n) == 2 && n == '\n'
           && INF_ROOTS <= *root_num_ref && *root_num_ref <= TWO_ROOTS)) /*????? */
        {
            print_input_error(n);
            printf(C_RED "Input error. Try again:\n" C_RESET);
        }
}


void input_roots(int root_num_ref, double* x_1ref, double* x_2ref)
{
    assert(x_1ref);
    assert(x_2ref);
    char n = '\0';
    switch (root_num_ref)
        {
            case TWO_ROOTS:
                printf(C_BLUE "Enter these two roots:\n" C_RESET);
                while (!(scanf("%lg %lg%c", x_1ref, x_2ref, &n) == 3 && n == '\n'))
                {
                    print_input_error(n);
                    printf(C_RED "Input error. Try again:\n" C_RESET);
                }
                my_sort(x_1ref, x_2ref);
                break;
            
            case ONE_ROOT:
                printf(C_BLUE "Enter this single root:\n" C_RESET);
                while (!(scanf("%lg%c", x_1ref, &n) == 2 && n == '\n'))
                {
                    print_input_error(n);
                    printf(C_RED "Input error. Try again:\n" C_RESET);
                }
                *x_2ref = NAN;
                break;
            
            case NO_ROOTS:
                *x_1ref = NAN;
                *x_2ref = NAN;
                break;

            case INF_ROOTS:
                *x_1ref = NAN;
                *x_2ref = NAN;
                break;

            default:
                printf(C_RED_BOX "Number of roots = %d\n" C_RESET, root_num_ref);
                assert(0);
        }
}


void write_tests_in_file(test_case tests[], char* file_name, unsigned tests_cnt)
{
    assert(file_name);
    FILE* fp = fopen(file_name, "a");
    if (!fp)
    {
        printf(C_RED_BOX "Can't open the file %s\n" C_RESET, file_name);
        return;
    }

    printf(C_YELLOW "Writing in %s...\n" C_RESET, file_name);

    for(unsigned ind = 0; ind < tests_cnt; ind++)
        print_structure_testcase(tests[ind], fp);

    if (fclose(fp))
        printf(C_RED_BOX "Can't close the file %s\n" C_RESET, file_name);
    else
        printf(C_GREEN "Tests was added successfully\n" C_RESET);

    free(tests);
}


void run_tests()
{
    int tests_completed = 0;
    const int tests_num = 7;

    test_case tests_all[tests_num] = 
    {{.a = 1, .b = -2, .c = 1, .root_num_ref = ONE_ROOT, .x_1ref = 1, .x_2ref = NAN},
    {.a = 1, .b = 0, .c = 0, .root_num_ref = ONE_ROOT, .x_1ref = 0, .x_2ref = NAN},
    {.a = 0, .b = 1, .c = 0, .root_num_ref = ONE_ROOT, .x_1ref = 0, .x_2ref = NAN},
    {.a = 0, .b = 0, .c = 1, .root_num_ref = NO_ROOTS, .x_1ref = NAN, .x_2ref = NAN},
    {.a = 0, .b = 0, .c = 0, .root_num_ref = INF_ROOTS, .x_1ref = NAN, .x_2ref = NAN},
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
    double x_1 = NAN, x_2 = NAN;
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


void print_structure_testcase(test_case test, FILE* fp)
{
    //printf("%d %lg %lg\n", test.root_num_ref, test.x_1ref, test.x_2ref);
    fprintf(fp, "%lg %lg %lg %d %lg %lg\n", test.a, test.b, test.c, test.root_num_ref, test.x_1ref, test.x_2ref);
}
