#include<stdio.h>
#include<stdlib.h>

void stackPush(int stack[], int n);
void stackPop(int stack[], int n);
void display(int stack[], int n);

int top = -1;

void main()
{
    printf("\nProgram to implement Stack Operations.\n\n");

    printf("-------------------Main Menu-------------------\n");

    printf("\nEnter the size of the Stack(Integer-valued Stack): ");
    int n;
    do
    {
        scanf("%d", &n);
        if(n < 0)
            printf("Invalid size - Enter non-negative values only. Enter again:");
    } while (n < 0);

    int stack[n];

    do
    {    
        printf("\nEnter Choice as 1 or 2 to perform Stack Push or Stack Pop Operations respectively. Enter any other value to exit program: ");
        int ch;
        scanf("%d", &ch);

        switch(ch)
        {
            case 1: if(top + 1 == n)
                        printf("\nOverflow Error. Cannot push an element when the Stack is full.\n");
                    else
                    {
                        printf("\nEnter the value of k where k is the no. of elements to be pushed into the stack: ");
                        int k;
                        do
                        {
                            scanf("%d", &k);
                            if(k < 0 || (k + top) >= n)
                                printf("\nInvalid size - Enter non-negative < remaining size values only . Enter again: ");
                        } while (k < 0 || (k + top) >= n);

                        for(int i = 0; i < k; i++)
                            stackPush(stack, n);
                    }
    
                    break;

            case 2: stackPop(stack, n);
                    break;

            default: exit(0);
        }
    } while(1);
}

void stackPush(int stack[], int n)
{
    printf("\nEnter the element to be pushed: ");
    int ele;
    scanf("%d", &ele);
    top = top + 1;
    stack[top] = ele; 

    printf("Current Stack instance looks like this:\n");
    display(stack, n);
}

void stackPop(int stack[], int n)
{
    if(top == -1)
        printf("\nUnderflow Error. Cannot pop an element when the Stack is empty.\n");
    else
    {
        printf("\nElement poped: %d\n", stack[top]);
        top = top - 1;
    }
    printf("Current Stack instance looks like this:\n");
    display(stack, n);
}

void display(int stack[], int n)
{
    for(int i = top; i >= 0; i--)
        printf("%d\n", stack[i]);
}
