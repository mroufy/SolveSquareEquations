#ifndef PLOT_H
#define PLOT_H

int draw_graph(char* filename);

int is_dot_on_line(double a, double b, double c, int x, int y);

char is_dot_on_axis(int x, int y, char* axis_char);

#endif