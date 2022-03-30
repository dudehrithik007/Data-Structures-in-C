#include<stdio.h>
#include<stdlib.h>

void enqueue(int* q, int* p, int n, int* front, int* rear);
void dequeue(int* q, int* p, int n, int* front, int* rear);
void display(int* q, int* p, int front, int rear);

void main()
{
    printf("\n\nPrerequisite Knowledge: \n\nA priority queue is a queue in which the dequeue operation removes an item at the front of the queue, but the enqueue operation inserts item according to their priorities. \nA higher priority item is always enqueued before a lower priority item. \nAn element that has the same priority as one or more elements in the queue is enqueued after all the elements with that priority.\n\n");

    printf("\n\nMenu driven implementation to perform the following operations on a priority queue (non-circular) of size n (implemented using array) depending on user's choice (where the value of n is provided by the user as input) \n\n1) Insert an element (provided by the user as input) to the queue according to its priority (also provided by the user as input). \n2) Delete an element from the queue. \n3) Display the contents of the queue with their corresponding priorities.\n\n");

    int choice;
    int front = 0; // front is always = 0
    int rear = 0; // rear contains the value at whioh at the current instance the new element is to be enqueued.

    printf("\nEnter the size of the queue: ");
    int n;
    do // Input Validation for the variable "n".
    {
        scanf("%d", &n);
        if(n < 0)
            printf("\nInvalid entry. Size of the queue is a whole numnber. Enter again: ");
    } while (n < 0);

    int* q = (int*) calloc(n, sizeof(int)); // Priority Queue.
    int* p = (int*) calloc(n, sizeof(int)); // p for priorities. A queue/an array made for maintaining the priorities of corresponding elements of the priority queue.
    
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
            case 1: enqueue(q, p, n, &front, &rear); break;
            case 2: dequeue(q, p, n, &front, &rear); break;
            case 3: display(q, p, front, rear); break;
        }

        printf("\n\nEnter either any value to exit or 1 to go to the main menu: ");
        scanf("%d", &choice);

    } while (choice == 1);

    printf("\n\n");
}

void enqueue(int* q, int* p, int n, int* front, int* rear)
{
    if(*rear == n)
        printf("\nOverflow. Queue is full.\n");
    else
    {
        printf("\nEnter the element to be inserted/added into the queue/enqueued: ");
        int ele;
        scanf("%d", &ele);
        printf("\nEnter the priority for this element (1 is the Lowest priority): ");
        int priority; 
        do // Input Validation for the variable "priority".
        {
            scanf("%d", &priority);
            if(priority < 1)
                printf("\nInvalid Entry. Enter again: ");
        } while (priority < 1);
    
        printf("\n");

        int index = 0; // index is used to find the index at which the current element needs to be inserted in accordance with its priority(and the rules mentioned in the prerequisites).
        while(p[index] != 0 && priority >= p[index]) // --1 Explanation of this while loop's conditions at the end of code.
            index++;                                 

        // after finding the correct position/index for enqueue of the element using the above while loop,                 
        for(int i = *rear - 1; i >= index ; i--) 
        {
            // we shift both the arrays' elements' forward by one space from index position to 
            q[i+1] = q[i];
            p[i+1] = p[i];
        }    
        
        // incorporate the current elements at the index position.
        q[index] = ele;
        p[index] = priority;
        ++*rear;
    }
    display(q, p, *front, *rear);
}

void dequeue(int* q, int* p, int n, int* front, int* rear)
{
    if(*rear == 0) // or *rear == *front as *front is always = 0
        printf("\nUnderflow. Queue is empty.\n");
    else
    {
        printf("\nElement deleted: %d\n", q[*front]);
        for(int i = *front; i <= *rear - 2; i++) // This loop shifts the priority queue elements and the array/queue containing the corresponding priorities once to the left after 1 element gets dequeued.
        {
            q[i] = q[i+1]; // Priority Queue elements left shift
            p[i] = p[i+1]; // corresponding priorities left shift
        }    
        
        (*rear)--; // After deleting one element by shifting the priority queue array elements(and corresponding priorities) once to the left, rear will be decremented by 1 as it points to the last element in the queue.

        // After dequeueing an element and shifting both the queues/arrays to the left once, we fill the (last+1)th element with 0. We do this due to the logic used above to find the correct position of insertion.
        // As rear contains the value at whioh at the current instance the new element is to be enqueued so it contains a 0, so the above loop doesn't do this as we run it till rear - 1 (i = rear - 2 and i + 1 = rear - 1). If we include it above we need to check whether the queue is full or not as if the queue is full then rear would not contain a 0 at the current instance before decrementing. So, we use the following loop for this:

        for(int i = *rear; i < n; i++)
            p[i] = 0;
    }
}

void display(int* q, int* p, int front, int rear)
{
    printf("\nPriority Queue:\n\n");
    for(int i = front; i <= rear - 1; i++)
        printf("%d ", q[i]);

    printf("\n\nCorresponding priorities:\n\n");
    for(int i = front; i <= rear - 1; i++)
        printf("%d ", p[i]);
}

// Explanations:

/* 

--1:

int index = 0;
while(p[index] != 0 && priority >= p[index]) 
    index++;                                
        
We increment index when both the conditions are true. 

For first only: As 0 entries(due to calloc()) in the priorities' array represent empty spaces(Priorities start from 1 being the lowest), all
the entered priorities would be non zero - so this condition is always true until we reach the position containing the first 0 after the last
instance of the highest priority - this can happen in 2 cases - if priority entered is not repeated or the priority entered is same as the 
priority that is repeated but is the highest priority during the current call of enqueue() (and similarly >= is used for/in the second 
condition due to the rule stated in the pre-requisites to insert the same priority element at the end and before the next priority).

Eg:  1 2 3 3 4 4 0 0 0. Entered priority: 5 in 1st case and 4 in 2nd case.

For the above two cases when the second condition is ANDed with the first condition, then also, true and false of the whole condition is 
decided by the first condition only and the second condition is always true - If the entered priority is equal to the highest priority or 
is a new priority that is higher than the current highest priority available in the priorities' array during the current execution of 
enqueue(), then 0's exist after the highest priority and it'll always be greater than 0 and will never stop incrementing.


For second: second condition is true whenever the priority entered is greater than or equal to the present priority and it'll be false
only if a priority higher than the entered priority exists. So for priorities that are repeated but are not the highest priority, first 
condition will always be true as priorities are all non zero but the second condition will decide if the whole condition is true or false
and it'll be false when it reaches the first instance of the next highest priority than the entered priority.

So, the ANDing of the two conditions gives us: 1st condition gives us means to deal with the highest and the new highest priority entered
and the 2nd condition gives us the means to deal with the remaining priorities which are less than the present highest.

Now, index has the correct position of insertion of the entered element.

*/