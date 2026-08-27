#include "../headers/defines.h"
#include "../headers/plot.h"

#include "../headers/input_fun.h"

#include <cassert>
#include <cstddef>
#include <cstdio>
#include <cstring>

int draw_plot(char* filename)
{
    double a = 0, b = 0, c = 0;
    if (coef_input(&a, &b, &c) == INPUT_ERROR)
            return INPUT_ERROR;

    int width = 0, height = 0;

    width_and_height_input(&width, &height);
    //printf(C_PURPLE "width = %d, height = %d\n" C_RESET, width, height);

    plot_output(a, b, c, width, height, filename);

    return 0;
}


int draw_plot_wo_buffering(char* filename)
{
    double a = 0, b = 0, c = 0;
    if (coef_input(&a, &b, &c) == INPUT_ERROR)
            return INPUT_ERROR;

    int width = 0, height = 0;

    width_and_height_input(&width, &height);
    //printf(C_PURPLE "width = %d, height = %d\n" C_RESET, width, height);

    plot_output_wo_buffering(a, b, c, width, height, filename);

    return 0;
}


int is_dot_on_line(double a, double b, double c, int x, int y)
{
    const double delta_x = 0.5;
    double arg = x;
    arg += delta_x;
    double res_1 = a * (arg * arg) + b * arg + c;
    arg -= 2 * delta_x;
    double res_2 = a * (arg * arg) + b * arg + c;

    // y have to be in between res_1 and res_2
    if ((res_2 <= y && y <= res_1) || (res_2 >= y && y >= res_1))
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


void width_and_height_input(int* width, int* height)
{
    char n = ' ';
    int scanf_result = 0;

    printf(C_BLUE "Enter width and height of the graph:\n" C_RESET);
    while (1)
    {
        scanf_result = scanf("%d %d%c", width, height, &n);

        if (scanf_result == 3 && n == '\n')
            return;
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
}



void plot_output(double a, double b, double c, int width, int height, char* filename)
{
    //printf(C_PURPLE "width = %d, height = %d\n" C_RESET, width, height);

    char axis_char = ' ';
    char buffer[] = "";
    char axis_str[] = " ";

    for (int y = height / 2; y >= -height / 2; y--)
    {
        printf(C_PURPLE "width = %d, height = %d\n" C_RESET, width, height);
        for (int x = -width / 2; x <= width / 2; x++)
        {
            //printf("x = %d, width = %d\n", x, width);
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
        printf("param\n");
        strcat(buffer, "\n");
    }

    FILE* fp = fopen(filename, "w");
    if (!fp)
    {
        printf(C_RED_BOX "Can't open the file\n" C_RESET);
        return;
    }

    fprintf(fp, "%s", buffer);

    if (fclose(fp))
        printf(C_RED_BOX "Can't close the file\n" C_RESET);
}


void plot_output_wo_buffering(double a, double b, double c, int width, int height, char *filename)
{
    char axis_char = ' ';

    FILE* fp = fopen(filename, "w");
    if (!fp)
    {
        printf(C_RED_BOX "Can't open the file\n" C_RESET);
        return;
    }
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
}
