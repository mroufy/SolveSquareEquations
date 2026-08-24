#ifndef DEFINES_H
#define DEFINES_H

#define C_RESET "\033[0m"
#define C_RED "\033[31m"
#define C_GREEN "\033[32m"
#define C_YELLOW "\033[33m"
#define C_BLUE "\033[34m"
#define C_RED_BOX "\033[41m"

const double EPSILON = 1e-6;


enum number_of_roots
{
    INPUT_ERROR = -2,
    INF_ROOTS = -1,
    NO_ROOTS = 0,
    ONE_ROOT = 1,
    TWO_ROOTS = 2
};

void input_clear();
void print_input_error(char c);
int compare_double(double a, double n);
double remove_minus_zero(double n);

#endif