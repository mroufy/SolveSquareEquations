#include <cstdio>
#include <stdio.h>
#include <math.h>


int minus_of_int(int x);


int main()
{
    int n = 0;
    scanf("%d", &n);
    printf("%d %s\n", minus_of_int(n), char(n));
}


int minus_of_int(int x)
{
    return -x;
}
