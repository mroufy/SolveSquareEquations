/*!
    \file

    \brief File contains prototypes of functions for plot.cpp
*/

#ifndef PLOT_H
#define PLOT_H

#include <cstdio>

int draw_plot(char* file_name);

void plot_output(double a, double b, double c, unsigned width, unsigned height, char* file_name);

void write_buffer_in_file(char* buffer, char* file_name);

int draw_plot_wo_buffering(char* file_name);

void plot_output_wo_buffering(double a, double b, double c, unsigned width, unsigned height, char *file_name);

int is_dot_on_line(double a, double b, double c, int x, int y);

char is_dot_on_axis(int x, int y, char* axis_char);

int width_and_height_input(unsigned* width, unsigned* height);

#endif
