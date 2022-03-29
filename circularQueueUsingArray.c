#include<stdio.h>
#include<stdlib.h>

int enqueue(int* cq, int n, int front, int rear);
int dequeue(int* cq, int n, int front, int rear);
int display(int* cq, int n ,int front, int rear);

void main()
{
    printf("\n\nMenu driven implementation to perform the following operations on a circular queue of size n (implemented using array) depending on user's choice (where the value of n is provided by the user as input) \n\n1) Insert an element (provided by the user as input) to the circular queue. \n2) Delete element from the circular queue. \n3) Display the contents of the circular queue.\n\n");

    int choice;

    printf("Enter the size of the queue: ");
    int n;
    do
    {
        scanf("%d", &n);
        if(n < 0)
            printf("\nInvalid entry. Size of the queue is a whole numnber. Enter again: ");
    } while (n < 0);

    n++; // Reason for this is explained below in the comments.
    int* cq = (int*) calloc(n, sizeof(int));
    int front = 0; // front is 1 position before the 1st/frontest element.
    int rear = 0; // rear is the position containing the last/rearmost element.
    // When the queue is empty, front = rear, and no element exists at after the front position and at the rear position. Otherwise, the above two comments are true.
    
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
            // As the returned values are simplied so the passed values are also simplified for front and rear in all the three functions:
            case 1: rear = enqueue(cq, n, front, rear); break; 
            case 2: front = dequeue(cq, n, front, rear); break; 
            case 3: display(cq, n, front, rear); break;
        }

        printf("\n\nEnter either any value to exit or 1 to go to the main menu: ");
        scanf("%d", &choice);

    } while (choice == 1);
}

// Order of writing/reading the code -- for easier understanding.
int enqueue(int* cq, int n, int front, int rear)
{
    if(rear + 1 == front) // --3 // Due to this condition(to distinguish between full and empty queue) and because at the initial condition(when front = rear), we insert the first element at rear + 1, so, the rear value(which is = front before doing rear = rear + 1) remains empty so we have done n++, if we don't do n++ above, then we are only able to enqueue n-1 elements. Therefore to enqueue n elements first we do n++.
        printf("\nFull Circular Queue. Overflow error.\n");
    else // --2
    {
        int ele;
        printf("\nEnter the element to be inserted/added into the queue/enqueued: ");
        scanf("%d", &ele);

        rear = (rear + 1) % n; // Simplifying rear values to 0 to n-1 // It changes the nth to 0th position and hence after that the values continue from 0 to n-1 and again nth changes to 0th...
        cq[rear] = ele;
    }
    display(cq, n, front, rear);
    return rear; // Simplified value of rear is returned.
}

int dequeue(int* cq, int n, int front, int rear)
{
    if(front == rear) // --1 // Written this according to --3.
        printf("\nEmpty Circular Queue. Underflow error.\n");
    else // --4
    {
        front = (front + 1) % n; // Simplifying front values to 0 to n-1 // It changes the nth to 0th position and hence after that the values continue from 0 to n-1 and again nth changes to 0th...
        printf("\nElement deleted: %d\n", cq[front]);
    }
    display(cq, n, front, rear);
    return front; // Simplied value of front is returned.
}

int display(int* cq, int n, int front, int rear)
{
    printf("\nQueue:\n\n");
    if(front < rear)
    {
        for(int i = front + 1; i <= rear; i++)
        printf("%d ", cq[i]);
    }
    if(front > rear)
    {
        for(int i = front + 1; i <= n-1; i++)
        printf("%d ", cq[i]);
        for(int i = 0; i <= rear; i++)
        printf("%d ", cq[i]);
    }
}

/* 

** Two if conditions are in the display() are used because the queue is implemented in clockwise manner, i.e., elements are enqueued in
** clockwise manner and elements are dequeued in clockwise manner. So, as front and rear move through the circular queue, and as the
** display function is receving the values of front and rear in simplified forms(from 0 to n-1 as we passed the values after finding
** the remainders), at some point after enqueueing, dequeueing and again enqueueing, front will be > rear for which the second if 
** condition is there. 

** Eg: if n = 5 => n++ => n = 6.
** Enqueue 4 elements, then dequeue 3 elements, then enqueue 2 elements.
** Now we see front = 3 and rear = 0. So we print in clockwise manner using two for loops in the second if condition: 
** first from front(3) to n-1(6-1 = 5) and second from 0 to rear(0).

** *(int(*)[6])cq - use this to watch the values changing in the queue in the debugger.

*/