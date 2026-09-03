/*!
    \file

    \brief File contains functions for creating and printing plot in a file
*/
#include "../headers/defines.h"
#include "../headers/plot.h"

#include "../headers/input_fun.h"
//#include "../headers/mymath.h"

#include <cassert>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>


///*!
//    \defgroup plot Plot
//
//    \brief
//*/
///*!
//    \ingroup plot
//
//    \brief
//
//    \param [in] file_name name of a file with a plot
//*/
//int plot_only(char* file_name)
//{
//    assert(file_name);
//
//    double a = 0, b = 0, c = 0;
//    if (coef_input(&a, &b, &c) == INPUT_ERROR)
//            return INPUT_ERROR;
//
//    int width = 0, height = 0;
//
//    width_and_height_input(&width, &height);
//    //printf(C_PURPLE "width = %d, height = %d\n" C_RESET, width, height);
//
//    char* buffer = (char*) calloc(((width + 1) * height), //(width + 1) because of symbol '\n' at the end
//                             sizeof(double));
//
//    generate_blank_plot(width, height, buffer);
//
//    draw_function(a, b, c, width, height, buffer);
//
//    write_buffer_in_file(buffer, file_name);
//
//    return 0;
//}
//
//
///*!
//    \ingroup plot
//
//    \brief Generates blank lines in a buffer for further filling
//
//    \param [in] width, height dimensions of a plot
//    \param [in, out] buffer array of chars with a plot in it (program clears buffer in the end)
//*/
//void generate_blank_plot(int width, int height, char* buffer)
//{
//    assert(buffer);
//
//    int ind = 0;
//
//    for (int y = height / 2; y >= - height / 2; y--)
//    {
//        for (int x = - width / 2; x <= width  / 2; x++) // rewrite
//        {
//            buffer[ind] = ' ';
//
//            ind++;
//        }
//
//        buffer[ind] = '\n';
//        ind++;
//    }
//}
//
//
///*!
//    \ingroup plot
//
//    \brief Draws function in buffer with clear plot without anything
//
//    \param [in] a, b, c coefficients
//    \param [in] width, height dimensions of a plot
//    \param [in, out] buffer array of chars with a plot in it (program clears buffer in the end)
//*/
//void draw_function(double a, double b, double c, int width, int height, char* buffer)
//{
//    double y_old = find_y(a, b, c, - width / 2 - 1);
//    double y = 0;
//
//    for (int x = - width / 2; x <= width / 2; x++)
//    {
//        y = find_y(a, b, c, x);
//
//        draw_line_for_x(x, y_old, y, width, height, buffer);
//        y_old = y;
//    }
//}
//
//
///*!
//    \ingroup plot
//
//    \brief finds an y value for quadratic function for one x value
//
//    \param [in] a, b, c coefficients
//    \param [in] x argument of the function
//
//    \return y value
//*/
//double find_y(double a, double b, double c, int x)
//{
//    return a * (x * x) + b * x + c;
//}
//
//
///*!
//    \ingroup plot
//
//    \brief 
//*/
//void draw_line_for_x(int x, double y_old, double y, int width, int height, char* buffer)
//{
//    int ind = 0;
//
//    my_sort(&y_old, &y);
//
//    check_for_plot_range(&y_old, height);
//    check_for_plot_range(&y, height);
//
//    for (int y_current = (int) y_old; y_current <= (int) y; y_current++)
//    {
//        
//        ind = (height / 2 - y_current) * (width + 1) * (x + width / 2);
//        buffer[ind] = '#';
//    }
//}
//
//
///*!
//    \ingroup plot
//
//    \brief The function checks whether y lies on the graph and replaces it with the extreme value present on the graph
//    if not value stays the same
//
//    \param [in, out] y changes in depend of plot dimensions
//    \param [in] height used to decide whether y is lying on the graph or not
//*/
//void check_for_plot_range(double* y, int height);
//{
//    if (- height / 2 > y || y > height / 2)

//}



/*!
    \defgroup draw_plot_buf Draw plot with buffering

    \brief Generates a plot in a buffer, and outputs it in a file

    \warning Can't generate a plot bigger than ~40000x40000
*/
/*!
    \ingroup draw_plot_buf

    \brief Draws a plot (Links the group)

    This function gets coefficients a, b, c from input line, 
    gets width and height of a plot, 
    generates plot with function (y = ax^2 + bx + c) in buffer, 
    writes buffer in a file with name that it gets in arguments.

    \param [in] file_name name of a file to output plot

    \return INPUT_ERROR if maximum of attempts for input reached
    \return Else returns 0

    \warning Can't generate a plot bigger than ~40000x40000
*/
int draw_plot(char* file_name)
{
    assert(file_name);

    double a = 0, b = 0, c = 0;
    if (coef_input(&a, &b, &c) == INPUT_ERROR)
            return INPUT_ERROR;

    int width = 0, height = 0;

    width_and_height_input(&width, &height);
    //printf(C_PURPLE "width = %d, height = %d\n" C_RESET, width, height);

    plot_output(a, b, c, width, height, file_name);

    return 0;
}


/*!
    \ingroup draw_plot_buf

    \brief Creates plot in a buffer and outputs it in a file with name that it gets in arguments

    \param [in] a, b, c coefficients
    \param [in] width, height dimensions of a plot
    \param [in] file_name name of a file to output a plot
*/
void plot_output(double a, double b, double c, int width, int height, char* file_name)
{
    assert(file_name);
    
    //printf(C_PURPLE "width = %d, height = %d\n" C_RESET, width, height);

    char axis_char = ' ';
    char* buffer = (char*) calloc((size_t) ((width + 1) * height), //(width + 1) because of symbol '\n' at the end
                             sizeof(double));
    unsigned ind = 0;

    printf(C_YELLOW "Generating plot...\n" C_RESET);

    for (int y = height / 2; y >= - height / 2; y--)
    {
        //printf(C_PURPLE "%u\n" C_RESET, ind); //
        //printf(C_PURPLE "width = %d, height = %d\n" C_RESET, width, height);

        for (int x = - width / 2; x <= width / 2; x++)
        {
            if (is_dot_on_line(a, b, c, x, y))
                buffer[ind] = '#';
            else if (is_dot_on_axis(x, y, &axis_char))
                buffer[ind] = axis_char;  
            else
                buffer[ind] = ' ';

            ind++;
        }

        buffer[ind] = '\n';
        ind++;
    }
    write_buffer_in_file(buffer, file_name);
}


/*!
    \brief Writes list of chars in file with name that it gets in arguments.

    \param [in] buffer array of chars with a plot in it (program clears buffer in the end)
    \param [in] file_name name of a file to output a plot
*/
void write_buffer_in_file(char* buffer, char* file_name)
{
    assert(buffer);
    assert(file_name);

    FILE* fp = fopen(file_name, "w");
    if (!fp)
    {
        printf(C_RED_BOX "Can't open the file %s\n" C_RESET, file_name);
        return;
    }

    printf(C_YELLOW "Writing in %s...\n" C_RESET, file_name);

    //printf(C_PURPLE "%s" C_RESET, buffer);
    fprintf(fp, "%s", buffer);

    if (fclose(fp))
        printf(C_RED_BOX "Can't close the file %s\n" C_RESET, file_name);
    else
        printf(C_GREEN "Plot was created successfully\n" C_RESET);

    free(buffer);
}


/*!
    \defgroup draw_plot_wo_buf Draw plot without buffering

    \brief Generates a plot in a file without any buffering
*/
/*!
    \ingroup draw_plot_wo_buf

    \brief Draws a plot without buffering

    This function gets coefficients a, b, c from input line, 
    gets width and height of a plot, 
    generates plot with function (y = ax^2 + bx + c) in a file with name that it gets in arguments.

    \param [in] file_name name of a file to output a plot

    \return INPUT_ERROR if maximum of attempts for input reached
    \return Else returns 0

    \warning Program is constantly working with a file while it creating a plot
*/
int draw_plot_wo_buffering(char* file_name)
{
    assert(file_name);

    double a = 0, b = 0, c = 0;
    if (coef_input(&a, &b, &c) == INPUT_ERROR)
            return INPUT_ERROR;

    int width = 0, height = 0;

    width_and_height_input(&width, &height);
    //printf(C_PURPLE "width = %d, height = %d\n" C_RESET, width, height);

    plot_output_wo_buffering(a, b, c, width, height, file_name);

    return 0;
}


/*!
    \ingroup draw_plot_wo_buf

    \brief Generates plot in a file with name that it gets in arguments

    \param [in] a, b, c coefficients
    \param [in] width, height dimensions of a plot
    \param [in] file_name name of a file to output a plot

    \warning Program is constantly working with a file while it creating a plot
*/
void plot_output_wo_buffering(double a, double b, double c, int width, int height, char *file_name)
{
    assert(file_name);

    char axis_char = ' ';

    printf(C_YELLOW "Generating plot and writing...\n" C_RESET);

    FILE* fp = fopen(file_name, "w");
    if (!fp)
    {
        printf(C_RED_BOX "Can't open the file %s\n" C_RESET, file_name);
        return;
    }

    for (int y = height / 2; y >= - height / 2; y--)
    {
        for (int x = - width / 2; x <= width / 2; x++)
        {
            if (is_dot_on_line(a, b, c, x, y))
                fprintf(fp, "#");
            else if (is_dot_on_axis(x, y, &axis_char))
                fprintf(fp, "%c", axis_char);
            else
                fprintf(fp, " ");
        }
        fprintf(fp, "\n");
    }

    if (fclose(fp))
        printf(C_RED_BOX "Can't close the file %s\n" C_RESET, file_name);
    else
        printf(C_GREEN "Plot was created successfully\n" C_RESET);
}


/*!
    \brief Checks if dot(x; y) on a line of function

    Checks if range of results of a function for [x - delta_x; x + delta_x] contents y.

    \param [in] a, b, c coefficients
    \param [in] x, y dot coordinates

    \return 1 if on a line
    \return 0 if not
*/
int is_dot_on_line(double a, double b, double c, int x, int y)
{
    const double delta_x = 0.5;

    double arg = x;

    /*calculating equation near x*/
    arg += delta_x;
    double res_1 = a * (arg * arg) + b * arg + c;

    arg -= 2 * delta_x;
    double res_2 = a * (arg * arg) + b * arg + c;

    // y have to be in between res_1 and res_2
    return ((res_2 <= y && y <= res_1) || (res_2 >= y && y >= res_1));
}


/*!
    \brief Checks if dot(x; y) is on an axis

    Checks if x == 0 or y == 0 and returns axis symbol

    \param [in] x, y dot coordinates
    \param [out] axis_char axis symbol

    \return 'O' - for cross of axis
    \return '-' - for x axis
    \return '|' - for y axis
    \return ' ' - if not on axis
*/
char is_dot_on_axis(int x, int y, char* axis_char)
{
    assert(axis_char);

    if (x == 0 && y == 0)
    {
        *axis_char = 'O';
        return 1;
    }
    else if (x == 0)
    {
        *axis_char = '|';
        return 1;
    }
    else if (y == 0)
    {
        *axis_char = '-';
        return 1;
    }
    else
    {
        *axis_char = ' ';
        return 0;
    }
}


/*!
    \brief Gets width and height from input line

    \param [out] width, height dimensions of a plot

    \return INPUT_ERROR if number of tries reached MAX_TRIES_COUNT = 10
    \return else returns 0
*/
int width_and_height_input(int* width, int* height)
{
    assert(width);
    assert(height);

    char n = ' ';

    printf(C_BLUE "Enter width and height of the graph:\n" C_RESET);

    int scanf_result = 0;

    for (unsigned tries_count = 0; tries_count <= MAX_TRIES_COUNT; tries_count++)
    {
        scanf_result = scanf("%d %d%c", width, height, &n);
        if (scanf_result == 3 && n == '\n')
            return 0;
        
        else if (*width < 0 || *height < 0)
        {
            printf("height and width can't be below zero\n");
            input_clear();
            scanf_result = 0;
            n = '\0';
        }

        else
        {
            print_input_error(n);
            scanf_result = 0;
            n = '\0';
        }
    }

    printf(C_RED_BOX "Max number of tries reached!\n" C_RESET);
    return INPUT_ERROR;
}
