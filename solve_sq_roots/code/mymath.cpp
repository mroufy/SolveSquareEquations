#include "../headers/defines.h"
#include "../headers/mymath.h"

#include <cassert>
#include <cmath>


int compare_double(double a, double n)
{
    assert(!isinf(a) && !isinf(n));
    //printf("a = %lg, n = %lg\n", a, n);

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


void my_sort(double* num1, double* num2)
{
    assert(num1 && num2);

    if (*num1 > *num2)
    {
        double buf_num = *num1;
        *num1 = *num2;
        *num2 = buf_num;
    }
}
