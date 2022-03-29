#include<stdio.h>
#include<stdlib.h>

void enqueue(int* q, int n, int* rear);
void dequeue(int* q, int n, int* front, int* rear);
void display(int* q, int front, int rear);

// Static and/or global variables are not working I don't know why therefore I used pointers.

void main()
{
    printf("\n\nMenu driven implementation to perform the following operations on a queue (non-circular) of size n (implemented using array) depending on user's choice (where the value of n is provided by the user as input) \n\n1) Insert an element (provided by the user as input) to the queue. \n2) Delete the element from the queue. \n3) Display the contents of the queue.\n\n");

    int choice;
    int front = 0; // front is always = 0 as we are shifting the array elements once to the left after a dequeue so front always points to the front most element of the queue.
    int rear = 0;  // rear contains the value at whioh at the current instance the new element is to be enqueued.

    printf("Enter the size of the queue: ");
    int n;
    do // Input validation for the variable "n".
    {
        scanf("%d", &n);
        if(n < 0)
            printf("\nInvalid entry. Size of the queue is a whole numnber. Enter again: ");
    } while (n < 0);

    int* q = (int*) calloc(n, sizeof(int));
    
    do
    {
        printf("\n\n***********Main Menu***********\n\n");

        printf("Enter choice: ");
        int ch;
        do
        {
            scanf("%d", &ch);
            if(ch < 1 || ch > 3)
                printf("\nInvalid choice. Enter again: ");
        } while(ch < 1 || ch > 3);

        switch(ch)
        {
            case 1: enqueue(q, n, &rear); break;
            case 2: dequeue(q, n, &front, &rear); break;
            case 3: display(q, front, rear); break;
        }

        printf("\n\nEnter either any value to exit or 1 to go to the main menu: ");
        scanf("%d", &choice);

    } while (choice == 1);

}

void enqueue(int* q, int n, int* rear)
{
    if(*rear == n)
        printf("\nOverflow. Queue is full.\n");
    else
    {
        int ele;
        printf("\nEnter the element to be inserted/added into the queue/enqueued: ");
        scanf("%d", &ele);

        q[*rear] = ele;
        ++*rear;
    }
}

void dequeue(int* q, int n, int* front, int* rear)
{
    if(*rear == 0) // or *rear == *front as *front is always = 0
        printf("\nUnderflow. Queue is empty.\n");
    else
    {
        printf("\nElement deleted: %d\n", q[*front]);
        for(int i = *front; i <= *rear - 2; i++) // This loop shifts the array elements once to the left after 1 element gets dequeued.
            q[i] = q[i+1];
        (*rear)--; // After deleting one element by shifting the array elements once to the left, rear will be decremented by 1 as it points to the last element.
    }
}

void display(int* q, int front, int rear)
{
    printf("\nQueue:\n\n");
    for(int i = front; i <= rear - 1; i++)
        printf("%d ", q[i]);
}