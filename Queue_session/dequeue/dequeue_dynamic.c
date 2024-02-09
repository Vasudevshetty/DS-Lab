/*Implement Double Ended Queue with static and dynamic memory allocation
mechanisms using array storage representation. (Represent Queue using
structure)*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define max_size 100

typedef struct Node
{
    int data;
    struct Node *next;
    struct Node *prev;
} node;
// having a doubly linked node helps in reducing dequeueing and enqueueing operation to constant time.

typedef struct
{
    node *front;
    node *rear;
    int count;
} dequeue;

// function to allocate memor.
dequeue *initdequeue();

// operations
void enqueueFront(dequeue *que, int data);
void enqueueRear(dequeue *que, int data);
int dequeueFront(dequeue *que);
int dequeueRear(dequeue *que);
int front(dequeue *que);
int rear(dequeue *que);

// supporting functions
void display(dequeue *que);
bool isEmpty(dequeue *que);

void destructQeueue(dequeue *que);

int main()
{
    int data, choice;
    dequeue *que = initdequeue();

    do
    {
        printf("\n\n");
        printf("Menu\n");
        printf("1. EnqueueFront(push).\n");
        printf("2. EnqueueRear(push).\n");
        printf("3. dequeueFront(pop). \n");
        printf("4. dequeueRear(pop). \n");
        printf("5. Front(peek).\n");
        printf("6. Rear(peek).\n");
        printf("7. Display\n");
        printf("8. Exit.\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter the data to enqueue: ");
            scanf("%d", &data);
            enqueueFront(que, data);
            display(que);
            break;
        case 2:
            printf("Enter the data to enqueue: ");
            scanf("%d", &data);
            enqueueRear(que, data);
            display(que);
            break;
        case 3:
            data = dequeueFront(que);
            if (data != -1)
                printf("The dequeueued data from front is %d\n", data);
            display(que);
            break;
        case 4:
            data = dequeueRear(que);
            if (data != -1)
                printf("The dequeueued data from rear is %d\n", data);
            display(que);
            break;
        case 5:
            if (front(que) != -1)
                printf("The front of the queue is %d\n", front(que));
            break;
        case 6:
            if (rear(que) != -1)
                printf("The rear of the queue is %d\n", rear(que));
            break;
        case 7:
            display(que);
            break;
        case 8:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice. Try again.\n");
            break;
        }
    } while (choice != 8);

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
    newNode->data = data;
    newNode->next = newNode->prev = NULL;
    return newNode;
}

dequeue *initdequeue()
{
    dequeue *que = (dequeue *)malloc(sizeof(dequeue));
    if (!que)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    que->front = que->rear = NULL;
    que->count = 0;
    return que;
}

bool isEmpty(dequeue* que){
    return !(que->front && que->rear && que->count);
}

void enqueueFront(dequeue* que, int data){
    node *newNode = createNode(data);
    if(isEmpty(que)){
        que->front = que->rear = newNode;
    }else{
        newNode->next = que->front;
        que->front->prev = newNode;
        que->front = newNode;
    }
    que->count++;
}

void enqueueRear(dequeue* que, int data){
    node *newNode = createNode(data);
    if(isEmpty(que))
        return enqueueFront(que, data);
    else{
        newNode->prev = que->rear;
        que->rear->next = newNode;
        que->rear = newNode;
    }
    que->count++;
}

int dequeueFront(dequeue* que){
    if(isEmpty(que)){
        printf("Stack underflow, deletion (dequing) failed).\n");
        return -1;
    }
    node *toDelete = que->front;
    int data = toDelete->data;
    if(que->front == que->rear)
        que->front = que->rear = NULL;
    else{
        que->front = toDelete->next;
        que->front->prev = NULL;
    }
    free(toDelete);
    que->count--;
    return data;
}

int dequeueRear(dequeue* que){
    if(isEmpty(que)){
        printf("Stack under flow, deletion (dequeueing failed).\n");
        return -1;
    }
    node *toDelete = que->rear;
    int data = toDelete->data;
    if(que->front == que->rear)
        return dequeueFront(que);
    que->rear = toDelete->prev;
    que->rear->next = NULL;
    free(toDelete);
    return data;
}

int rear(dequeue* que){
    return isEmpty(que) ? -1 : que->rear->data;
}

int front(dequeue* que){
    return isEmpty(que) ? -1 : que->front->data;
}

void display(dequeue* que){
    if(isEmpty(que)){
        printf("Qeueue underflow, no elementst to display.\n");
        return;
    }
    node *temp = que->front;
    printf("The elements of the queue are, \n");
    while(temp){
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void destructQeueue(dequeue* que){
    if(!isEmpty(que)){
        node *temp = que->front;
        while(temp){
            node *next = temp->next;
            free(temp);
            temp = next;
        }
    }
    free(que);
}