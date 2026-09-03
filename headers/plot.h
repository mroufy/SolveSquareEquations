/*!
    \file

    \brief File contains prototypes of functions for plot.cpp
*/

#ifndef PLOT_H
#define PLOT_H

//int plot_only(char* file_name);
//
//void generate_blank_plot(int width, int height, char* buffer);
//
//void draw_function(double a, double b, double c, int width, int height, char* buffer);
//
//double find_y(double a, double b, double c, int x);
//
//void draw_line_for_x(int x, double y_old, double y, int width, int height, char* buffer);

int draw_plot(char* file_name);

void plot_output(double a, double b, double c, int width, int height, char* file_name);

void write_buffer_in_file(char* buffer, char* file_name);

int draw_plot_wo_buffering(char* file_name);

void plot_output_wo_buffering(double a, double b, double c, int width, int height, char *file_name);

int is_dot_on_line(double a, double b, double c, int x, int y);

char is_dot_on_axis(int x, int y, char* axis_char);

int width_and_height_input(int* width, int* height);

#endif
