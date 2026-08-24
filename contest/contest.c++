#include <cstdio>
#include <stdio.h>
#include <math.h>


int main()
{
    int n = 0, m = 0, k =0;
    double tflelev = 0, tdoors = 0, tflfoot = 0;
    double t_foot = 0, t_elev = 0;
    scanf("%d %d %d %lg %lg %lg", &n, &m, &k, &tflelev, &tdoors, &tflfoot);
    t_foot = tflfoot * fabs(n - m);
    t_elev = fabs(n - k) * tflelev + 2 * tdoors + fabs(n - m) * tflelev;
    if (t_foot < t_elev)
        printf("stairs\n");
    else
        printf("elevator\n");
}
