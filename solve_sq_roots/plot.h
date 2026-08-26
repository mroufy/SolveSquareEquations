#ifndef PLOT_H
#define PLOT_H

#include <cstdio>

int draw_graph(char* filename);

int is_dot_on_line(double a, double b, double c, int x, int y);

char is_dot_on_axis(int x, int y, char* axis_char);

int width_and_height_input(int* width, int* height);

void plot_output(double a, double b, double c, int width, int height, FILE* fp);

#endif