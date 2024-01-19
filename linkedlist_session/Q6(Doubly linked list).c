/*Develop a menu driven program to implement Double linked list with various
operations such as
i) Insertion and Deletion at front/rear
ii) Insertion and Deletion at the specified position
iii) Delete by Key
iv) Search by key
v) Create an ordered list
vi) Reverse a list
vii) Creating a copy of the list*/

#include <stdio.h>
#include <stdlib.h>

// structure to store the node of the double linked list.
typedef struct Node
{
    int data;
    struct Node *next;
    struct Node *prev;
} node;

// structure to store the double linkedlist's head and tail and its length.
typedef struct
{
    node *head;
    node *tail;
    int length;
} doubleLinkedList;

// function to check conditions.
int isEmpty(doubleLinkedList *myList);
int isSorted(doubleLinkedList *myList);

// function to initalise the node and list.
node *createNode(int data);
void initNode(node *Node, int data);
doubleLinkedList *initDoubleLinkedList();

// function to insert.
void insertAtHead(doubleLinkedList *myList, int data);
void insertAtRear(doubleLinkedList *myList, int data);
void insertAtPosition(doubleLinkedList *myList, int data, int position);

// functions to delete.
int deleteAtHead(doubleLinkedList *myList);
int deleteAtRear(doubleLinkedList *myList);
int deleteAtPosition(doubleLinkedList *myList, int position);

// operation on keys.
node *searchByKey(doubleLinkedList *myList, int key);
int deleteByKey(doubleLinkedList *myList, int key);

// other operatins.
void createOrderedList(doubleLinkedList *myList, int data);
void reverse(doubleLinkedList *myList);
doubleLinkedList *copyList(doubleLinkedList *orginal);

// display function.
void display(doubleLinkedList *myList);

void destructList(doubleLinkedList *myList)
{
    node *temp = myList->head->next;
    while (temp)
    {
        node *next = temp->next;
        free(temp);
        temp = next;
    }
    free(myList->head);
    free(myList);
}

int main()
{
    doubleLinkedList *myList = initDoubleLinkedList();
    doubleLinkedList *copy;
    int choice, data, position, key;

    do
    {
        printf("\n\n");
        printf("Menu.\n");
        printf("1. Insert at head(front).\n");
        printf("2. Insert at rear\n");
        printf("3. Insert at specific position.\n");
        printf("4. Delete from head(front).\n");
        printf("5. Delete from rear(tail).\n");
        printf("6. Delete from specific position.\n");
        printf("7. Delete by key.\n");
        printf("8. Search by key.\n");
        printf("9. Create a ordered list.\n");
        printf("10. Reverse the linked list.\n");
        printf("11. Create a copy of the list.\n");
        printf("12.Display the list.\n");
        printf("13.Exit.\n");

        printf("Enter the choice of operation : ");
        scanf("%d", &choice);
        printf("\n\n");

        // added menu driven feature intend as you need.

        switch (choice)
        {
        case 1:
            printf("Enter data to insert at front: ");
            scanf("%d", &data);
            insertAtHead(myList, data);
            printf("\n\n");
            display(myList);
            break;
        case 2:
            printf("Enter data to insert at rear: ");
            scanf("%d", &data);
            insertAtRear(myList, data);
            printf("\n\n");
            display(myList);
            break;
        case 3:
            printf("Enter data to insert: ");
            scanf("%d", &data);
            printf("Enter position to insert at: ");
            scanf("%d", &position);
            insertAtPosition(myList, data, position);
            printf("\n\n");
            display(myList);
            break;
        case 4:
            deleteAtHead(myList);
            display(myList);
            break;
        case 5:
            deleteAtRear(myList);
            display(myList);
            break;
        case 6:
            printf("Enter position to delete: ");
            scanf("%d", &position);
            deleteAtPosition(myList, position);
            printf("\n\n");
            display(myList);
            break;
        case 7:
            printf("Enter key to delete: ");
            scanf("%d", &key);
            deleteByKey(myList, key);
            printf("\n");
            display(myList);
            break;
        case 8:
            printf("Enter key to search: ");
            scanf("%d", &key);
            searchByKey(myList, key);
            break;
        case 9:
            printf("Enter data to insert in the ordered list: ");
            scanf("%d", &data);
            createOrderedList(myList, data);
            printf("\n");
            display(myList);
            break;
        case 10:
            printf("Reversed list is,\n");
            reverse(myList);
            display(myList);
            break;
        case 11:
            copy = copyList(myList);
            display(myList);
            printf("Copied list is,\n");
            display(copy);
            destructList(copy);
            break;
        case 12:
            display(myList);
            break;
        case 13:
            printf("Exiting the program.....\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
    } while (choice != 13);
    destructList(myList);
    return 0;
}

node *createNode(int data)
{
    node *newNode = (node *)malloc(sizeof(node));
    if (!newNode)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    else
        initNode(newNode, data);
    return newNode;
}

// function to initalise the node of the linked list with given data.
void initNode(node *Node, int data)
{
    Node->data = data;
    Node->next = NULL;
    Node->prev = NULL;
}

// function to check the list is empty
int isEmpty(doubleLinkedList *myList)
{
    return !(myList->length && myList->head->next && myList->tail);
    /*This corrsponds to myList->length != 0 and myList->head->next != NULL and myList->tail != NULL. We should form a linked list such that,
    if the list is going to be empty all the above conditions should to be taken care.*/
}

// function to initalise the linked list.
doubleLinkedList *initDoubleLinkedList()
{
    doubleLinkedList *myList = (doubleLinkedList *)malloc(sizeof(doubleLinkedList));
    if (!myList)
    {
        printf("Memory allocaiton failed.\n");
        exit(1);
    }
    myList->head = createNode(0);
    myList->tail = NULL;
    myList->length = 0;
    return myList;
}

// function to insert at the head of the linkedlist.
void insertAtHead(doubleLinkedList *myList, int data)
{
    // create a new node and check memory allocation if done initalise.
    node *newNode = createNode(data);
    // check whether the list is empty,
    if (isEmpty(myList))
    {
        // if empty make tail and head same.
        myList->head->next = myList->tail = newNode;
    }
    else
    {
        // if the list is not empty, change the links as follows/
        newNode->next = myList->head->next;
        myList->head->next->prev = newNode;
        myList->head->next = newNode;
    }
    // increment the length.
    myList->length++;
}

// function to insert at rear part of the list.
void insertAtRear(doubleLinkedList *myList, int data)
{
    // check whether the given list is empty.
    if (isEmpty(myList))
    {
        // if empty rear and head are same upon insertion.
        return insertAtHead(myList, data);
    }

    // create a newnode if allcoated initalise.
    node *newNode = createNode(data);

    // using a temp pointer upon tail add new node and change links as follows.
    node *temp = myList->tail;

    /*This is the main differnece in a double linked list we can traverse from any direction having that in mind
    insertion or deletion from rear part's time complexity in regualar linekd list is O(n) but in double linkd list
    it reduces down to O(1) constant time.(n is the no of elements).*/

    newNode->prev = myList->tail;
    temp->next = newNode;
    myList->tail = newNode;

    // increment the length.
    myList->length++;
}

// function to insert at a specific postiion.
void insertAtPosition(doubleLinkedList *myList, int data, int position)
{
    // check the position is valid or not.
    if (position < 0 || position > myList->length)
    {
        printf("Invalid position to insert.\n");
        return;
    }

    // if the given position is zero, which means to insert at head call insertathead fn.
    if (position == 0)
        return insertAtHead(myList, data);

    // if the given position is last position, insert at rear.
    if (position == myList->length)
        return insertAtRear(myList, data);

    // if the given position is valid and not the head or rear's position
    // then create a node if allocated iniatlise.
    node *newNode = createNode(data);

    // using a temp pointer move towards the desired position.
    node *temp = myList->head->next;
    for (int i = 0; i < position - 1; i++)
        temp = temp->next;

    // change the links such that a newnode gets inserted without distrubing any order.
    newNode->next = temp->next;
    temp->next->prev = newNode;
    newNode->prev = temp;
    temp->next = newNode;

    // incremente the length of the pointer.
    myList->length++;
}

// function to delete at the head part of the linked list.
int deleteAtHead(doubleLinkedList *myList)
{
    // check whether there are elements to delete.
    if (isEmpty(myList))
    {
        printf("No elements to delete.\n");
        return -1;
    }

    // check whether  the head is null, shouldn't occur in a program.
    if (!myList->head->next)
    {
        printf("Error: head is null.\n");
        return -1;
    }

    // then take the address of the head to be deleted along extracting data.
    node *toDelete = myList->head->next;
    int data = toDelete->data;

    // special case where the list conatins only one element.
    if (!toDelete->next)
    {
        // in that case we have to make the list empty. (note isEmpty() condition) where length gets decremented later.
        myList->head->next = NULL;
        myList->tail = NULL;
    }
    else
    {
        // if that isn't the case change the links accordingly.
        myList->head->next = myList->head->next->next;
        // i.e // make second element as new head.
        myList->head->next->prev = NULL;
    }

    // deallcoate the data and return the data.
    free(toDelete);
    myList->length--; // decrement the length.

    return data;
}

// function to delete at the rear part of the linkedlist.
int deleteAtRear(doubleLinkedList *myList)
{
    // check whether there are elements to delete
    if (isEmpty(myList))
    {
        printf("No elements to delete.\n");
        return -1;
    }

    // check whether the list is not corrupted or not.
    if (!myList->tail)
    {
        printf("Error: Tail is NULL.\n");
        return -1;
    }

    // take the address of the tail to be deleted and extracting the data.
    node *toDelete = myList->tail;
    int data = toDelete->data;

    // if the list conatins only one element(spcl case)
    if (!toDelete->prev)
    {
        // then to make it empty chane the links.
        myList->head->next = NULL;
        myList->tail = NULL;
    }
    else
    {
        // if it isn't the case, change the link accordingly,
        myList->tail = myList->tail->prev;
        // i.e make last-second element as new rear element.
        myList->tail->next = NULL;
    }

    free(toDelete);
    myList->length--;

    return data;
}

// function to delete at given position in a linked list.
int deleteAtPosition(doubleLinkedList *myList, int position)
{
    // check whether the given position is valid or not.
    if (position < 0 || position >= myList->length)
    {
        printf("Invalid position to delete.\n");
        return -1;
    }

    // check whether the given position is head(0)
    if (position == 0)
        return deleteAtHead(myList);
    // check whetehr it is rear element.
    if (position == myList->length - 1)
        return deleteAtRear(myList);

    // if itsn't the head or rear using a pointer move to the desired position.
    node *temp = myList->head->next;
    while (position > 1)
    {
        temp = temp->next;
        position--;
    }

    node *toDelete = temp->next;
    int data = toDelete->data;

    temp->next = toDelete->next;
    toDelete->next->prev = temp;

    myList->length--;
    return data;
}

// function to search a key and return the node pointer.
node *searchByKey(doubleLinkedList *myList, int key)
{
    if (isEmpty(myList))
        return NULL;

    // using a pointer search while traversing if found return.
    node *temp = myList->head->next;
    while (temp)
    {
        if (temp->data == key)
        {
            printf("Element found.\n");
            return temp;
        }
        temp = temp->next;
    }
    // if not found. i.e exited the loop suppose.
    printf("Element not found.\n");
    return NULL;
}

// function to delete the key present in the linked list.
int deleteByKey(doubleLinkedList *myList, int key)
{
    node *toDelete = searchByKey(myList, key);

    // check whether the todelete actually returned a node.
    if (!toDelete)
    {
        printf("Deletion failed.\n");
        return -1;
    }

    // check whether todelete returned node is head or tail if call delete functions accordingly.
    if (toDelete == myList->head->next)
        return deleteAtHead(myList);
    if (toDelete == myList->tail)
        return deleteAtRear(myList);

    // if it isn't the head or tail find the node before the todelete node so as to change links.
    node *temp = toDelete->prev;
    //  note this point this makes double linkedlist very usefull.

    // change links.
    temp->next = toDelete->next;
    toDelete->next->prev = temp;

    // take out the data and free the memory.
    int data = toDelete->data;
    free(toDelete);

    // decrement the length and return the data.
    myList->length--;
    return data;
}

// function to check whether the list is sorted.
int isSorted(doubleLinkedList *myList)
{
    if (isEmpty(myList) || myList->length == 1)
    {
        // an empty or single element list is always considered sorted.
        return 1; // true.
    }

    // traverse using a pointer alongside compare.
    node *temp = myList->head->next;
    while (temp->next)
    {
        if (temp->data <= temp->next->data)
            temp = temp->next;
        else
            return 0;
    }

    // if completely traversed.
    return 1;
}

// function to create ordered list.
void createOrderedList(doubleLinkedList *myList, int data)
{
    if (!isSorted(myList))
    {
        printf("List isn't sorted. Insertion failed.\n");
        return;
    }

    // check whether the list is empty or the data is the least.
    if (isEmpty(myList) || data <= myList->head->next->data)
    {
        return insertAtHead(myList, data);
    }
    // check whether the data is the highest.
    if (data >= myList->tail->data)
    {
        return insertAtRear(myList, data);
    }

    // create a newnode if it isn't least or highest, if allocated initalise.
    node *newNode = createNode(data);

    // find the appropriate positon to insert the data.
    node *temp = myList->head->next;
    while (temp->next && temp->next->data < data)
    {
        temp = temp->next;
    }

    // insert the data.
    newNode->next = temp->next; // append the remaining nodes to new node.

    if (temp->next)
        temp->next->prev = newNode; // check whether if it isn't null only then change the reamaining node's previous to new node.

    // adjust the link with inserted positions.
    newNode->prev = temp;
    temp->next = newNode;
    // visulise with paper for better understanding.

    myList->length++; // increment the length.
}

// function to reverse
void reverse(doubleLinkedList *myList)
{
    // check whether the list is empty.
    if (isEmpty(myList))
    {
        printf("No elements to reverse.\n");
        return;
    }

    // have three pointers.
    node *current = myList->head->next;
    node *next = NULL;
    node *prev = NULL;

    // traverse along
    while (current)
    {
        // save the next.
        next = current->next;

        // reverse the links.
        current->next = prev;
        current->prev = next;

        // move the prev pointer to current node
        prev = current;
        // similarly move the current pointer to next pointer.
        current = next;
    }

    // update the exchanged heads and tails.
    myList->tail = myList->head->next;
    myList->head->next = prev;
}

// function to copy the list to another list and return.
doubleLinkedList *copyList(doubleLinkedList *orginal)
{
    // create a copy double linkedlist and initalise.
    doubleLinkedList *copy = initDoubleLinkedList();

    // found empty return a null initalised list.
    if (isEmpty(orginal))
        return copy;

    // traverse along the orginal list and insert the data into duplicate(copy).
    node *temp = orginal->head->next;
    while (temp)
    {
        insertAtRear(copy, temp->data);
        temp = temp->next;
    }
    return copy;
}

// function to display the linked list.
void display(doubleLinkedList *myList)
{
    // check whether the list is empty
    if (isEmpty(myList))
    {
        printf("No elements to display.\n");
        return;
    }

    // using a pointer from the head traverse along side print.(display)
    node *temp = myList->head->next;

    printf("Elements of the list are,\n");
    printf("NULL<=>");
    while (temp)
    {
        printf("%d<=>", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}