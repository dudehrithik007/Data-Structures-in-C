#include<stdio.h>

int trfact(int n, int acc)
{
    if(n == 0 || n == 1)
        return acc;
    return trfact(n-1, n*acc);
}

void main()
{
    printf("\n\nProgram to print n! using Tail Recursion. \n\nEnter n = ");
    int n;
    scanf("%d", &n);
    printf("\n%d! = %d", n, trfact(n, 1));
    printf("\n\n");
}