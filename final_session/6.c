/*Implement circular single linked list to perform the following operations
i) Insert front ii) Insert rear iii) Delete a node with the given key iv) Search for an item byposition
Display the list contents after each operatio*/

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
        printf("Memory allocation failed.\n");
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
        printf("Memory allocation failed.\n");
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

void freeList(CircularList *list)
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

void insertAtHead(CircularList *list, int data)
{
    Node *newNode = initNode(data);
    if (isEmpty(list))
        list->head->next = newNode;
    else
    {
        Node *temp = list->head->next;
        while (temp->next != list->head->next)
            temp = temp->next;

        newNode->next = list->head->next;
        list->head->next = newNode;
        temp->next = list->head->next;
    }
    list->length++;
}

void insertAtTail(CircularList *list, int data)
{
    if (isEmpty(list))
        return insertAtHead(list, data);

    Node *newNode = initNode(data);

    Node *temp = list->head->next;
    while (temp->next != list->head->next)
        temp = temp->next;

    temp->next = newNode;
    newNode->next = list->head->next;
    list->length++;
}

int deleteAtHead(CircularList *list)
{
    if (isEmpty(list))
    {
        printf("List is empty, cannot delete.\n");
        return -1;
    }
    Node *toDelete = list->head->next;
    int data = toDelete->data;

    if (list->length == 1)
        list->head->next = NULL;
    else
    {
        Node *tail = list->head->next;
        while (tail->next != list->head->next)
            tail = tail->next;

        list->head->next = toDelete->next;
        tail->next = list->head->next;
    }

    free(toDelete);
    list->length--;
    return data;
}

int deleteAtTail(CircularList *list)
{
    if (isEmpty(list))
    {
        printf("List is emtpy, cannot delete.\n");
        return -1;
    }

    if (list->length == 1)
        return deleteAtHead(list);

    Node *temp = list->head->next;
    while (temp->next->next != list->head->next)
        temp = temp->next;

    Node *toDelete = temp->next;
    int data = toDelete->data;

    temp->next = list->head->next;

    free(toDelete);
    list->length--;
    return data;
}

Node *searchByPosition(CircularList *list, int position)
{
    if (position < 0 || position >= list->length)
    {
        printf("Invalid position to search.\n");
    }
    Node *temp = list->head->next;
    for (int i = 0; i < position; i++)
        temp = temp->next;
    return temp;
}

Node *searchBykey(CircularList *list, int key)
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

int deleteByKey(CircularList *list, int key)
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
    if (toDelete->next == list->head->next)
        return deleteAtTail(list);

    int data = toDelete->data;

    Node *temp = list->head->next;
    while (temp->next != toDelete && temp->next != list->head->next)
        temp = temp->next;

    temp->next = toDelete->next;

    free(toDelete);
    list->length--;
    return data;
}

int main()
{
    CircularList *list = initList();
    int data, position, key;
    int choice;

    do
    {
        printf("\nMenu\n");
        printf("1. Insert at head\n2. Insert at tail\n3. Search by position\n4. Delete by Key\n5. Exit\n");
        printf("Enter choice : ");
        scanf("%d", &choice);
        printf("\n");

        switch (choice)
        {
        case 1:
            printf("Enter data : ");
            scanf("%d", &data);
            insertAtHead(list, data);
            display(list);
            break;
        case 2:
            printf("Enter data : ");
            scanf("%d", &data);
            insertAtTail(list, data);
            display(list);
            break;
        case 3:
            printf("Enter position : ");
            scanf("%d", &position);
            Node *temp = searchByPosition(list, position);
            if(temp)
                printf("The data at the position is %d\n", temp->data);
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