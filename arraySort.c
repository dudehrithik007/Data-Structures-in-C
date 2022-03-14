#include <stdio.h>

void sortinc(int ar[], int n);
void sortdec(int ar[], int n);

int main()
{
    printf("\n\nC program: Array elements' sort - Bubble Sort is used.\n");

    printf("\n\nEnter the number of elements to be put in the array: ");
    int n;
    scanf("%d", &n);

    printf("\nEnter array elements:\n");
    int ar[n+1];
    for(int i = 0; i < n; i++)
        scanf("%d", &ar[i]);

    printf("\nThe array entered is: ");
    for(int i = 0; i < n; i++)
        printf("%d ", ar[i]);

    printf("\n\nSorting the entered array in: \n 1. Non-Decreasing/Increasing Order. \n 2. Non-Increasing/Decreasing Order. \nEnter Choice(1 or 2): ");
    int ch;
    scanf("%d", &ch);

    if(ch == 1)
        sortinc(ar, n);
    if(ch == 2)
        sortdec(ar, n);
    if(ch != 1 && ch != 2)
        printf("Invalid Choice.");

    printf("\nThe array after sorting it is: ");
    for(int i = 0; i < n; i++)
        printf("%d ", ar[i]);
    
    printf("\n\n");
}

void sortinc(int ar[], int n)
{
    for(int i = 0; i < n; i++)
        for(int j = 0 ; j < n-1; j++)
            if(ar[j]>ar[j+1])
            {
                int temp = ar[j];
                ar[j] = ar[j+1];
                ar[j+1] = temp;
            }
}

void sortdec(int ar[], int n)
{
    for(int i = 0; i < n; i++)
        for(int j = 0 ; j < n-1; j++)
            if(ar[j] < ar[j+1])
            {
                int temp = ar[j];
                ar[j] = ar[j+1];
                ar[j+1] = temp;
            }
}


