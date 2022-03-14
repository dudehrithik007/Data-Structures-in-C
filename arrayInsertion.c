#include <stdio.h>

void arInsert(int ar[], int n, int ele, int pos);

void main()
{
    printf("\n\nC program: Array element insertion based on the position of the element in the array is entered.\n");

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

    printf("\n\nEnter an element to be inserted into the array: ");
    int ele;
    scanf("%d", &ele);

    printf("\nEnter the position in the array at which the entered element needs to be inserted: ");
    int pos;
    do
    {
        scanf("%d", &pos);
        if((pos-1) >= n || (pos-1) < 0)
            printf("\nElement to be inserted must be inserted in the array. Enter again: ");
    } while ((pos-1) >= n || (pos-1) < 0);

    arInsert(ar, n, ele, pos);
}

void arInsert(int ar[], int n, int ele, int pos)
{
    for(int i = 0; i < n+1; i++)
    {
        if (i == pos-1)
        {
            for(int j = n+1; j >=i; j--)
            {
                ar[j] = ar[j-1];
            }
        }
    }
    ar[pos-1] = ele;
    printf("\nThe array after performing the insertion: ");
    for(int i = 0; i < n+1; i++)
        printf("%d ",ar[i]);
    printf("\n\n");
}