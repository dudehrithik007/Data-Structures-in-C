#include <stdio.h>

int arSearch(int ar[], int n, int ele);

void main()
{
    printf("\n\nC program: Array element search based on the element in the array is entered.\n");

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

    printf("\n\nEnter the element to be searched: ");
    int ele;
    scanf("%d", &ele);
    
    int index = arSearch(ar, n, ele);
    if(index != -1)
        printf("\nElement found at %dth position.", index+1);
    else
        printf("\nElement not found.");
    
    printf("\n\n");
}

int arSearch(int ar[], int n, int ele)
{
    for(int i = 0; i < n; i++)
    {
        if (ar[i] == ele)
            return i;
    }
    return -1;
}

