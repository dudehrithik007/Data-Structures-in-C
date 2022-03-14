#include<stdio.h>

int trfib(int n, int a, int b)
{
    if(n == 1)
        return a;
    if(n == 2)
        return b;
   return trfib(n-1, b, a+b);
}

void main()
{
    printf("\n\nC Program to find and print the nth Fibonacci Number using Tail-Recursion and to find and print The Fibonacci Sequence till nth Fibonacci Number (Using iteration on the Tail-Recursive function).\n\nEnter n = ");
    int n;
    scanf("%d", &n);
    printf("\nFib(%d) = %d", n, trfib(n, 0, 1));
    
    printf("\n\nFibonacci Sequence till %dth Fibonacci Number is: ", n);
    for(int i = 1; i <= n; i++)
    {
        printf("%d ", trfib(i,0,1));
    }

    printf("\n\n");
}

