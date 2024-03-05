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
} Node;

Node *initNode(int data)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode)
    {
        printf("Memory allcoation failed.\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = newNode;
    return newNode;
}

typedef struct CircularList
{
    Node *head;
    int length;
} CircularList;

CircularList *initList()
{
    CircularList *list = (CircularList *)malloc(sizeof(CircularList));
    if (!list)
    {
        printf("Memory allocaitn failed.\n");
        exit(1);
    }
    list->head = initNode(0);
    list->head->next = NULL;
    list->length = 0;
    return list;
}

bool isEmpty(const CircularList *list)
{
    return !(list->head->next && list->length);
}

void display(const CircularList *list)
{
    if (isEmpty(list))
    {
        printf("List is empty, cannot display.\n");
        return;
    }
    Node *temp = list->head->next;
    printf("The elements of the list are, \n");
    do
    {
        printf("%d->", temp->data);
        temp = temp->next;
    } while (temp != list->head->next);
    printf("%d\nThe length of the list is %d\n", temp->data, list->length);
}

void insertByOrder(CircularList *list, int data)
{
    Node *newNode = initNode(data);
    if (isEmpty(list))
    {
        list->head->next = newNode;
    }
    else
    {
        Node *temp = list->head->next;

        while (temp->next != list->head->next && temp->data < data)
            temp = temp->next;

        newNode->next = temp->next;
        temp->next = newNode;
    }
    list->length++;
}

Node *searchByKey(CircularList *list, int key)
{
    if (isEmpty(list))
    {
        printf("List is empty, cannot delete.\n");
        return NULL;
    }
    Node *temp = list->head->next;
    do
    {
        if (temp->data == key)
            return temp;
        else
            temp = temp->next;
    } while (temp != list->head->next);
    return NULL;
}

int deleteByPosition(CircularList *list, int position)
{
    if (isEmpty(list))
    {
        printf("List is empty, canot delete.\n");
        return -1;
    }
    if (position < 0 || position > list->length)
    {
        printf("INvalid postion to delet.\n");
        return -1;
    }

    Node *temp = list->head->next, *toDelete;
    if (position == 0)
    {
        toDelete = list->head->next;
        while (temp->next != toDelete)
            temp = temp->next;
        list->head->next = toDelete->next;
        temp->next = list->head->next;
    }
    else
    {
        for (int i = 0; i < position - 1; i++)
            temp = temp->next;

        toDelete = temp->next;
        temp->next = toDelete->next;
    }

    list->length--;
    int data = toDelete->data;
    free(toDelete);
    return data;
}

int main()
{
    CircularList *list = initList();
    for (int i = 0; i < 10; i++)
    {
        insertByOrder(list, i + 1);
        display(list);
        printf("\n");
    }
    for (int i = 9; i >= 0; i--)
    {
        deleteByPosition(list, i);
        display(list);
        printf("\n");
    }
    return 0;
}