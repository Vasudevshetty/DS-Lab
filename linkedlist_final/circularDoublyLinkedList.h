/*This header file contains doubly circualr linked list methods and it's structure...
the functions avaliable are, insertion and deletion at head,tail and specific position, serach and delete a key,
reverse the contents, copy the contents of the list, create a ordered list.*/

#ifndef CircularDoubly_h
#define CircularDoubly_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// the data feild will be by default int, if wanted we can override..
typedef struct Node
{
    int data;
    struct Node *next;
    struct Node *prev;
} node;

typedef struct
{
    struct Node *Head;
    struct Node *Tail;
    int Length;
    // we can add any type of extra meta data realated to it like max, min ...etc.
} circularDoublyList;

#define head list->Head->next
#define tail list->Tail
#define length list->Length

// functions to create the node, init the list and destruct the list.
node *createNode(int data)
{
    // create the node using dynamic memory allocation.
    node *newNode = (node *)malloc(sizeof(node));
    if (!newNode)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = newNode->prev = newNode;
    return newNode;
}

// function to init the list.
circularDoublyList *initList()
{
    circularDoublyList *list = (circularDoublyList *)malloc(sizeof(circularDoublyList));
    if (!list)
    {
        printf("Memeory allocation failed.\n");
        exit(1);
    }
    list->Head = createNode(0);
    head = tail = NULL;
    length = 0;
    return list;
}

// support functions ...
bool isEmpty(circularDoublyList *list)
{
    return !(head && tail && length);
}
// function to destruct the list.
void destructList(circularDoublyList *list)
{
    if (!isEmpty(list))
    {

        node *temp = head;
        do
        {
            node *next = temp->next;
            free(temp);
            temp = next;
        } while (temp != head);
    }
    free(list->Head);
    free(list);
}

// sorted condition check
bool isSorted(circularDoublyList *list)
{
    if(isEmpty(list))
        return true;
    node *temp = head;
    while (temp->next != head)
    {
        if (temp->data < temp->next->data)
            temp = temp->next;
        else
            return false;
    }
    return true;
}

// display function.
void display(circularDoublyList *list)
{
    if (isEmpty(list))
    {
        printf("Empty list, display failed.\n");
        return;
    }
    node *temp = head;
    printf("Elements of the list are, \n");
    do
    {
        printf("%d <=> ", temp->data);
        temp = temp->next;
    } while (temp != head);
    printf("%d\nThe length(nodes count) of the list are %d\n", temp->data, length);
}

// insertion functions.
void insertAtHead(circularDoublyList *list, int data)
{
    node *newNode = createNode(data);
    if (isEmpty(list))
        head = tail = newNode;
    else
    {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
        head->prev = tail;
        tail->next = head;
    }
    length++;
}

// insert at tail.
void insertAtTail(circularDoublyList *list, int data)
{
    if (isEmpty(list))
        return insertAtHead(list, data);
    node *newNode = createNode(data);
    tail->next = newNode;
    newNode->prev = tail;
    tail = newNode;
    tail->next = head;
    head->prev = tail;
    length++;
}

void insertAtPosition(circularDoublyList *list, int data, int position)
{
    if (position < 0 || position > length)
    {
        printf("Invalid position, insertion failed.\n");
        return;
    }
    if (position == 0)
        return insertAtHead(list, data);
    if (position == length)
        return insertAtTail(list, data);

    node *temp = head;
    for (int i = 0; i < position - 1; i++)
        temp = temp->next;
    node *newNode = createNode(data);
    newNode->next = temp->next;
    temp->next->prev = newNode;
    newNode->prev = temp;
    temp->next = newNode;
    length++;
}

// deletion functions.
int deleteAtHead(circularDoublyList *list)
{
    if (isEmpty(list))
    {
        printf("Empty list, deletion failed.\n");
        return -1;
    }
    node *toDelete = head;
    if (length == 1)
    {
        head = tail = NULL;
    }
    else
    {
        head = toDelete->next;
        tail->next = head;
        head->prev = tail;
    }
    int data = toDelete->data;
    free(toDelete);
    length--;
    return data;
}

// delete at tail function.
int deleteAtTail(circularDoublyList *list)
{
    if (isEmpty(list))
    {
        printf("Empty list, deletion failed.\n");
        return -1;
    }
    if (length == 1)
        return deleteAtHead(list);
    node *toDelete = tail;
    int data = toDelete->data;
    tail = tail->prev;
    tail->next = head;
    head->prev = tail;
    free(toDelete);
    length--;
    return data;
}

// deletion at specific position.
int deleteAtPosition(circularDoublyList *list, int position)
{
    if (isEmpty(list))
    {
        printf("Empty list, deletion failed.\n");
        return -1;
    }
    if (position < 0 || position >= length)
    {
        printf("Invalid position, deletion failed.\n");
        return -1;
    }
    if (position == 0)
        return deleteAtHead(list);
    if (position == length - 1)
        return deleteAtTail(list);

    node *temp = head;
    for (int i = 0; i < position - 1; i++)
        temp = temp->next;
    node *toDelete = temp->next;
    int data = toDelete->data;
    temp->next = toDelete->next;
    toDelete->next->prev = temp;
    free(toDelete);
    length--;
    return data;
}

node *searchByKey(circularDoublyList *list, int key)
{
    node *temp = head;
    do
    {
        if (temp->data == key)
            return temp;
        else
            temp = temp->next;
    } while (temp != head);
    return NULL;
}

int deleteByKey(circularDoublyList *list, int key)
{
    if (isEmpty(list))
    {
        printf("List is empty, deletion failed.\n");
        return -1;
    }
    node *toDelete = searchByKey(list, key);
    if (!toDelete)
    {
        printf("Element not found, deletion failed.\n");
        return -1;
    }
    if (toDelete == head)
        return deleteAtHead(list);
    else if (toDelete == tail)
        return deleteAtTail(list);
    else
    {
        node *temp = toDelete->prev;
        temp->next = toDelete->next;
        toDelete->next->prev = temp;
        int data = toDelete->data;
        free(toDelete);
        length--;
        return data;
    }
}

circularDoublyList* copyList(circularDoublyList* original){
    node *temp = original->Head->next;
    circularDoublyList *copy = initList();
    do{
        insertAtTail(copy, temp->data);
        temp = temp->next;
    } while (temp != original->Head->next);
    return copy;
}

void reverse(circularDoublyList* list){
    node *current = head, *next, *previous = tail;
    do{
        next = current->next;

        current->next = previous;
        current->prev = next;

        previous = current;
        current = next;
    } while (current != head);
    head = tail;
    tail = head->prev;
}

void createOrderedList(circularDoublyList* list, int data){
    if(!isSorted(list)){
        printf("List isn't sorted, insertion and creation of ordered list failed.\n");
        return;
    }
    if(isEmpty(list) || data < head->data)
        return insertAtHead(list, data);
    if(data > tail->data)
        return insertAtTail(list, data);
    else{
        int position = 0;
        node *temp = head;
        do{
            if(temp->data > data)
                break;
            temp = temp->next;
            position++;
        } while (temp != head);
        return insertAtPosition(list, data, position);
    }
}

#endif