#include "../headers/defines.h"

#include "../headers/default_solving.h"
#include "../headers/plot.h"
#include "../headers/test.h"
#include "../headers/study.h"


#include <cassert>
#include <cstdio>
#include <cstring>


int main(int argc, char *argv[])
{
    if (argc > 1 && !strcmp(argv[1], "help"))
    {
        printf(C_BLUE "study - practice in solving equations\n"
               "testauto - to run preprogrammed tests\n"
               "test - to run tests from your file\n"
               "testadd - add tests to file\n"
               "plot - draw plot of the function\n"
               "plotwobuf - draw plot w/o buffering\n"
               "or do not type anything if you just want to solve equation\n" C_RESET);
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






/*

сделать документацию (doxygen)

NAN in textcase +
testadd rework +

scan_root_num норм ли так писать?

add input error in print_input_error

*/
