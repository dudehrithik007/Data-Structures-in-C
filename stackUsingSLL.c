#include <stdio.h>
#include <stdlib.h> // Used for malloc(), realloc().

void push();
void pop();
void display();

// Made global to avoid the returning of it from and passing of it to functions:
struct node* head = NULL; // Always points to the first node of the list except when the list is empty.
struct node* top = NULL; // Pointer to the top of the stack.

void main()
{
    printf("\n\nMenu-driven implementation to perform the following operations on a stack (implemented using singly linked list) depending on the user's choice: \n1) PUSH k number of elements provided by the user as input to the stack (where the value of k is provided by the user as input). \n2) POP an element from the stack. \n3) Display the contents of the stack.\n\n");

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
            case 1: push(); break;
            case 2: pop(); break;
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
    struct node* next; // Points to the next node in the list. The last node's next is NULL as it points to no element. // Self-referential structure: A structure that have members which point to a structure variable of the same data type.
};

void push() // Pushing of 'k' elements in the stack at a time.
{
    printf("\nEnter the number of elements to be pushed to the stack at a time: ");
    int k;
    scanf("%d", &k);

    for(int i = 1; i <= k; i++) // Logic for pushing an element into the stack is run 'k' times to push 'k' elements.
    {
        printf("\nEnter a value to be pushed into the stack: ");
        int ele;
        scanf("%d", &ele); // 'value' to be put in the inserted node.
        struct node* newNode = (struct node*) malloc(sizeof(struct node)); // Creating the node (Allocating memory) to be pushed into the stack.
        newNode -> value = ele; // Putting the value in the node which is to be pushed into the stack.   

        if(top == NULL) // When the stack is empty.
        {
            top = newNode;
            head = newNode;
            top -> next = NULL; 
        }
        else  // When the stack contains at least one element.
        {
            top -> next = newNode;
            top = top -> next;
            top -> next = NULL;
        }

        display(); // Displaying the current contents of the stack after pushing of each element to it.
    }
}

void pop() // Pops an element of the stack at a time.
{
    if(top == NULL) // Empty stack.
        printf("\nUnderflow. Empty stack. Nothing here to be popped.");
    else // When the stack contains at least one element.
    {
        struct node* trav = head;
        if(top != head) // If the stack contains more than 1 elements.
        {
            while(trav -> next != top) // Traversing to the node before the top node.
                trav = trav -> next;

            printf("\nValue popped = %d", top -> value);
            realloc(top, 0); // Memory deallocation of the node being deleted.
            top = trav;
            top -> next = NULL;
        }
        else // If the stack contains exactly 1 element.
        {
            printf("\nValue popped = %d", top -> value);
            realloc(top, 0); // Memory deallocation of the node being deleted.
            top = NULL;
            head = NULL;
        }        
    }
    display(); // Displaying the current contents of the stack after poping of an element from it.
}

void display() // Displays the current contents of the stack.
{
    printf("\n\nThe current contents of the stack are:\n\n");

    struct node* trav = head;
    if(top != NULL) // If the stack is not empty.
    {
        do  // Traversing till the last node in the stack.
        {
            printf("%d ", trav -> value);
            trav = trav -> next;
        } while(trav != NULL);    
    }
    printf("\n\n");
}