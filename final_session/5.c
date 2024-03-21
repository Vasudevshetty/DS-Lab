/*Implement circular single linked list to perform the following operations
i) Insert by order ii ) Delete by position iii) Search for an item by key iv) Delete by key
Display the list contents after each operation*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node
{
    int data;
    struct Node *next;
    struct Node *prev;
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
        list->head->next = list->tail= newNode;
    else
    {
        newNode->next = list->head->next;
        list->head->next->prev = newNode;
        list->head->next = newNode;

        list->tail->next = list->head->next;
        list->head->next->prev = list->tail;
    }
    list->length++;
}

void insertAtTail(DoubleList* list, int data){
    if(isEmpty(list)) return insertAtHead(list, data);

    Node* newNode= initNode(data);

    newNode->prev = list->tail;
    list->tail->next = newNode;
    list->tail = newNode;
    list->tail->next = list->head->next;
    list->head->next->prev = list->tail;

    list->length++;
}

void insertInOrder(DoubleList *list, int data)
{
    if (isEmpty(list) || list->head->next->data > data)
        return insertAtHead(list, data);
    if(data > list->tail->data)
        return insertAtTail(list, data);

    Node *newNode = initNode(data);

    Node *temp = list->head->next;
    while (temp->next != list->head->next && temp->next->data < data)
        temp = temp->next;

    newNode->prev = temp;
    newNode->next = temp->next;
    temp->next->prev = newNode;
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

    list->tail = list->tail->prev;
    list->tail->next = list->head->next;
    list->head->next->prev = list->head->next;

    free(toDelete);
    list->length--;
    return data;
}

int deleteByPosition(DoubleList *list, int position)
{
    if (isEmpty(list))
    {
        printf("List is emtpy, cannot delete.\n");
        return -1;
    }
    if (position < 0 || position >= list->length)
    {
        printf("Invalid position to delete.\n");
        return -1;
    }

    if (position == 0)
        return deleteAtHead(list);
    if (position == list->length - 1)
        return deleteAtTail(list);

    Node *temp = list->head->next;
    for (int i = 0; i < position - 1; i++)
        temp = temp->next;

    Node *toDelete = temp->next;
    int data = toDelete->data;

    temp->next = toDelete->next;
    toDelete->next->prev = temp;

    free(toDelete);
    list->length--;
    return data;
}

Node *searchBykey(DoubleList *list, int key)
{
    Node *temp = list->head->next;
    do
    {
        if (temp->data == key)
            return temp;
        temp = temp->next;
    } while (temp != list->head->next);
    return NULL;
}

int deleteByKey(DoubleList *list, int key)
{
    if (isEmpty(list))
    {
        printf("List is empty, cannot delete.\n");
        return -1;
    }
    Node *toDelete = searchBykey(list, key);

    if (!toDelete)
    {
        printf("key not found to delete.\n");
        return -1;
    }

    if (toDelete == list->head->next)
        return deleteAtHead(list);
    if (toDelete == list->tail)
        return deleteAtTail(list);

    int data = toDelete->data;

    Node *temp = toDelete->prev;

    temp->next = toDelete->next;
    toDelete->next->prev = temp;

    free(toDelete);
    list->length--;
    return data;
}

int main()
{
    DoubleList *list = initList();
    int data, position, key;
    int choice;

    do
    {
        printf("\nMenu\n");
        printf("1. Insert in order\n2. Delete by Position\n3. Search by key\n4. Delete by Key\n5. Exit\n");
        printf("Enter choice : ");
        scanf("%d", &choice);
        printf("\n");

        switch (choice)
        {
        case 1:
            printf("Enter data : ");
            scanf("%d", &data);
            insertInOrder(list, data);
            display(list);
            break;
        case 2:
            printf("Enter position : ");
            scanf("%d", &position);
            deleteByPosition(list, position);
            display(list);
            break;
        case 3:
            printf("Enter key : ");
            scanf("%d", &key);
            if (searchBykey(list, key))
                printf("Key found.\n");
            else
                printf("Key not found.\n");
            break;
        case 4:
            printf("Enter key : ");
            scanf("%d", &key);
            deleteByKey(list, key);
            display(list);
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