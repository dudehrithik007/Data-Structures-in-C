#include<stdio.h>

int rfib(int n);

void main()
{
    printf("\n\nProgram to find and print the nth Fibonacci Number recursively and to find and print The Fibonacci Sequence till nth Fibonacci Number (Using iteration on the recursive function).\n\n");

    printf("Enter a positive integer n to compute its Fibonacci Number: ");
    int n;
    do
    {
        scanf("%d", &n); 
        if(n <= 0)
            printf("\nInvalid Input. Enter a positive integer only: ");
    }while(n <= 0);

    printf("\nfib(%d) (in recursive way and not in tail recursive way) = %d", n, rfib(n));

    printf("\n\nFibonacci sequence till n (Using iteration on the recursive function): ");
    int fib;
    for(int i = 1; i <= n; i++)
        printf("%d ", rfib(i));

    printf("\n\n");
}

int rfib(int n)
{   
    if(n == 1)
        return 0;
    if (n == 2)
        return 1;
    else
        return rfib(n-1) + rfib(n-2);
}