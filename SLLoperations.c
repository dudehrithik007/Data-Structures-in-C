#include <stdio.h>
#include <stdlib.h> // Used for malloc(), realloc().

// variable 'trav' in each of the following functions is used to traverse the list.

int traversal(int flag);
struct node* travToPos(int pos, int flag);
void insertion();
void deletion();
void search();

struct node* head = NULL; // Always points to the first node of the list except when the list is empty. Made global to avoid the returning of it from and passing of it to functions.

void main()
{
    printf("\n\nMenu driven program to implement Singly-Linked-List with its various operations.\n\n");

    char choice;
    do
    {
        printf("\n\n----------Singly-Linked-List----------\n\n");
        
        printf("Enter 1, 2, 3, 4 or 5 respectivly for: \n1. Traversing the whole list, \n2. Traversing the list till the entered position, \n3. Inserting a node to the list at the entered position, \n4. Deleting a node from the list from the entered position, \n5. Searching for all instances of a data value entered by the user. \n\nEnter here: ");
        int ch;
        do // Input validation for variable 'ch'.
        {
            scanf("%d", &ch);
            if(ch != 1 && ch != 2 && ch!= 3 && ch!= 4 && ch!= 5)
                printf("\nInvalid Entry. Enter again: ");
        } while (ch != 1 && ch != 2 && ch!= 3 && ch!= 4 && ch!= 5);
        
        switch(ch)
        {
            case 1: traversal(0); break;
            case 2: travToPos(0, 0); break;
            case 3: insertion(); break;
            case 4: deletion(); break;
            case 5: search(); break;
        }

        printf("\n\nDo you wish to perform another operation (Enter 'y' or 'Y' to continue): ");
        while(getchar() != '\n'); // Clearing the input buffer before taking the input.
        scanf("%c", &choice);

    } while (choice == 'y' || choice == 'Y');

    printf("\n\n\n");    
}

struct node
{
    int value; // This value can itself be another structure containing a lot of values. Or we can declare more values directly here. <=> Using user-defined or in-built datatypes for our values.
    struct node* next; // Points to the next node in the list. The last node's next is NULL as it points to no node. // Self-referential structure: A structure that have members which point to a structure variable of the same data type.
};

// flag in traversal() is used mainly to distinguish its usage when it is called from the menu-driver (flag = 0) and when it is called from other functions (flag = 1). Further explanation is written below.
int traversal(int flag) // This function is used to traverse through the whole list. The argument flag is used to make two versions of the same function in one function itself using if conditions on 'flag'. When flag is 0, we print each node's value and count the total number of nodes while traversing the list. Whwn flag is 1, we only count the total number of nodes in the list. In both the cases, we return the total number of nodes present in the list. According to the flag value passed at the time of calling, the function will behave accordingly as explained.
{
    int i = 0; // variable 'i' is used to count the number of nodes at present in the list.

    if(head == NULL) // Empty list.
        printf("\nThe list is empty.\n");

    else // When the list contains at least 1 element.
    {
        struct node* trav = head; // Starting the traversal from the first node using head pointer.
        i++; // i = 1 because now we know the list at least contain 1 element.

        if(flag == 0) // This is used to print the value of the first node if flag is 0.
        {
            printf("\nList at the current instance:\n\n"); 
            printf("%d ", trav -> value);
        }   

        while((trav -> next) != NULL) // This is used to count as well as print the values after the first node's value in the list.
        {
            trav = trav -> next;
            i++; // Counting the nodes
            if(flag == 0) // Printing the node's value if flag is 0.
                printf("%d ", trav -> value);
        }
    }

    printf("\n");

    return i; // returing the number of nodes at present in the list.
}

// flag in travToPos() is used mainly to distinguish its usage when it is called from the menu-driver (flag = 0) and when it is called from other functions (flag = 1). Further explanation is written below.
struct node* travToPos(int pos, int flag) // This function when flag is 1 is used to traverse the list till the position 'pos' (passed as a parameter) and it returns a pointer to the last node at present in the list. If the flag is 0, then it takes the 'pos' value from the user, traverses the list and print each node's value while traversing and returns a pointer to the last node at present in the list.
{
    if(head == NULL) // Empty list.
        printf("\nThe list is empty.\n");

    else // When the list contains at least 1 element.
    {
        if(flag == 0) // Takes 'pos' from the user. Otherwise, passed value of 'pos' is used. 
        {   
            printf("\nEnter the position till which you wanna traverse the list: ");
            do // Input validation for variable 'pos'.
            {
                scanf("%d", &pos);
                if(pos < 1 || pos > traversal(1))
                    printf("\nPosition values are natural numbers only and are less than or equal to the size of the list. Enter again: ");
            } while (pos < 1 || pos > traversal(1));

            printf("\nList at the current instance:\n\n");
        }

        int i = 1; // i is 1 as after entering the else part we know we have at least one element and below in the while loop after going to the next element we are incrementing i.
        struct node* trav = head;

        while(i != pos) // When i = pos, we exit this loop, we have incremented i at the last iteration to reach i = pos but we have not printed the ith, that is, the pos'th value which is the last value which we do print below separately as when i = pos we exited the loop. This is happening as in the ith iteration we are printing the ith value and then we are incrementing i in the ith iteration itself. So, when i = pos, the loop exits therefore we cannot print the i = pos'th value from inside the loop. We don't increment i first before printing as we have initialised i with 1 above in this logic so we need to print the 1st node first with i having the corresponding value as 1 and so on...
        {
            if(flag == 0) // Prints the ith node's value till i = pos - 1.
                printf("%d ", trav -> value);

            trav = trav -> next;
            i++;
        }     
        if(flag == 0) // Prints the last node's value which is at position, i = pos. Also if pos = 1 then it prints head's value as we don't go inside the while loop.
            printf("%d ", trav -> value); 
                        
        return trav; // Returns a pointer to the last node at present in the list.
    }
}

// Different cases are made as in some cases we need to change and in some we don't need to change the head's value which is inherent to the list.
void insertion() // Inserts a node at the position specified by the user in the list.
{
    printf("\n\nEnter a value to be inserted in the list: ");
    int ele;
    scanf("%d", &ele); // 'value' to be put in the inserted node.
    struct node* newNode = (struct node*) malloc(sizeof(struct node)); // Creating the node (Allocating memory) to be inserted in the list.
    newNode -> value = ele; // Putting the value in the node which is to be inserted in the list.   

    if(head == NULL) // When the list is empty. Making the new node 'newNode' as the first node. // Here we need to change head's value.
    {
        newNode -> next = NULL;
        head = newNode;
    }
    else // When the list contains at least 1 node.
    {
        printf("\nEnter the position at which you wanna insert the element: ");
        int pos;
        do // Input validation for variable 'pos'.
        {
            scanf("%d", &pos);
            if(pos < 1 || pos > traversal(1) + 1)
                printf("Position values are natural numbers only and are less than or equal to the size of the list + 1. Enter again: ");
        } while (pos < 1 || pos > traversal(1) + 1); // +1 because, say, the list contains n nodes then we can insert another node at (n+1)th position too.
        
        if(pos == 1) // Inserting a node at the start of the list (When the list already contains at least one node). // Here we need to change head's value.
        {
            newNode -> next = head;
            head = newNode;
        }    
        else // Inserting a node at any position other than the start of the list (When the list already contains at least one node). // Here we don't need to change head's value.
        {
            struct node* trav = travToPos(pos-1, 1); // 'trav' points to the node at one position before we need to insert the new node 'newNode'.
            newNode -> next = trav -> next; // Also makes possible here itself the case of insertion of the last node (as well as when there are 2 nodes in the list and the insertion of the 2nd node) where the new node 'newNode' which becomes the last node (after insertion of it) points to NULL after insertion of it as it now becomes the last node. This happens due to the NULL value in the previous last node's next being assigned to the new last node's next.
            trav -> next = newNode;
        }
    }
    printf("\nElement insertion successful.\n");
    traversal(0); // Displaying the whole linked-list after each node insertion.
}

// Different cases are made as in some cases we need to change and in some we don't need to change the head's value which is inherent to the list.
void deletion() // Deletes a node from the position specified by the user from the list.
{
    int delVal; // Temporary variable to store the 'value' part of the node that we are gonna delete. 

    if(head == NULL) // Empty list.
        printf("\nNo nodes detected.\n");

    else // When the list contains at least 1 node. 
    {
        struct node* trav = NULL;

        if(head -> next == NULL) // When the list has only 1 node. // Here we need to change head's value.
        {
            delVal = head -> value; // Storing the 'value' of the node being deleted before deleting it.
            realloc(head, 0); // Deallocation of memory of the node being deleted.
            head = NULL; // Pointing to NULL as it implies that after deleting the only node we have, 0 nodes left now. We may also insert a new node at this point. There also it'll be helpful ofcourse as we will be able to identify this case and insert accordingly. // Additional: Pointing to NULL to avoid a dangling pointer (even for a while). Dangling pointers are pointers that point to certain memory address - occurs at the time of the object destruction when the object is deleted or de-allocated from memory without modifying the value of the pointer. They can also become security holes.
        }

        else // When the list has more than 1 node.
        {
            printf("\nEnter the position at which you wanna delete the element: ");
            int pos;
            do // Input validation for variable 'pos'.
            {
                scanf("%d", &pos);
                if(pos < 1 || pos > traversal(1))
                    printf("Position values are natural numbers only and are less than or equal to the size of the list. Enter again: ");
            } while (pos < 1 || pos > traversal(1));

            if(pos == 1) // Deleting a node from the start of the list (When the list has more than 1 node). // Here we need to change head's value.
            {
                trav = head;
                head = head -> next;
                delVal = trav -> value;
                realloc(trav, 0);
                trav = NULL;
            }
            else // Deleting a node from any position other than the start of the list (When the list has more than 1 node). // Here we don't need to change head's value.
            {
                trav = travToPos(pos-1, 1); // For deleting the element at position 'pos', we make 'trav' point to the node at the position one less than that position.
                struct node* temp = trav -> next; // And we make a temporary pointer 'temp' point to the node which we want to delete.
                trav -> next = (trav -> next) -> next; // or temp -> next; // Also makes possible here itself the case of deletion of the last node (as well as when there are 2 nodes in the list and the deletion of the 2nd node) where the second last node which becomes the last node (after deletion of the current last node) points to NULL after deletion of the current last node as it now becomes the last node.
                delVal = temp -> value;
                realloc(temp, 0);
                temp = NULL;
            }
        }
        printf("\nElement deletion successful.\n");
        printf("\nElement deleted is: %d.\n", delVal);
    }
    traversal(0); // Displaying the whole linked-list after each node deletion.
}

// Some comments in search() pertain only when the if-else condition to check whether the list is empty or not is not used. For simplicity, read the following comments while ignoring the if-else condition to check whether the list is empty or not.
void search() // Searching for all instances of a data value entered by the user.
{
    if(head != NULL) // If the list is non-empty.
    {
        printf("\nEnter the data value that needs to be searched: ");
        int data;
        scanf("%d", &data);

        int flag = 0; // Used to track whether we have found at least one instance of the value or not.
        int i = 1; // Used to dispay the positions of the value if found in the list. // i = 1 because initially we point to head in the for loop, that is, at the position 1 in the list. Even if the list is empty we are not using the value of i later in the code in that case (When the list is empty, we don't enter the loop, so, i's value becomes useless and trav points to NULL as head points to NULL), so, setting i to 1 makes no difference in that case as we don't use it in that case. Otherwise, if the list contains at least 1 node, initially, i = 1 means we point to position 1 in the list that is at the first node which is pointed to by head as in the initialisation of the loop.

        for(struct node* trav = head; trav != NULL; trav = trav -> next, i++) // We enter this loop only if the list is non-empty. // After the last iteration, when trav = NULL, i also increments, but as we exit the loop and don't use i outside the loop, it doesn't matter.
        {
            if(data == trav -> value)
            {
                printf("\nData found at position: %d.", i);
                flag = 1; // If found at atleast one instance of the value, then set flag to 1.
            }
        }
        if(flag == 0)
            printf("\nData not found.\n");
    }
    else
        printf("\nEmpty List.\n");

    printf("\n");
}

// order of reading of conditions in insertion() for better understanding:
// 0 nodes exist so inserting 1 node, 1 node exist so inserting 2nd node at:
// at pos = 1 if 1 node exist, if >1 nodes exist.
// at pos = last if 1 node exist, if >1 nodes exist.
// at pos = in between if 1 node exist, if >1 nodes exist.

// order of reading of conditions in deletion() for better understanding:
// 0 nodes exist, >= 1 node exist, 1 node exist, >1 (>=2) node exist so deleting 2nd node at:
// at pos = 1 if 2 node exist, if >1 nodes exist.
// at pos = last if 2 node exist, if >1 nodes exist.
// at pos = in between if 2 node exist, if >1 nodes exist.

// Similarly for other functions.

/*

Additional:

Extra piece of code (can be included in a new function) to implement input validation in a code to insert a node anywhere in between the
first and the last node only which can only happen if we at least have 2 nodes already in the list.

int ch, flag;
    do // Input
    {
        scanf("%d", &ch);
        flag = 0;
        if(ch == 2) // For choosing insertInBetween().
        {
            if(traversal(1) < 2) // If we have atleast 2 nodes then flag remains = 0 else it becomes = 1 and that implies invalid input for ch = 2 with less than 2 nodes in the list.
                flag = 1;
        }
        if((ch != 1 && ch != 2 && ch != 3) || flag == 1) // Additional - Understanding of these conditions come easy to us when we think in terms Boolean Algebra.
            printf("\nInvalid Entry. Enter again: ");
    } while ((ch != 1 && ch != 2 && ch != 3) || flag == 1);

*/