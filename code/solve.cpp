/*!
    \file
    \brief Solve functions
    
    This file contains functions for solving square equations.
*/
#include "../headers/defines.h"
#include "../headers/solve.h"

#include "../headers/mymath.h"

#include <cassert>
#include <cmath>


/*!
    \defgroup solve_sq Solve square equation

    \brief Solves square equation
*/
/*!
    \ingroup solve_sq

    \brief Solves any square equations

    \param[in] a, b, c coefficient of an equation
    \param[out] x_1, x_2 roots of an equation

    \return number of roots
*/
int solve_square_equation(double a, double b, double c, double *x_1, double *x_2)
{
    assert(x_1);
    assert(x_2);

    if (compare_double(a, 0))
    {
        return solve_linear_equation(b, c, x_1);
    }
    else
    {
        return solve_full_square_equation(a, b, c, x_1, x_2);
    }
}


/*!
    \ingroup solve_sq
    
    \brief Solves only full square equations

    \param[in] a, b, c coefficient of an equation
    \param[out] x_1, x_2 roots of an equation

    \return number of roots
*/

int solve_full_square_equation(double a, double b, double c, double *x_1, double *x_2)
{
    assert(x_1);
    assert(x_2);

    double dis = b * b - 4 * a * c;

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


/*!
    \ingroup solve_sq
    
    \brief Solves linear equations

    \param[in] k, b coefficient of an equation kx + b = 0
    \param[out] x_1 root of an equation
    
    \return number of roots
*/
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
