/*!
    \file

    \brief File contains functions that help working with math
*/
#include "../headers/defines.h"
#include "../headers/mymath.h"

#include <cassert>
#include <cmath>


/*!
    \brief Compares two double numbers

    \param [in] num1, num2 numbers to compare

    \return If they are within an EPSILON or they are both NAN it returns 1
    \return If not it returns 0

    \warning Do not use for infinite numbers
*/
int compare_double(double num1, double num2)
{
    assert(!isinf(num1));
    assert(!isinf(num2));

    //printf(C_PURPLE "a = %lg, n = %lg\n" C_RESET, a, n);

    if (isnan(num1) && isnan(num2))
        return 1;

    return (fabs(num1 - num2) < EPSILON);
}


/*!
    \brief Removes minus from zero if it's a minus zero

    \param [in] n number that we need to

    \return Function returns 0 if gets double number near 0.
    \return Else returns what it gets.

    \warning Do not use for infinite numbers.
*/
double remove_minus_zero(double n)
{
    if (compare_double(n, 0))
        return 0;
    else
        return n;
}


/*!
    \brief Sorts 2 numbers in increasing order

    \param [in, out] num1, num2 numbers that will be sorted

    \returns Sorted 2 numbers

    \warning Do not use for infinite numbers
*/
void my_sort(double* num1, double* num2)
{
    assert(num1);
    assert(num2);
    assert(!isinf(*num1));
    assert(!isinf(*num2));

    if (*num1 > *num2)
    {
        double buf_num = *num1;
        *num1 = *num2;
        *num2 = buf_num;
    }
}
