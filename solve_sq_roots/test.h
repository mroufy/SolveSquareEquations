#ifndef TEST_H
#define TEST_H

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

#endif