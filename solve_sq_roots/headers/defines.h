/*!
    \file

    \brief File contains defines for working with colors, defines for numbers of roots and constants
*/

#ifndef DEFINES_H
#define DEFINES_H

#define C_RESET "\033[0m"
#define C_RED "\033[31m"
#define C_GREEN "\033[32m"
#define C_YELLOW "\033[33m"
#define C_BLUE "\033[34m"
#define C_PURPLE "\033[35m" /*for debugging primarily*/ 
#define C_RED_BOX "\033[41m"


/*!
    \brief EPSILON is a very small number used for comparing double numbers
*/
const double EPSILON = 1e-6;


unsigned const MAX_TRIES_COUNT = 10;


/*!
    \brief Determines the numbers corresponding to different numbers of roots
*/
enum number_of_roots
{
    INPUT_ERROR = -2,
    INF_ROOTS = -1,
    NO_ROOTS = 0,
    ONE_ROOT = 1,
    TWO_ROOTS = 2
};

#endif