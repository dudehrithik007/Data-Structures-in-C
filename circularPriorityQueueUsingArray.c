#include<stdio.h>
#include<stdlib.h>

void enqueue(int* cq, int* p, int n, int* front, int* rear);
void dequeue(int* cq, int* p, int n, int* front, int* rear);
void display(int* cq, int* p, int n, int front, int rear);

// For all the variables wherever I have used (variable) % n or (variable + 1) % n, this is used for simplifcation of values(from higher values than n-1) such that they are from 0 to n-1, that is, the circular array's indices.
// variable = (variable + 1) % n is therefore used as a substitution for variable++ to move in the circle in any one direction, say, clockwise.
// Therefore, we cannot use comparison operators for checking whether for eg, variable 'rear' is before or after variable 'index' using the index values of the circular queue as after the last index of the circular queue we arrive at the first index using the condition specified in the above comment. If we don't use it and instead use the ++ operator then it will increment it out of the queue and a circular structure won't be made.
// Therefore, I have used a while loop to check after initialising i = *rear whether index == i or not while moving in the same direction using i = (i + 1) % n, say, clockwise. Instead of checking for eg in a for loop condition to iterate until i <= index or something else due to the above comments as we want after n-1 to arrive at 0 th index. So, comparsion operators become useless here as after n-1 we arrive at 0, so even if for eg 0th position is "greater than" n - 1 when we move clockwise in an instance but 0 < n-1 so that makes our logic false here as we wanna increment but the for loop condition becomes false.

void main()
{
    printf("\n\nPrerequisite Knowledge: \n\nA priority queue is a queue in which the dequeue operation removes an item at the front of the queue, but the enqueue operation inserts item according to their priorities. \nA higher priority item is always enqueued before a lower priority item. \nAn element that has the same priority as one or more elements in the queue is enqueued after all the elements with that priority.\n\n");
    
    printf("\n\nMenu driven implementation to perform the following operations on a circular priority queue of size n (implemented using array) depending on user's choice (where the value of n is provided by the user as input) \n\n1) Insert an element (provided by the user as input) to the circular priority queue. \n2) Delete element from the circular priority queue. \n3) Display the contents of the circular priority queue.\n\n");

    int choice;

    printf("Enter the size of the queue: ");
    int n;
    do // Input validation for variable "n".
    {
        scanf("%d", &n);
        if(n < 0)
            printf("\nInvalid entry. Size of the queue is a whole numnber. Enter again: ");
    } while (n < 0);

    n++; // Reason for this is explained below --2
    int* cq = (int*) calloc(n, sizeof(int)); // Circular Priority Queue.
    int* p = (int*) calloc(n, sizeof(int)); // p for priorities. A queue/an array made for maintaining the priorities of corresponding elements of the circular priority queue.
    int front = 0; // front is 1 position before the 1st/frontest element.
    int rear = 0; // rear is the position containing the last/rearmost element.
    // Whenever the queue is empty, front = rear, and no element exists at after the front position and at the rear position. Otherwise, the above two comments are true.
    
    do
    {
        printf("\n\n***********Main Menu***********\n\n");

        printf("Enter choice: ");
        int ch;
        do // Input validation for variable "ch".
        {
            scanf("%d", &ch);
            if(ch < 1 || ch > 3)
                printf("\nInvalid choice. Enter again: ");
        } while(ch < 1 || ch > 3);

        switch(ch)
        {
            case 1: enqueue(cq, p, n, &front, &rear); break;
            case 2: dequeue(cq, p, n, &front, &rear); break;
            case 3: display(cq, p, n, front, rear); break;
        }

        printf("\n\nEnter either any value to exit or 1 to go to the main menu: ");
        scanf("%d", &choice);

    } while (choice == 1);
}

void enqueue(int* cq, int* p, int n, int* front, int* rear)
{
    if((*rear + 1) % n == *front) // --2: Due to this condition (to distinguish between full and empty queue) and because at the initial condition(when front = rear), we insert the first element at rear + 1, so, the rear value(which is = front before doing rear = rear + 1) remains empty so we have done n++, if we don't do n++ above, then we are only able to enqueue n-1 elements. Therefore to enqueue n elements first we do n++.
        printf("\nFull Circular Queue. Overflow error.\n");
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

        int index = (*front + 1) % n; // index is used to find the index at which the current element needs to be inserted in accordance with its priority(and the rules mentioned in the prerequisites).
        while(p[index] != 0 && priority >= p[index]) // --1 Explanation of this while loop's conditions at the end of code in priorityQueueUsingArray_2.c
            index = (index + 1) % n;

        *rear = (*rear + 1) % n; // Rear incremented to incorporate the space in the circular priority queue for the new element that has just been inputted. // Simplifying (using "%n") rear values to 0 to n-1 // It changes the nth to 0th position and hence after that the values continue from 0 to n-1 and again nth changes to 0th...

        // After finding the correct position/index for enqueue of the element using the above while loop:              
        if(*front != *rear)
        {
            int i = *rear;
            while(i != index) // We reach the position of insertion of the new element using "index" variable in the circular priority queue.
            {
                cq[i % n] = cq[(i + n - 1) % n]; // Shifting elements to make space at "index" position in the circular priority queue(and correspondingly in the priorities' queue) for the current element that was inputted.
                p[i % n] = p[(i + n - 1) % n]; // (i + n - 1) % n simulates i - 1 in circular fashion. Since before 0 we need n - 1. So, if i = 0, for i - 1 we need n - 1.
                i = (i + n - 1) % n; // Moving in the same direction, anticlockwise as we assumed clockwise above for increasing indices (ofcourse except the 0 and n - 1 transition - which we are taking care of using the "%n" part in expressions) - explanation in the comments above main().
            }
        }
        
        // Putting the inputs in the current instance at the "index" position after making space for them at "index" position by shifting the elements in each of the arrays above.
        cq[index] = ele;
        p[index] = priority;
    }
    display(cq, p, n, *front, *rear);
}

void dequeue(int* cq, int* p, int n, int* front, int* rear)
{
    if(*front == *rear) // Written this according to --2.
        printf("\nEmpty Circular Queue. Underflow error.\n");
    else
    {
        *front = (*front + 1) % n; // Simplifying (using "%n") front values to 0 to n-1 // It changes the nth to 0th position and hence after that the values continue from 0 to n-1 and again nth changes to 0th...
        printf("\nElement deleted: %d\n", cq[*front]);
        p[*front] = 0; // Priority(priorities' array) = 0 at front. // According to the logic above used to find the correct insertion position using the "index" variable. After incrementing front in the line two lines before this line, we reach the first element in the queue, we set the value at front as 0 - that is kind of resetting the position - simulating element deletion - that no element exists here as the arrays were initialised with 0's using calloc(). The logic of != 0 used in the while loop to find the next position of insertion (variable "index") remains preserved after deletion to enqueue more elements after completition of this operation.
    } // Also, the 2nd condition in the while loop used to find the position of insertion of next element (variable "index") also remains preserved as only elements of highest priority are dequeued, that is, from the front of the queue only(prerequisites) and not from between/end and as they are initialised to zero and as front is now one index higher, elements' positions' before front are actually now the elements' positions to be enqueued later - these positions are "reset" in the sense that they become as they were when the arrays were initialised so both conditions of finding the position to enqueue are preserved as for the 2nd condition ">=" the elements' prioritites' ordering remain the same throughout the dequeue operation. Effect on 1st condition was removed by the 0 initialisation here and the effect on 2nd condition(checking >=) is also removed due to the resetting of the array for the dequeued element by the 0 initialisation and front incrementation by 1. See Explanation of variable index in priorityQueueUsingArray_2.c

    display(cq, p, n, *front, *rear);
}

void display(int* cq, int* p, int n, int front, int rear)
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

    printf("\n\nCorresponding priorities:\n\n");
    if(front < rear)
    {
        for(int i = front + 1; i <= rear; i++)
            printf("%d ", p[i]);
    }
    if(front > rear)
    {
        for(int i = front + 1; i <= n-1; i++)
            printf("%d ", p[i]);
        for(int i = 0; i <= rear; i++)
            printf("%d ", p[i]);
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