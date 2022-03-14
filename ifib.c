#include<stdio.h>

void ifib(int n); // Use return type as int when returning.

void main()
{
    printf("\n\nProgram to compute iteratively and print the nth Fibonacci Number (Uncomment and comment the marked statements respectively for this version of the program). Also computing and printing the Fibonacci Sequence till nth Fibonacci Number iteratively (Default version of the program).\n\n");

    printf("Enter a positive integer n to compute its Fibonacci Number: ");
    int n;
    do
    {
        scanf("%d",&n); 
        if(n <= 0)
            printf("Invalid Input. Enter a positive integer only: ");
    } while(n <= 0);

    // printf("\n\nfib(%d) (in Iterative way) = %d", n, ifib(n)); // Uncomment it
    ifib(n); // Comment it

    printf("\n\n");
}

void ifib(int n) // Use return type as int when returning.
{
    printf("\nFibonacci Sequence till %dth Fibonacci Number is: ", n);
    if(n == 1)
    {
        printf("0 "); // Comment it
        // return 0; // Uncomment it
    }
    if(n == 2)
    {
        printf("1 "); // Comment it
        // return 1; // Uncomment it
    }
    if(n != 1 && n != 2)
    {
        printf("0 "); // Comment it
        printf("1 "); // Comment it
        int n1 = 0, n2 = 1, n3;
        for(int i = 3; i <= n; i++) // Performing a +1 shift of variables to the right in the Fibonacci Sequence.
        {
            n3 = n1 + n2; // for eg: n3 is 3rd Fibonacci number when i = 3. Therefore starting from 3 to compute nth Fibonacci number in nth iteration or we can start from 1 to n-2. -2 for the 1st and 2nd Fibonacci Number declared above. Therefore , number of iterations = n-2.
            printf("%d ", n3); // Comment it
            n1 = n2; // n1 shifts to the next number in the sequence.
            n2 = n3; // n2 shifts to the next number in the sequence.
        }
        // return n3; // Uncomment it
    }
}