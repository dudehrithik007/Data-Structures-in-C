#include <stdio.h>

void arDisplay(int ar[], int n, int i);

int main()
{
    printf("\n\nC Program to display the entered array elements.\n");

    printf("\n\nEnter the number of elements to be put in the array: ");
    int n;
    scanf("%d", &n);

    printf("\nEnter array elements:\n");
    int ar[n];
    for(int i = 0; i < n; i++)
        scanf("%d", &ar[i]);

    printf("\nEnter the array index from which the element is to be displayed: ");
    int i;
    do
    {
        scanf("%d", &i);
        if(i < 0 || i >= n)
            printf("\nEnter value in the array limits only: ");
    }while(i < 0 || i >= n);

    arDisplay(ar, n, i);
}

void arDisplay(int ar[], int n, int i)
{
    printf("\nElement at %dth index is: %d", i, ar[i]);
    printf("\n\n");
}

