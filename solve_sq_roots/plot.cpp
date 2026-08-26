#include "defines.h"
#include "plot.h"

#include "input_fun.h"

#include <cassert>
#include <cstdio>

int draw_graph(char* filename)
{
    double a = 0, b = 0, c = 0;
    if (coef_input(&a, &b, &c) == INPUT_ERROR)
            return INPUT_ERROR;

    FILE* fp = fopen(filename, "w");
    if (!fp)
    {
        printf(C_RED_BOX "Can't open the file\n" C_RESET);
        return 0;
    }

    int width = 0, height = 0;
    char axis_char = ' ';

    printf("Enter width and height of the graph:\n");
    scanf("%d %d", &width, &height);
    while (width <= 0 || height <= 0)
    {
        printf("Width and height can't be zero or below. Try again:\n");
        scanf("%d %d", &width, &height);
    }
    assert(width > 0 && height > 0);

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
    double arg = x; //обрезается на 0
    arg += 0.5;
    double res_max = a * (arg * arg) + b * arg + c;
    arg -= 1.0;
    double res_min = a * (arg * arg) + b * arg + c;
    if ((res_min <= y && y <= res_max) || (res_min >= y && y >= res_max))
        return 1;
    else
        return 0;
}


char is_dot_on_axis(int x, int y, char* axis_char)
{
    assert(axis_char);
    if (!x && !y)
    {
        *axis_char = 'O';
        return 1;
    }
    else if (!x)
    {
        *axis_char = '|';
        return 1;
    }
    else if (!y)
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