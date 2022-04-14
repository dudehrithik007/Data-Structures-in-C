#include <stdio.h>
#include <stdlib.h> // Used for malloc(), realloc().

// variable 'trav' in each of the following functions is used to traverse the list.

int traversal(int flag);
struct node* travToPos(int pos, int flag);
void insertion();
void deletion();
void search();

// Made global to avoid the returning of it from and passing of it to functions.
struct node* head = NULL; // Always points to the first node of the list except when the list is empty.
struct node* tail = NULL; // Always points to the last node of the list except when the list is empty.
// When there is only one node in the list, then the last node and the first node coincide and hence head and tail too coincide.

void main()
{
    printf("\n\nTo implement various operations on a Circular-Singly-Linked-List in a menu-driven program.");

    char choice;
    do
    {
        printf("\n\n------------Circular-Singly-Linked-List------------\n\n");
        
        printf("Enter 1, 2, 3, 4 or 5 respectivly for: \n1. Traversing the whole list, \n2. Traversing the list till the entered position, \n3. Inserting a node to the list at the entered position, \n4. Deleting a node from the list from the entered position, \n5. Searching for all instances of a data value entered by the user. \n\nEnter here: ");
        int ch;
        do // Input validation for variable 'ch'.
        {
            scanf("%d", &ch);
            if(ch != 1 && ch != 2 && ch!= 3 && ch!= 4 && ch != 5)
                printf("\nInvalid Entry. Enter again: ");
        } while (ch != 1 && ch != 2 && ch!= 3 && ch!= 4 && ch != 5);
        
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
    struct node* next; // Points to the next node in the list. The last node's next is the first node. // Self-referential structure: A structure that have members which point to a structure variable of the same data type.
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
        i++; // i = 1 because now we know the list at least contains 1 element and we(trav) point(s) to head above.

        if(flag == 0) // This is used to print the value of the first node if flag is 0.
        {       
            printf("\nList at the current instance:\n\n"); 
            printf("%d ", trav -> value);
        }    

        while((trav -> next) != head) // This is used to count as well as print the values after the first node's value in the list. // Only the while loop condition is different here from the SLL ((trav -> next) != NULL).
        {
            trav = trav -> next;
            i++; // Counting the nodes
            if(flag == 0) // Printing the node's value if flag is 0.
                printf("%d ", trav -> value);
        }
    }

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
        
        int i = 1; // i is 1 as after entering the else part we know we have at least one element and we initially point to head below therefore and below in the while loop after going to the next element we are incrementing i.
        struct node* trav = head;

        while(i != pos) // When i = pos, we exit this loop, we have incremented i at the last iteration to reach i = pos but we have not printed the ith, that is, the pos'th value which is the last value which we do print below separately as when i = pos we exited the loop. This is happening as in the ith iteration we are printing the ith value and then we are incrementing i in the ith iteration itself. So, when i = pos, the loop exits therefore we cannot print the i = pos'th value from inside the loop. We don't increment i first before printing as we have initialised i with 1 above in this logic so we need to print the 1st node first with i having the corresponding value as 1 and so on...
        {
            if(flag == 0) // Prints the node's value till 'pos - 1'.
                printf("%d ", trav -> value);

            trav = trav -> next;
            i++;
        }     
        if(flag == 0) // Prints the last node's value which is at position = 'pos'. Also if pos = 1 then it prints head's value as we don't go inside the while loop - when we have only 1 node in the list, then, it is the last node itself.
            printf("%d ", trav -> value); 
                        
        return trav; // Returns a pointer to the last node at present in the list.
    }
}

// Different cases are made because to change head's position (if required - mentioned below), tail's position (if required - mentioned below), other nodes' positions (if required) while inserting a new node require different operations to be perfomred.
void insertion() // Inserts a node at the position specified by the user in the list.
{
    printf("\n\nEnter a value to be inserted in the list: ");
    int ele;
    scanf("%d", &ele); // 'value' to be put in the inserted node.
    struct node* newNode = (struct node*) malloc(sizeof(struct node)); // Creating the node (Allocating memory) to be inserted in the list.
    newNode -> value = ele; // Putting the value in the node which is to be inserted in the list.

    if(head == NULL) // or tail == NULL // When the list is empty. // Making the new node 'newNode' as the first node. // Here we need to change head's as well as tail's value.
    {
        head = newNode;
        tail = newNode;
        newNode -> next = newNode; // To maintain the circular property.
    }
    else // When the list contains at least 1 node.
    {
        printf("\nEnter the position at which you wanna insert the element: ");
        int pos;
        int max = traversal(1) + 1;
        do // Input validation for variable 'pos'.
        {
            scanf("%d", &pos);
            if(pos < 1 || pos > max)
                printf("Position values are natural numbers only and are less than or equal to the size of the list + 1. Enter again: ");
        } while (pos < 1 || pos > max); // +1 because, say, the list contains n nodes then we can insert another node at (n+1)th position too.
        
        struct node* trav = NULL;

        if(pos == 1) // Inserting a node at the start of the list (When the list already contains at least one node). // Here we need to change head's as well as tail's value.
        {
            newNode -> next = head;
            head = newNode;
            tail -> next = newNode; // To maintain the circular property.
        }
        else // Inserting a node at any position other than the start of the list (When the list already contains at least one node).
        {
            trav = travToPos(pos-1, 1);
            newNode -> next = trav -> next; // To maintain the circular property if pos = max, else, it also works to maintains the links correctly.
            trav -> next = newNode;
            if(pos == max) // This is a new case which was not in SLL as we have tail here which points to the last node of the list in Circular SLL.
                tail = newNode;
        }
    }
    printf("\n\n\nElement insertion successful.\n");
    traversal(0); // Displaying the whole linked-list after each node insertion.
}

// Different cases are made because to change head's position (if required - mentioned below), tail's position (if required - mentioned below), other nodes' positions (if required) while inserting a new node require different operations to be perfomred.
void deletion() // Deletes a node from the position specified by the user from the list.
{
    int delVal; // Temporary variable to store the 'value' part of the node that we are gonna delete. 

    if(head == NULL) // Empty list.
        printf("\nNo nodes detected.\n");

    else // When the list contains at least 1 node.
    {
        struct node* temp = NULL; // We make a temporary pointer 'temp' point to the node which we want to delete.

        if(head == tail) // When the list has only 1 node. // head != NULL right now as we are in the else part. That's why. // Here we need to change head's as well as tail's value.
        {
            temp = head;
            head = NULL;
            tail = NULL;
        }

        else // When the list has at least 2 nodes. // We make separate cases till 2 nodes as we have 2 pointers to keep track of the list here. In SLL we created separate cases till 1 node as there we have only one pointer 'head' to keep track of the list.
        {
            printf("\nEnter the position at which you wanna delete the element: ");
            int pos;
            do // Input validation for variable 'pos'.
            {
                scanf("%d", &pos);
                if(pos < 1 || pos > traversal(1))
                    printf("Position values are natural numbers only and are less than or equal to the size of the list. Enter again: ");
            } while (pos < 1 || pos > traversal(1));

            // int max = traversal(1); // Can use below as an alternative. max - 1 instead of pos - 1.

            if(pos == 1) // Deleting the first node. // Here we need to change head's as well as tail's value. Tail's value due to the circular property.
            {
                temp = head;
                head = head -> next;
                tail -> next = head; // To maintain the circular property.
            }
            
            else // Deleting a node from any position other than the start of the list. // Here we need to change tail's value only if we are deleting the last node.
            {
                struct node* trav = travToPos(pos-1, 1); // For deleting the element at position 'pos', we make 'trav' point to the node at the position one less than that position.
                temp = trav -> next;
                trav ->  next = (trav -> next) -> next; // or temp -> next; // To maintain the circular property if pos = max. // Also makes possible here itself the case of deletion of the last node where the second last node which becomes the last node (after deletion of the current last node) points to the first node.
                if(temp == tail) // or pos == max // Here we need to change tail's value as we are deleting the last node.
                    tail = trav;
            }  
        }
        delVal = temp -> value; // Storing the 'value' of the node being deleted before deleting it.
        realloc(temp, 0); // Deallocation of memory of the node being deleted.
        temp = NULL; // Pointing to NULL to avoid a dangling pointer (even for a while). Dangling pointers are pointers that point to certain memory address - occurs at the time of the object destruction when the object is deleted or de-allocated from memory without modifying the value of the pointer. They can also become security holes.
        printf("\nElement deletion successful.\n");
        printf("\nElement deleted is: %d.\n", delVal);
    }
    traversal(0); // Displaying the whole linked-list after each node insertion.
}

void search() // Searching for all instances of a data value entered by the user.
{
    printf("\nEnter the data value that needs to be searched: ");
    int data;
    scanf("%d", &data);

    int flag = 0; // Used to track whether we have found at least one instance of the value or not.

    struct node* trav = head;

    for(int i = 1; i <= traversal(1); i++) // Traversing the nodes till the current size of the list. // i is used to dispay the positions of the value if found in the list. // i = 1 because initially we(trav) point(s) to head above the for loop, that is, we are at the position 1 in the list. Even if the list is empty we are not using the value of i later in the code after the loop as we won't enter the loop (i's value is only used inside the loop and we enter the loop if the list contains at least 1 element) in that case, so, setting i to 1 makes no difference in that case. Otherwise, if the list contains at least 1 node, initially, i = 1 means we point to position 1 in the list that is at the first node which is also pointed to by trav.
    {
        if(data == trav -> value)
        {
            printf("\nData found at position: %d.", i);
            flag = 1; // If found at atleast one instance of the value, then set flag to 1.
        }
        trav = trav -> next;
    } // After exiting the loop i contains the value = no. of elements in the list + 1 and trav contains head (and not NULL due to the circular list). As we don't use i and trav outside the loop, so it doesn't matter.
    if(flag == 0)
        printf("\nData not found.\n");

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