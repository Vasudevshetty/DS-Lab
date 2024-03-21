/*Implement circular single linked list to perform the following operations
i) Insert by position ii) Delete rear iii) Delete Front iv) Search for an item by valueDisplay the list contents
after each operation*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node
{
    int data;
    struct Node *next, *prev;
} Node;

Node *initNode(int data)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = newNode->prev = newNode;
    return newNode;
}

typedef struct DoubleList
{
    Node *head, *tail;
    int length;
} DoubleList;

DoubleList *initList()
{
    DoubleList *list = (DoubleList *)malloc(sizeof(DoubleList));
    if (!list)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    list->head = initNode(0);
    list->head->next = list->tail = NULL;
    list->length = 0;
    return list;
}

bool isEmpty(const DoubleList *list)
{
    return !(list->head->next && list->tail && list->length);
}

void display(const DoubleList *list)
{
    if (isEmpty(list))
    {
        printf("Empty list, display failed.\n");
        return;
    }
    printf("The elements of the list are, \n");
    Node *temp = list->head->next;
    do
    {
        printf("%d ", temp->data);
        temp = temp->next;
    } while (temp != list->head->next);
    printf("\nThe length of the list is %d\n", list->length);
}

void freeList(DoubleList *list)
{
    if (!isEmpty(list))
    {
        Node *temp = list->head->next;
        do
        {
            Node *next = temp->next;
            free(temp);
            temp = next;
        } while (temp != list->head->next);
        free(temp);
    }
    free(list->head);
    free(list);
}

void insertAtHead(DoubleList *list, int data)
{
    Node *newNode = initNode(data);
    if (isEmpty(list))
        list->head->next = list->tail = newNode;
    else
    {
        newNode->next = list->head->next;
        list->head->next->prev = newNode;
        list->head->next = newNode;
        list->head->next->prev = list->tail;
        list->tail->next = list->head->next;
    }
    list->length++;
}

void insertAtTail(DoubleList *list, int data)
{
    if (isEmpty(list))
        return insertAtHead(list, data);

    Node *newNode = initNode(data);

    list->tail->next = newNode;
    newNode->prev = list->tail;
    list->tail = newNode;
    list->tail->next = list->head->next;
    list->head->next->prev = list->tail;

    list->length++;
}

void insertByPosition(DoubleList* list, int data, int position){
    if(position < 0 || position > list->length){
        printf("Memory allocation failed.\n");
        return;
    }

    if(position == 0)
        return insertAtHead(list, data);
    if(position == list->length)
        return insertAtTail(list, data);

    Node *newNode = initNode(data);

    Node *temp = list->head->next;
    for (int i = 0; i < position - 1;i++)
        temp = temp->next;

    newNode->next = temp->next;
    temp->next = newNode;

    list->length++;
}

int deleteAtHead(DoubleList *list)
{
    if (isEmpty(list))
    {
        printf("List is empty, cannot delete.\n");
        return -1;
    }
    Node *toDelete = list->head->next;
    int data = toDelete->data;

    if (list->length == 1)
        list->head->next = list->tail = NULL;
    else
    {
        list->head->next = toDelete->next;
        list->head->next->prev = list->tail;
        list->tail->next = list->head->next;
    }

    free(toDelete);
    list->length--;
    return data;
}

int deleteAtTail(DoubleList *list)
{
    if (isEmpty(list))
    {
        printf("List is emtpy, cannot delete.\n");
        return -1;
    }

    if (list->length == 1)
        return deleteAtHead(list);

    Node *toDelete = list->tail;
    int data = toDelete->data;

    list->tail = toDelete->prev;
    list->tail->next = list->head->next;
    list->head->next->prev = list->tail;

    free(toDelete);
    list->length--;
    return data;
}

Node *searchBykey(DoubleList *list, int key)
{
    Node *temp = list->head->next;
    do
    {
        if (temp->data == key){
            printf("Key found.\n");
            return temp;
        }
        temp = temp->next;
    } while (temp != list->head->next);
    printf("Key not found.\n");
    return NULL;
}

int main()
{
    DoubleList *list = initList();
    int data, position, key;
    int choice;

    do
    {
        printf("\nMenu\n");
        printf("1. Insert at Position\n2. Delete at head\n3. Delete by tail\n4. Search by Key\n5. Exit\n");
        printf("Enter choice : ");
        scanf("%d", &choice);
        printf("\n");

        switch (choice)
        {
        case 1:
            printf("Enter data & position : ");
            scanf("%d %d", &data, &position);
            insertByPosition(list, data, position) ;
            display(list);
            break;
        case 2:
            deleteAtHead(list);
            display(list);
            break;
        case 3:
            deleteAtTail(list);
            display(list);
            break;
        case 4:
            printf("Enter key : ");
            scanf("%d", &key);
            searchBykey(list, key);
            break;
        case 5:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice, please try again.\n");
            break;
        }
    } while (choice != 5);
    freeList(list);
    return 0;
}