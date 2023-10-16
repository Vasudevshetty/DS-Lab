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
struct node
{
    int data;
    struct node *next;
    struct node *prev;
};

// structure to store the double linkedlist's head and tail and its length.
struct doubleLinkedList
{
    struct node *head;
    struct node *tail;
    int length;
};

// function to check conditions.
int isEmpty(struct doubleLinkedList l);
int isSorted(struct doubleLinkedList l);

// function to initalise the node and list.
void initNode(struct node *Node, int data);
void initDoubleLinkedList(struct doubleLinkedList *l);

// function to insert.
void insertAtHead(struct doubleLinkedList *l, int data);
void insertAtRear(struct doubleLinkedList *l, int data);
void insertAtPosition(struct doubleLinkedList *l, int data, int position);

// functions to delete.
int deleteAtHead(struct doubleLinkedList *l);
int deleteAtRear(struct doubleLinkedList *l);
int deleteAtPosition(struct doubleLinkedList *l, int position);

// operation on keys.
struct node *searchByKey(struct doubleLinkedList l, int key);
int deleteByKey(struct doubleLinkedList *l, int key);

// other operatins.
void createOrderedList(struct doubleLinkedList *l, int data);
void reverse(struct doubleLinkedList *l);
struct doubleLinkedList copyList(struct doubleLinkedList orginal);

// display function.
void display(struct doubleLinkedList l);

int main()
{
    struct doubleLinkedList l;
    initDoubleLinkedList(&l);
    struct doubleLinkedList copy;
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
            insertAtHead(&l, data);
            printf("\n\n");
            display(l);
            break;
        case 2:
            printf("Enter data to insert at rear: ");
            scanf("%d", &data);
            insertAtRear(&l, data);
            printf("\n\n");
            display(l);
            break;
        case 3:
            printf("Enter data to insert: ");
            scanf("%d", &data);
            printf("Enter position to insert at: ");
            scanf("%d", &position);
            insertAtPosition(&l, data, position);
            printf("\n\n");
            display(l);
            break;
        case 4:
            deleteAtHead(&l);
            display(l);
            break;
        case 5:
            deleteAtRear(&l);
            display(l);
            break;
        case 6:
            printf("Enter position to delete: ");
            scanf("%d", &position);
            deleteAtPosition(&l, position);
            printf("\n\n");
            display(l);
            break;
        case 7:
            printf("Enter key to delete: ");
            scanf("%d", &key);
            deleteByKey(&l, key);
            printf("\n");
            display(l);
            break;
        case 8:
            printf("Enter key to search: ");
            scanf("%d", &key);
            searchByKey(l, key);
            break;
        case 9:
            printf("Enter data to insert in the ordered list: ");
            scanf("%d", &data);
            createOrderedList(&l, data);
            printf("\n");
            display(l);
            break;
        case 10:
            printf("Reversed list is,\n");
            reverse(&l);
            display(l);
            break;
        case 11:
            copy = copyList(l);
            display(l);
            printf("Copied list is,\n");
            display(copy);
            break;
        case 12:
            display(l);
            break;
        case 13:
            printf("Exiting the program.....\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
    } while (choice != 13);
    return 0;
}

// function to initalise the node of the linked list with given data.
void initNode(struct node *Node, int data)
{
    Node->data = data;
    Node->next = NULL;
    Node->prev = NULL;
}

// function to check the list is empty
int isEmpty(struct doubleLinkedList l)
{
    return !(l.length && l.head && l.tail);
    /*This corrsponds to l.length != 0 and l.head != NULL and l.tail != NULL. We should form a linked list such that,
    if the list is going to be empty all the above conditions should to be taken care.*/
}

// function to initalise the linked list.
void initDoubleLinkedList(struct doubleLinkedList *l)
{
    l->head = NULL;
    l->tail = NULL;
    l->length = 0;
}

// function to insert at the head of the linkedlist.
void insertAtHead(struct doubleLinkedList *l, int data)
{
    // create a new node and check memory allocation if done initalise.
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    if (!newNode)
    {
        printf("Memory allocation failed.\n");
        return;
    }
    else
        initNode(newNode, data);

    // check whether the list is empty,
    if (isEmpty(*l))
    {
        // if empty make tail and head same.
        l->head = l->tail = newNode;
    }
    else
    {
        // if the list is not empty, change the links as follows/
        newNode->next = l->head;
        l->head->prev = newNode;
        l->head = newNode;
    }
    // increment the length.
    l->length++;
}

// function to insert at rear part of the list.
void insertAtRear(struct doubleLinkedList *l, int data)
{
    // check whether the given list is empty.
    if (isEmpty(*l))
    {
        // if empty rear and head are same upon insertion.
        return insertAtHead(l, data);
    }

    // create a newnode if allcoated initalise.
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    if (!newNode)
    {
        printf("Memory allocation failed.\n");
        return;
    }
    else
        initNode(newNode, data);

    // using a temp pointer upon tail add new node and change links as follows.
    struct node *temp = l->tail;

    /*This is the main differnece in a double linked list we can traverse from any direction having that in mind
    insertion or deletion from rear part's time complexity in regualar linekd list is O(n) but in double linkd list
    it reduces down to O(1) constant time.(n is the no of elements).*/

    newNode->prev = l->tail;
    temp->next = newNode;
    l->tail = newNode;

    // increment the length.
    l->length++;
}

// function to insert at a specific postiion.
void insertAtPosition(struct doubleLinkedList *l, int data, int position)
{
    // check the position is valid or not.
    if (position < 0 || position > l->length)
    {
        printf("Invalid position to insert.\n");
        return;
    }

    // if the given position is zero, which means to insert at head call insertathead fn.
    if (position == 0)
        return insertAtHead(l, data);

    // if the given position is last position, insert at rear.
    if (position == l->length)
        return insertAtRear(l, data);

    // if the given position is valid and not the head or rear's position
    // then create a node if allocated iniatlise.
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    if (!newNode)
    {
        printf("Memory allocation failed.\n");
        return;
    }
    else
        initNode(newNode, data);

    // using a temp pointer move towards the desired position.
    struct node *temp = l->head;
    for (int i = 0; i < position - 1; i++)
        temp = temp->next;

    // change the links such that a newnode gets inserted without distrubing any order.
    newNode->next = temp->next;
    temp->next->prev = newNode;
    newNode->prev = temp;
    temp->next = newNode;

    // incremente the length of the pointer.
    l->length++;
}

// function to delete at the head part of the linked list.
int deleteAtHead(struct doubleLinkedList *l)
{
    // check whether there are elements to delete.
    if (isEmpty(*l))
    {
        printf("No elements to delete.\n");
        return -1;
    }

    // check whether  the head is null, shouldn't occur in a program.
    if (!l->head)
    {
        printf("Error: head is null.\n");
        return -1;
    }

    // then take the address of the head to be deleted along extracting data.
    struct node *toDelete = l->head;
    int data = toDelete->data;

    // special case where the list conatins only one element.
    if (!toDelete->next)
    {
        // in that case we have to make the list empty. (note isEmpty() condition) where length gets decremented later.
        l->head = NULL;
        l->tail = NULL;
    }
    else
    {
        // if that isn't the case change the links accordingly.
        l->head = l->head->next;
        // i.e // make second element as new head.
        l->head->prev = NULL;
    }

    // deallcoate the data and return the data.
    free(toDelete);
    l->length--; // decrement the length.

    return data;
}

// function to delete at the rear part of the linkedlist.
int deleteAtRear(struct doubleLinkedList *l)
{
    // check whether there are elements to delete
    if (isEmpty(*l))
    {
        printf("No elements to delete.\n");
        return -1;
    }

    // check whether the list is not corrupted or not.
    if (!l->tail)
    {
        printf("Error: Tail is NULL.\n");
        return -1;
    }

    // take the address of the tail to be deleted and extracting the data.
    struct node *toDelete = l->tail;
    int data = toDelete->data;

    // if the list conatins only one element(spcl case)
    if (!toDelete->prev)
    {
        // then to make it empty chane the links.
        l->head = NULL;
        l->tail = NULL;
    }
    else
    {
        // if it isn't the case, change the link accordingly,
        l->tail = l->tail->prev;
        // i.e make last-second element as new rear element.
        l->tail->next = NULL;
    }

    free(toDelete);
    l->length--;

    return data;
}

// function to delete at given position in a linked list.
int deleteAtPosition(struct doubleLinkedList *l, int position)
{
    // check whether the given position is valid or not.
    if (position < 0 || position >= l->length)
    {
        printf("Invalid position to delete.\n");
        return -1;
    }

    // check whether the given position is head(0)
    if (position == 0)
        return deleteAtHead(l);
    // check whetehr it is rear element.
    if (position == l->length - 1)
        return deleteAtRear(l);

    // if itsn't the head or rear using a pointer move to the desired position.
    struct node *temp = l->head;
    while (position > 1)
    {
        temp = temp->next;
        position--;
    }

    struct node *toDelete = temp->next;
    int data = toDelete->data;

    temp->next = toDelete->next;
    toDelete->next->prev = temp;

    l->length--;
    return data;
}

// function to search a key and return the node pointer.
struct node* searchByKey(struct doubleLinkedList l, int key){
    if(isEmpty(l)) return NULL;

    // using a pointer search while traversing if found return.
    struct node* temp = l.head;
    while(temp){
        if(temp->data == key){
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
int deleteByKey(struct doubleLinkedList *l, int key){
    struct node* toDelete = searchByKey(*l, key);

    // check whether the todelete actually returned a node.
    if(!toDelete){
        printf("Deletion failed.\n");
        return -1;
    }

    // check whether todelete returned node is head or tail if call delete functions accordingly.
    if(toDelete == l->head) return deleteAtHead(l);
    if(toDelete == l->tail) return deleteAtRear(l);

    // if it isn't the head or tail find the node before the todelete node so as to change links.
    struct node* temp = toDelete->prev;
    //  note this point this makes double linkedlist very usefull.
  
    // change links.
    temp->next = toDelete->next;
    toDelete->next->prev = temp;

    // take out the data and free the memory.
    int data = toDelete->data;
    free(toDelete);

    // decrement the length and return the data.
    l->length--;
    return data;
}

// function to check whether the list is sorted.
int isSorted(struct doubleLinkedList l){
    if(isEmpty(l) || l.length == 1){
        // an empty or single element list is always considered sorted.
        return 1; // true.
    }
    
    // traverse using a pointer alongside compare.
    struct node* temp = l.head;
    while(temp->next){
        if(temp->data < temp->next->data) temp = temp->next;
        else return 0;
    }

    // if completely traversed.
    return 1;
}

// function to create ordered list.
void createOrderedList(struct doubleLinkedList *l, int data){
    if(!isSorted(*l)){
        printf("List isn't sorted. Insertion failed.\n");
        return;
    }

    // check whether the list is empty or the data is the least.
    if(isEmpty(*l) || data <= l->head->data){
        return insertAtHead(l, data);
    }
    // check whether the data is the highest.
    if(data >= l->tail->data){
        return insertAtRear(l, data);
    }

    // create a newnode if it isn't least or highest, if allocated initalise.
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    if(!newNode){
        printf("Memory allocation failed.\n");
        return;
    }else initNode(newNode, data);

    // find the appropriate positon to insert the data.
    struct node* temp = l->head;
    while(temp->next && temp->next->data < data){
        temp = temp->next;
    }    

    // insert the data.
    newNode->next = temp->next; // append the remaining nodes to new node.
    
    if(temp->next)
    temp->next->prev = newNode; // check whether if it isn't null only then change the reamaining node's previous to new node.
    
    // adjust the link with inserted positions. 
    newNode->prev = temp;
    temp->next = newNode;
    // visulise with paper for better understanding.

    l->length++; // increment the length.
}

// function to reverse
void reverse(struct doubleLinkedList *l){
    // check whether the list is empty.     
    if(isEmpty(*l)){
        printf("No elements to reverse.\n");
        return;
    }

    // have three pointers.
    struct node* current = l->head;
    struct node* next = NULL;
    struct node* prev = NULL;

    // traverse along
    while(current){
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
    l->tail = l->head;
    l->head = prev;
}

// function to copy the list to another list and return.
struct doubleLinkedList copyList(struct doubleLinkedList orginal)
{
    // create a copy double linkedlist and initalise.
    struct doubleLinkedList copy;
    initDoubleLinkedList(&copy);

    // found empty return a null initalised list.
    if (isEmpty(orginal))
        return copy;

    // traverse along the orginal list and insert the data into duplicate(copy).
    struct node *temp = orginal.head;
    while (temp)
    {
        insertAtRear(&copy, temp->data);
        temp = temp->next;
    }
    return copy;
}

// function to display the linked list.
void display(struct doubleLinkedList l)
{
    // check whether the list is empty
    if (isEmpty(l))
    {
        printf("No elements to display.\n");
        return;
    }

    // using a pointer from the head traverse along side print.(display)
    struct node *temp = l.head;

    printf("Elements of the list are,\n");
    printf("NULL<=>");
    while (temp)
    {
        printf("%d<=>", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}