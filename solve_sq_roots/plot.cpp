#include "defines.h"
#include "plot.h"

#include "input_fun.h"

#include <cassert>
#include <cstdio>
#include <cstring>

int draw_graph(char* filename)
{
    double a = 0, b = 0, c = 0;
    if (coef_input(&a, &b, &c) == INPUT_ERROR)
            return INPUT_ERROR;

    int width = 0, height = 0;
    char axis_char = ' ';

    width_and_height_input(&width, &height);

    FILE* fp = fopen(filename, "w");
    if (!fp)
    {
        printf(C_RED_BOX "Can't open the file\n" C_RESET);
        return 0;
    }

    //plot_output(a, b, c, width, height, fp);


    for (int y = height / 2; y >= -height / 2; y--)
    {
        for (int x = -width / 2; x <= width / 2; x++)
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
        printf(C_RED_BOX "Can't close the file\n" C_RESET);
    return 0;
}


int is_dot_on_line(double a, double b, double c, int x, int y)
{
    const double delta_x = 0.5;
    double arg = x;
    arg += delta_x;
    double res_max = a * (arg * arg) + b * arg + c;
    arg -= 2 * delta_x;
    double res_min = a * (arg * arg) + b * arg + c;

    if ((res_min <= y && y <= res_max) || (res_min >= y && y >= res_max))
        return 1;
    else
        return 0;
}


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


int width_and_height_input(int* width, int* height)
{
    char n = ' ';
    int scanf_result = 0;

    printf(C_BLUE "Enter width and height of the graph:\n" C_RESET);
    while (1)
    {
        scanf_result = scanf("%d %d%c", width, height, &n);

        if (scanf_result == 3 && n == '\n')
            return 0;
        else if (*width <= 0 || *height <= 0)
        {
            printf(C_RED "Width and height can't be zero or below. Try again:\n" C_RESET);
            scanf_result = 0;
        }
        else
        {
            print_input_error(n);
            printf(C_RED "Input error. Try again\n" C_RESET);
            scanf_result = 0;
        }
    }
    scanf_result = scanf("%d %d%c", width, height, &n);
}


/*
void plot_output(double a, double b, double c, int width, int height, char* filename)
{
    char axis_char = ' ';
    char buffer[] = "";
    char axis_str[] = "\0";
    for (int y = height / 2; y >= -height / 2; y--)
    {
        for (int x = -width / 2; x <= width / 2; x++)
        {
            if (is_dot_on_line(a, b, c, x, y))
                strcat(buffer, "#");
            else if (is_dot_on_axis(x, y, &axis_char))
            {
                axis_str[0] = axis_char;
                strcat(buffer, axis_str);
            }   
            else
                strcat(buffer, " ");
        }
        strcat(buffer, "\n");
    }

    FILE* fp = fopen(filename, "w");
    if (!fp)
    {
        printf(C_RED_BOX "Can't open the file\n" C_RESET);
        return;
    }

    fprintf(fp, "%s", buffer);
}
*/
