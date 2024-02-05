/*The dynamic queue implmenting using linked list.*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node
{
    int data;
    struct Node *next;
} node;

typedef struct
{
    node *front;
    node *rear;
    int size;
} queue;

node *createNode(int data)
{
    node *newNode = (node *)malloc(sizeof(node));
    if (!newNode)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

queue *initQueue()
{
    queue *que = (queue *)malloc(sizeof(queue));
    if (!que)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    que->front = que->rear = NULL;
    que->size = 0;
    return que;
}

bool isEmpty(queue *que)
{
    return !(que->front && que->rear && que->size);
}

void enqueue(queue *que, int data)
{
    node *newNode = createNode(data);
    if(isEmpty(que)){
        que->rear = que->front = newNode;
    }else{
        que->rear->next = newNode;
        que->rear = newNode;
    }
    que->size++;
}

int dequeue(queue *que)
{
    if (isEmpty(que))
    {
        printf("Stack over flow, deletion failed.\n");
        return -1;
    }
    node *toDelete = que->front;
    int data = toDelete->data;
    if (que->front == que->rear && que->size == 1)
        que->front = que->rear = NULL;
    else
        que->front = toDelete->next;

    free(toDelete);
    que->size--;
    return data;
}

int front(queue *que)
{
    return isEmpty(que) ? -1 : que->front->data;
}

int rear(queue *que)
{
    return isEmpty(que) ? -1 : que->rear->data;
}

void display(queue *que)
{
    if (isEmpty(que))
    {
        printf("Queue under flow, no elements to dispay.\n");
        return;
    }
    node *temp = que->front;
    printf("Elements of the queue are, \n");
    while (temp)
    {
        printf("%d -- ", temp->data);
        temp = temp->next;
    }
    printf("Count : %d\n", que->size);
}

void destructQueue(queue *que)
{
    if (!isEmpty(que))
    {
        node *temp = que->front;
        while (temp)
        {
            node *next = temp->next;
            free(temp);
            temp = next;
        }
    }
    free(que);
}

int main()
{
    queue *que = initQueue();
    int data, choice;

    do
    {
        printf("Menu.\n1.Enqueue\n2.Dequeue\n3.Front\n4.Rear\n5.Display\n6.Exit\n");
        printf("Enter your choice : ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter data : ");
            scanf("%d", &data);
            enqueue(que, data);
            display(que);
            break;
        case 2:
            data = dequeue(que);
            printf("The deleted(popped) elemnent is %d\n", data);
            display(que);
            break;
        case 3:
            printf("The front element of the queue is %d\n", front(que));
            break;
        case 4:
            printf("The rear element of the queue is %d\n", rear(que));
            break;
        case 5:
            display(que);
            break;
        case 6:
            printf("Exiting....\n");
            break;
        default:
            printf("Invlaid choice, please input right choice...\n");
            break;
        }
        printf("\n\n");
    } while (choice != 6);
    destructQueue(que);
    return 0;
}