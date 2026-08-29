/*!
    \file

    \brief Main decides in which mode program will run and help mode to help user with choosing mode.
*/
#include "../headers/defines.h"

#include "../headers/default_solving.h"
#include "../headers/plot.h"
#include "../headers/test.h"
#include "../headers/study.h"

#include "default_solving.cpp"
#include "plot.cpp"
#include "test.cpp"
#include "study.cpp"
#include "input_fun.cpp"
#include "mymath.cpp"
#include "solve.cpp"

#include <cassert>
#include <cstdio>
#include <cstring>

void help_output();


/*!
    \brief Main

    \brief Main chooses mode that program will run in by using command-line arguments

    \param[in] argc number of command-line arguments
    \param[in] argv array of command-line arguments

    \return 0
*/
int main(int argc, char *argv[])
{
    assert(argv);

    if (argc > 1 && !strcmp(argv[1], "help"))
    {
        help_output();
        return 0;
    }

    else if (argc > 1 && !strcmp(argv[1], "study"))
    {
        study_mode();
        return 0;
    }

    else if (argc > 1 && !strcmp(argv[1], "testauto"))
    {
        run_tests();
        return 0;
    }

    else if (argc > 2 && !strcmp(argv[1], "test"))
    {
        run_file_tests(argv[2]);
        return 0;
    }

    else if (argc > 2 && !strcmp(argv[1], "testadd"))
    {
        add_test_file(argv[2]);
        return 0;
    }

    else if (argc > 2 && !strcmp(argv[1], "plot"))
    {
        draw_plot(argv[2]);
        return 0;
    }

    else if (argc > 2 && !strcmp(argv[1], "plotwobuf"))
    {
        draw_plot_wo_buffering(argv[2]);
        return 0;
    }

    else
    {
        regular_solve();
        return 0;
    }
}


/*!
    \brief Prints commands that user can type in command-line arguments
    to choose mode that program will run in
*/
void help_output()
{
    printf(C_BLUE "study - practice in solving equations\n"
               "testauto - run preprogrammed tests\n"
               "test <filename> - to run tests from your file\n"
               "testadd <filename> - add tests to file\n"
               "plot <filename> - draw plot of the function\n"
               "plotwobuf <filename> - draw plot w/o buffering\n"
               "or do not type anything if you just want to solve equation\n" C_RESET);
}







/*
do main with switch and enum

scan_root_num норм ли так писать?

refactor all code
*/
