#include "../headers/defines.h"
#include "../headers/plot.h"

#include "../headers/input_fun.h"

#include <cassert>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>

int draw_plot(char* file_name)
{
    assert(file_name);

    double a = 0, b = 0, c = 0;
    if (coef_input(&a, &b, &c) == INPUT_ERROR)
            return INPUT_ERROR;

    unsigned width = 0, height = 0;

    width_and_height_input(&width, &height);
    //printf(C_PURPLE "width = %u, height = %u\n" C_RESET, width, height);

    plot_output(a, b, c, width, height, file_name);

    return 0;
}


void plot_output(double a, double b, double c, unsigned width, unsigned height, char* file_name)
{
    assert(file_name);
    
    //printf(C_PURPLE "width = %u, height = %u\n" C_RESET, width, height);

    char axis_char = ' ';
    char* buffer = (char*) calloc(((width + 1) * height), sizeof(double));
    unsigned ind = 0;

    printf(C_YELLOW "Generating plot...\n" C_RESET);

    for (int y = int(height) / 2; y >= -int(height) / 2; y--)
    {
        //printf(C_PURPLE "%u\n" C_RESET, ind); //
        //printf(C_PURPLE "width = %u, height = %u\n" C_RESET, width, height);

        for (int x = -int(width) / 2; x <= int(width) / 2; x++)
        {
            //printf(C_PURPLE "x = %d, width = %u\n" C_RESET, x, width);
            if (is_dot_on_line(a, b, c, x, y))
                buffer[ind] = '#';
            else if (is_dot_on_axis(x, y, &axis_char))
                buffer[ind] = axis_char;  
            else
                buffer[ind] = ' ';

            ind++;
        }
        //strcat(buffer, "\n");
        buffer[ind] = '\n';
        ind++;
    }
    write_buffer_in_file(buffer, file_name);
}


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


int draw_plot_wo_buffering(char* file_name)
{
    assert(file_name);

    double a = 0, b = 0, c = 0;
    if (coef_input(&a, &b, &c) == INPUT_ERROR)
            return INPUT_ERROR;

    unsigned width = 0, height = 0;

    width_and_height_input(&width, &height);
    //printf(C_PURPLE "width = %u, height = %u\n" C_RESET, width, height);

    plot_output_wo_buffering(a, b, c, width, height, file_name);

    return 0;
}


void plot_output_wo_buffering(double a, double b, double c, unsigned width, unsigned height, char *file_name)
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
    for (int y = int(height) / 2; y >= -int(height) / 2; y--)
    {
        for (int x = -int(width) / 2; x <= int(width) / 2; x++)
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


int is_dot_on_line(double a, double b, double c, int x, int y)
{
    const double delta_x = 0.5;
    double arg = x;
    /*calculating y near x*/
    arg += delta_x;
    double res_1 = a * (arg * arg) + b * arg + c;
    arg -= 2 * delta_x;
    double res_2 = a * (arg * arg) + b * arg + c;

    // y have to be in between res_1 and res_2
    return ((res_2 <= y && y <= res_1) || (res_2 >= y && y >= res_1));
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


void width_and_height_input(unsigned* width, unsigned* height)
{
    assert(width);
    assert(height);

    char n = ' ';
    int scanf_result = 0;

    printf(C_BLUE "Enter width and height of the graph:\n" C_RESET);
    while (1)
    {
        scanf_result = scanf("%u %u%c", width, height, &n);

        if (scanf_result == 3 && n == '\n')
            return;
        /*else if (*width <= 0 || *height <= 0)
        {
            printf(C_RED "Width and height can't be zero or below. Try again:\n" C_RESET);
            scanf_result = 0;
        }*/
        else
        {
            print_input_error(n);
            printf(C_RED "Input error. Try again\n" C_RESET);
            scanf_result = 0;
        }
    }
}
