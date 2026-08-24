#include "defines.h"
#include "mymath.h"

#include <cassert>
#include <cmath>


int compare_double(double a, double n)
{
    //printf("a = %lg, n = %lg\n", a, n);
    assert(!isinf(a) && !isinf(n));
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
