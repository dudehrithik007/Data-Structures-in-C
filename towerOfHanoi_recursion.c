#include<stdio.h>
#include<math.h>

int toh(int n, char src, char inter, char dest)
{
    if(n > 0)
    {
        toh(n-1, src, dest, inter);
        printf("\nMove disc %d from %c to %c", n, src, dest);
        toh(n-1, inter, src, dest);
    }
}

void main()
{
    printf("\n\nRecursive implementation using C to provide solution (with minimal number of disk moves) to the Tower of Hanoi problem with n number of disks (where the value of n is provided by the user as input).\n\n");

    printf("Enter the number of discs: ");
    int n;
    do
    {
        scanf("%d", &n);
        if(n < 0)
            printf("\nNumber of Discs cannot be negative. Enter again: ");
    } while(n < 0);

    int moves = pow(2, n) - 1;
    printf("\nNumber of moves = %d\n", moves);
    printf("\nSteps to move %d discs from source %c to destination %c: \n", n, 'A', 'C');
    toh(n, 'A', 'B', 'C');

    printf("\n\n");
}