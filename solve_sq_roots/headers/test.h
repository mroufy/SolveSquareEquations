#ifndef TEST_H
#define TEST_H

#include <cstdio>

struct test_case
{
    double a, b, c;
    int root_num_ref;
    double x_1ref, x_2ref;
};

void run_file_tests(char* file_name);

int add_test_file(char* file_name);

void scan_root_num(test_case test);

void scan_tests_count(unsigned* tests_cnt);

void write_tests_in_file(test_case tests[], char* file_name, unsigned tests_cnt);

void input_roots(test_case test);

void run_tests();

int run_one_test(test_case test);

void print_structure_testcase(test_case test, FILE* fp);

#endif