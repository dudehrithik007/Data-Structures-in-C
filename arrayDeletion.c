#include <stdio.h>

void arDelete(int ar[], int n, int pos);

void main()
{
    printf("\n\nC program: Array element deletion based on the position of the element in the array is entered.\n");

    printf("\n\nEnter the number of elements to be put in the array: ");
    int n;
    scanf("%d", &n);

    printf("\nEnter array elements:\n");
    int ar[n];
    for(int i = 0; i < n; i++)
        scanf("%d", &ar[i]);

    printf("\nThe array entered is: ");
    for(int i = 0; i < n; i++)
        printf("%d ", ar[i]);

    printf("\n\nEnter the position in the array from which the element needs to be deleted: ");
    int pos;
    do
    {
        scanf("%d", &pos);
        if((pos-1) >= n || (pos-1) < 0)
            printf("\nElement to be deleted must lie in the array. Enter again: ");
    } while ((pos-1) >= n || (pos-1) < 0);
    arDelete(ar, n, pos);
}

void arDelete(int ar[], int n, int pos)
{
    int deleted = ar[pos-1];

    for(int i = 0; i < n; i++)
    {
        if (i == pos-1)
        {
            for(int j = i; j < 20; j++)
            {
                ar[j] = ar[j+1];
            }
        }
    }
    printf("\nThe element deleted from index number %d or position number %d is %d\n", pos-1, pos, deleted);
    printf("\nThe array after performing the deletion: ");
    for(int i = 0; i < n-1; i++)
        printf("%d ", ar[i]);

    printf("\n\n");
}