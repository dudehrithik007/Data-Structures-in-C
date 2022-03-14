#include <stdio.h>

int rfact(int n);

void main()
{
    printf("\n\nRecursive (Not Tail Recursive) Factorial Computation Program: \n\n");

    printf("Enter a non negative integer to compute its factorial recursively (not tail recursively): ");
    int n;
    do
    {
        scanf("%d", &n); 
        if(n<0)
            printf("\nInvalid Input. Enter a non negative integer only: ");
    } while(n<0);

    int fact =  rfact(n);
    printf("\n%d! = %d", n, fact);

    printf("\n\n");
}

int rfact(int n)
{
    int fact = 1;
    if(n == 0)
        return 1;
    if(n == 1)
        return 1;
    else
        return n * rfact(n-1);
}
