#include <stdio.h>
#include <stdlib.h> // Used for malloc(), realloc().

void enqueue();
void dequeue();
void display();

// Made global to avoid the returning of it from and passing of it to functions.
struct node* head = NULL; // Always points to the first node of the list except when the list is empty. 
struct node* tail = NULL; // Always points to the last node of the list except when the list is empty.

void main()
{
    printf("\n\nMenu-driven implementation to perform the following operations on a queue (implemented using doubly linked list) depending on the user's choice: \n1) INSERT an element provided by the user as input to the queue. \n2) DELETE an element from the queue. \n3) Display the contents of the queue.\n\n");

    char ch;
    int choice;
    do
    {
        printf("\nEnter choice: ");
        do // Input validation for variable 'choice'.
        {
            scanf("%d", &choice);
            if(choice < 1 || choice > 3)
                printf("Invalid Entry. Enter again: ");
        } while (choice < 1 || choice > 3);

        switch(choice)
        {
            case 1: enqueue(); break;
            case 2: dequeue(); break;
            case 3: display(); break;
        }

    printf("\n\n\n\nDo you wish to perform another operation (Enter 'y' or 'Y' to continue): ");
    while(getchar() != '\n'); // Clearing input buffer before taking the input.
        scanf("%c", &ch);

    } while (ch == 'y' || ch == 'Y');

    printf("\n\n");
}

struct node
{
    int value; // This value can itself be another structure containing a lot of values. Or we can declare more values directly here. <=> Using user-defined or in-built datatypes for our values.
    struct node* next; // Points to the next node in the list. The last node's next (pointed to by tail) is NULL as it points to no element. 
    struct node* prev;  // Points to the previous node in the list. The first node's prev (pointed to by head) is NULL as it points to no element.
    // Self-referential structure: A structure that have members which point to a structure variable of the same data type.
};

void enqueue() // Enqueueing an element to the queue at a time.
{
    printf("\nEnter a value to be enqueued into the queue: ");
    int ele;
    scanf("%d", &ele); // 'value' to be put in the inserted node.
    struct node* newNode = (struct node*) malloc(sizeof(struct node)); // Creating the node (Allocating memory) to be enqueued into the queue.
    newNode -> value = ele; // Putting the value in the node which is to be enqueued into the queue.

    if(head == NULL) // or tail == NULL // Empty Queue.
    {
        head = newNode;
        tail = newNode;
        newNode -> next = NULL;
        newNode -> prev = NULL;
    }
    else // If the queue contains at least 1 element. // All enqueueing are from tail - therefore tail is only used here. For the first element's enqueue above - we use both head and tail.
    {
        tail -> next = newNode;
        (tail -> next) -> prev = tail; // or newNode -> prev = tail;
        tail = tail -> next;
        tail -> next = NULL; // As tail is always the last element in the queue.
    }
    display(); // Displaying the current contents of the queue after enqueueing of an element to it.
}

void dequeue() // Dequeueing an element from the queue at a time.
{
    if(head == NULL) // Empty queue.
        printf("\nEmpty queue. Nothing here to be dequeued.");
    else // When the queue contains at least one element.
    {
        if(head == tail) // As head != NULL is already checked in the above if. // When the queue contains exactly one element. 
        {
            printf("\nElement dequeued = %d", head -> value);
            realloc(head, 0);
            head = NULL;
            tail = NULL;
        }
        else // When the queue contains more than one element. // All dequeueing are from head - therefore head is only used here. For the first element's dequeue above - we use both head and tail.
        {
            struct node* temp = head;
            head = head -> next;
            head -> prev = NULL; // As head is always the first element in the queue.

            printf("\nElement dequeued = %d", temp -> value);
            realloc(temp,0);
            temp = NULL;
        }
    }
    display(); // Displaying the current contents of the queue after dequeueing of an element from it.
}

void display() // Displays the current contents of the queue.
{
    printf("\n\nThe current contents of the stack are:\n\n");

    if(head != NULL) // When the queue is non-empty.
    {
        struct node* trav = head;

        for(trav = head; trav != tail; trav = trav -> next)
            printf("%d ", trav -> value);

        printf("%d ", trav -> value); // Printing the last node's value when the above for loop exits at the condition trav == tail.
    }    
}