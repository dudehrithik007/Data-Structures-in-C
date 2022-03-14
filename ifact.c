#include <stdio.h>

void ifact(int n);

void main()
{
    printf("\n\nIterative Factorial Computation Program: \n\n");
    printf("Enter a non negative integer to compute its factorial iteratively: ");
    int n;
    do
    {
        scanf("%d",&n); 
        if(n<0)
            printf("\nInvalid Input. Enter a non negative integer only: ");
    } while(n<0);

    ifact(n);

    printf("\n\n");
}

void ifact(int n)
{
    int fact = 1;
    if(n != 0)
    {
        for(int i = 1; i <= n; i++)
        {
            fact = fact * i;
        }
    }
    printf("\n%d! = %d",n,fact);
}
