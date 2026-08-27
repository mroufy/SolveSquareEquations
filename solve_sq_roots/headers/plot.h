#ifndef PLOT_H
#define PLOT_H

#include <cstdio>

int draw_plot(char* filename);

int draw_plot_wo_buffering(char* filename);

int is_dot_on_line(double a, double b, double c, int x, int y);

char is_dot_on_axis(int x, int y, char* axis_char);

void width_and_height_input(int* width, int* height);

void plot_output(double a, double b, double c, int width, int height, char* filename);

void plot_output_wo_buffering(double a, double b, double c, int width, int height, char *filename);

#endif