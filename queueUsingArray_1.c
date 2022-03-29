#include<stdio.h>
#include<stdlib.h>

int enqueue(int* q, int n, int rear);
int dequeue(int* q, int front, int rear);
void display(int* q, int front, int rear);

void main()
{
    printf("\n\nMenu driven implementation to perform the following operations on a queue (non-circular) of size n (implemented using array) depending on user's choice (where the value of n is provided by the user as input) \n\n1) Insert an element (provided by the user as input) to the queue. \n2) Delete the element from the queue. \n3) Display the contents of the queue.\n\n");

    /* In this implementation of the queue:

    ** As we are not actually deleting the elements from the array but are removing them from the queue as represented by front and
    ** therefore not moving the array elements to fill the removed elements' positions, the removed elements' positions are being wasted in 
    ** the queue and the elements can only be filled once, until rear == n - 1 and removed once, until front (== rear) == n-1. Once 
    ** the queue reaches the conditions(true) rear == n - 1 AND front (== rear) == n - 1, then we cannot further respectively add 
    ** more elements(even after removing elements from the queue as rear has reached the last position of the queue even when there
    ** could be space in the queue as wasted spaces mentioned above if front > -1) AND remove more elements(as the queue is now empty
    ** as front == rear and as we have reached the last position of the queue as front == n - 1 (== rear) so we cannot even add more
    ** elements(in the wasted spaces) and therefore cannot remove elements after adding as we cannot add). So, once rear reaches the
    ** last position, no more elements can be added(even when there could be space as mentioned above) and once front reaches the 
    ** last position(rear will also be at the last position as front reaches the last position), no more elements can be removed(as 
    ** now the queue is empty and no more elements can be added in the wasted spaces and then be removed).

    ** Also, front is always <= rear. This is because when front == rear, queue is empty, so no more elements can be removed and
    ** hence front will never be > rear. And, front < rear whenever there exists at least one element in the queue.

    ** front and rear move only right to left when removing or adding elements respectively. As the array elements are not deleted
    ** by moving the array elements, front and rear cannot move as they would've with the array(in the right to left direction) if the 
    ** deletion with moving the array elements was performed.

    ** At front the element does not exist and at the rear the last element in the queue exists.

    ** Solution of the wasting of spaces using another implementation or circular queue. (queueUsingArray_2.c or circularQueueUsingArray.c)

    */

    int choice = 1;

    printf("Enter the size of the queue: ");
    int n;
    do
    {
        scanf("%d", &n);
        if(n < 0)
            printf("\nInvalid entry. Size of the queue is a whole numnber. Enter again: ");
    } while (n < 0);

    int* q = (int*) calloc(n, sizeof(int));

    int front = -1;
    int rear = -1;
    
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
            case 1: rear = enqueue(q, n, rear); break;
            case 2: front = dequeue(q, front, rear); break;
            case 3: display(q, front, rear); break;
        }

        printf("\n\nEnter either any value to exit or 1 to go to the main menu: ");
        scanf("%d", &choice);

    } while (choice == 1);

}

int enqueue(int* q, int n, int rear)
{
    if (rear == n-1)
        printf("\nOverflow. Queue is full.\n");
    else
    {
        int ele;
        printf("\n\nEnter the element to be inserted/added into the queue/enqueued: ");
        scanf("%d", &ele);

        q[++rear] = ele;
    }
    return rear;
}

int dequeue(int* q, int front, int rear)
{
    if(front == rear)
        printf("\nUnderflow. Queue is empty.\n");
    else
        printf("\n\nElement deleted: %d\n", q[++front]);

    return front;
}

void display(int* q, int front, int rear)
{
    printf("\nQueue:\n\n");
    for(int i = front + 1; i <= rear; i++)
        printf("%d ", q[i]);
}