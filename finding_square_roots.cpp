#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define C_RESET "\033[0m"
#define C_RED "\033[31m"
#define C_GREEN "\033[32m"
#define C_YELLOW "\033[33m"
#define C_BLUE "\033[34m"
#define C_RED_BOX "\033[41m"

const double EPSILON = 1e-6;

struct test_case
{
    double a, b, c;
    int root_num_ref;
    double x_1ref, x_2ref;
};

void run_file_tests(char* file_name);
int add_test_file(char* file_name);
void run_tests();
int run_one_test(test_case test);
void print_structure_test(test_case test);
int coef_input(double *a, double *b, double *c);
void input_clear();
int input_check();
int solve_square_equation(double a, double b, double c, double *x_1, double *x_2);
int solve_full_square_equation(double a, double b, double c, double *x_1, double *x_2);
int find_discriminant(double a, double b, double c);
int solve_linear_equation(double k, double b, double *x_1);
void output_roots(int root_num, double *x_1, double *x_2);
int compare_double(double a, double n);
double remove_minus_zero(double n);
void print_input_error(char c);
int time_to_reply(int s);

enum number_of_roots
{
    INPUT_ERROR = -2,
    INF_ROOTS = -1,
    NO_ROOTS = 0,
    ONE_ROOT = 1,
    TWO_ROOTS = 2
};


int main(int argc, char *argv[])
{
    srand(time(NULL));
    int token_num = rand() / 1000;
    if (rand() % 2)
    {
        printf("%sРешение квадратичных уравнений пока не поддерживается в вашей стране. Мы сообщим, когда это изменится.%s\n", C_RED, C_RESET);
        system("say 'Решение квадратичных уравнений пока не поддерживается в вашей стране. Мы сообщим, когда это изменится.'");
        return 0;
    }
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


void run_file_tests(char* file_name)
{
    FILE* fp = fopen(file_name, "r");
    test_case test = {};
    int scanf_result = fscanf(fp, "%lg %lg %lg %d %lg %lg\n", &test.a, &test.b, &test.c, &test.root_num_ref, &test.x_1ref, &test.x_2ref);
    while (scanf_result == 6)
    {
        if (run_one_test(test))
            printf("%sTest completed\n%s", C_GREEN, C_RESET);
        scanf_result = fscanf(fp, "%lg %lg %lg %d %lg %lg\n", &test.a, &test.b, &test.c, &test.root_num_ref, &test.x_1ref, &test.x_2ref);
    }
}


int add_test_file(char* file_name)
{
    FILE* fp = fopen(file_name, "a");
    int scanf_result = 0;
    while (1)
    {
        char n = '\0';
        test_case test = {};
        printf("%sEnter coefficients, number of roots, roots(a b c root_num x_1 x_2)\n%s", C_BLUE, C_RESET);
        scanf_result = scanf("%lg %lg %lg %d %lg %lg%c", &test.a, &test.b, &test.c, &test.root_num_ref, &test.x_1ref, &test.x_2ref, &n);
        if (scanf_result == 7 && n == '\n')
        {
            fprintf(fp, "%lg %lg %lg %d %lg %lg\n", test.a, test.b, test.c, test.root_num_ref, test.x_1ref, test.x_2ref);
            return 1;
        }
        else
        {
            print_input_error(n);
            printf("%sInput error. Try again\n%s", C_RED, C_RESET);
        }
    }
}


void run_tests()
{
    int tests_completed = 0;
    const int tests_num = 7;

    test_case test1 = {.a = 1, .b = -2, .c = 1, .root_num_ref = ONE_ROOT, .x_1ref = 1};
    test_case test2 = {.a = 1, .b = 0, .c = 0, .root_num_ref = ONE_ROOT, .x_1ref = 0};
    test_case test3 = {.a = 0, .b = 1, .c = 0, .root_num_ref = ONE_ROOT, .x_1ref = 0};
    test_case test4 = {.a = 0, .b = 0, .c = 1, .root_num_ref = NO_ROOTS};
    test_case test5 = {.a = 0, .b = 0, .c = 0, .root_num_ref = INF_ROOTS};
    test_case test6 = {.a = 1, .b = -5, .c = 6, .root_num_ref = TWO_ROOTS, .x_1ref = 2, .x_2ref = 3};
    test_case test7 = {.a = 1, .b = -13, .c = 42, .root_num_ref = TWO_ROOTS, .x_1ref = 6, .x_2ref = 8};
    
    #define TEST(a) test ## a
    
    /*for (int i = 1; i <= tests_num; ++i)
    {
        tests_completed += run_one_test(TEST(i)); //"test1" -> test1
    }*/
    tests_completed += run_one_test(test1);
    tests_completed += run_one_test(test2);
    tests_completed += run_one_test(test3);
    tests_completed += run_one_test(test4);
    tests_completed += run_one_test(test5);
    tests_completed += run_one_test(test6);
    tests_completed += run_one_test(test7);

    if (tests_completed == tests_num)
        printf("%sAll tests completed %d/%d\n%s", C_GREEN, tests_completed, tests_num, C_RESET);
    else
        printf("%sTests completed %d/%d\n%s", C_YELLOW, tests_completed, tests_num, C_RESET);
}


int run_one_test(test_case test)
{
    double x_1 = 0, x_2 = 0;
    int root_num = solve_square_equation(test.a, test.b, test.c, &x_1, &x_2);

    x_1 = remove_minus_zero(x_1);
    x_2 = remove_minus_zero(x_2);

    if (root_num != test.root_num_ref || !(compare_double(x_1, test.x_1ref)) || !(compare_double(x_2, test.x_2ref)))
    {
        printf("%sTest FAILED: a = %lg, b = %lg, c = %lg\n"
            "Expected %d roots, x_1 = %lg, x_2 = %lg\n"
            "Got %d roots, x_1 = %lg, x_2 = %lg\n%s",
            C_RED, test.a, test.b, test.c, test.root_num_ref, test.x_1ref, test.x_2ref, root_num, x_1, x_2, C_RESET);
        return 0;
    }
    else
        return 1;
}


void print_structure_test(test_case test)
{
    printf("%lg %lg %lg %d %lg %lg\n", test.a, test.b, test.c, test.root_num_ref, test.x_1ref, test.x_2ref);
}

int coef_input(double *a, double *b, double *c)
{
    assert(a);
    assert(b);
    assert(c);

    int scanf_result = 0, tries_count = 0;
    char n = 0;

    printf("%sЭщкере я НАНО-АИ-ГПТ-67. Я умею решать сложнейшие, лютейшие квадратичные уравнения, только введите коффициенты\n%s",
             C_BLUE, C_RESET);
    system("say 'Эщкере я НАНО-АИ-ГПТ-67. Я умею решать сложнейшие, лютейшие квадратичные уравнения, только введите коффициенты'");

    while (1)
    {

        scanf_result = scanf("%lg %lg %lg%c", a, b, c, &n);
        usleep(time_to_reply(1));
        if (scanf_result == 4 && n == '\n')
        {
            printf("Хм... Дайте подумать...\n");
            system("say 'Хм... Дайте подумать'");
            return 0;
        }
        else
        {
            usleep(time_to_reply(1));
            print_input_error(n);
            usleep(time_to_reply(1));
            //printf("%sInput error. Try again\n%s", C_RED, C_RESET);
            printf("%sОшибка ввода.%s\n", C_RED, C_RESET);
            system("say 'Ошибка ввода'");
            usleep(time_to_reply(1));
            printf("%sПопробуйте еще раз\n%s", C_RED, C_RESET);
            system("say 'Попробуйте ещё раз'");
            scanf_result = 0;
        }

        ++tries_count;
        if (tries_count >= 10)
        {
            printf("%sMax number of tries reached\n%s", C_RED_BOX, C_RESET);
            return INPUT_ERROR;
        }

        printf("%sВведите коэффициенты\n%s",
             C_BLUE, C_RESET);
        system("say 'Введите коффициенты'");
    }
}


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


int solve_square_equation(double a, double b, double c, double *x_1, double *x_2)
{
    assert(x_1);
    assert(x_2);

    if (a == 0)
    {
        return solve_linear_equation(b, c, x_1);
    }
    else
    {
        return solve_full_square_equation(a, b, c, x_1, x_2);
    }
}


int solve_full_square_equation(double a, double b, double c, double *x_1, double *x_2)
{
    assert(x_1);
    assert(x_2);

    int dis = find_discriminant(a, b, c);

    if (dis < 0)
    {
        return NO_ROOTS;
    }
    else if (compare_double(dis, 0))
    {
        *x_1 = -b / (2 * a);
        return ONE_ROOT;
    }
    else
    {
        *x_1 = (-b - sqrt(dis)) / (2 * a);
        *x_2 = (-b + sqrt(dis)) / (2 * a);
        return TWO_ROOTS;
    }
}


int find_discriminant(double a, double b, double c)
{
    return b * b - 4 * a * c;
}


int solve_linear_equation(double k, double b, double *x_1)
{
    assert(x_1);
    
    if (compare_double(k, 0.0))
    {
        if (compare_double(b, 0.0))
        {
            return INF_ROOTS;
        }
        else
        {
            return NO_ROOTS;
        }
    }
    *x_1 = -b / k;
    return ONE_ROOT;
}


void output_roots(int root_num, double *x_1, double *x_2)
{
    assert(x_1);
    assert(x_2);

    *x_1 = remove_minus_zero(*x_1);
    *x_2 = remove_minus_zero(*x_2);

    usleep(time_to_reply(5));

    switch (root_num)
    {
    case NO_ROOTS:
        printf("%sВоу у этого уравнения нет ни одного решения\n%s", C_YELLOW, C_RESET);
        system("say 'Воу у этого уравнения нет ни одного решения'");
        usleep(time_to_reply(2));

        break;
    case ONE_ROOT:
        printf("%sЭто уравнение имеет всего один корень и это: %lg\n%s", C_YELLOW, *x_1, C_RESET);
        system("say 'Это уравнение имеет всего один корень и это: '");
        usleep(time_to_reply(2));
        
        break;
    case TWO_ROOTS:
        printf("%sЭто уравнение имеет целых два корня, один из них это %lg, а второй корень это %lg\n%s", C_GREEN, *x_1, *x_2, C_RESET);
        system("say 'Это уравнение имеет целых два корня, один из них это , а второй корень это '");
        usleep(time_to_reply(2));
        break;
    case INF_ROOTS:
        printf("%sПравильным ответом на эту задачу будет являться бесконечное количество корней\n%s", C_GREEN, C_RESET);
        system("say 'Правильным ответом на эту задачу будет являться бесконечное количество корней'");
        usleep(time_to_reply(2));
        break;
    default:
        printf("%sRoot count error\n%s", C_RED, C_RESET);
    }
}


int compare_double(double a, double n)
{
    if (isnan(a) && isnan(n))
        return 1;
    return (fabs(a - n) < EPSILON);
}


double remove_minus_zero(double n)
{
    if (compare_double(n, 0))
        return 0;
    else
        return n;
}


int time_to_reply(int s)
{
    s = s * 1e6;
    return (rand() % s + s) / 2;
}


