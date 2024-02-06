/*Implement Double Ended Queue with static and dynamic memory allocation
mechanisms using array storage representation. (Represent Queue using
structure)*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define max_size 100

// create a circular queue struct
typedef struct
{
    int *container; // to store the values.
    int front;      // pointer to manipulate from front.
    int rear;       // pointer to manipulate from rear.
    int size;       // variable size.
} dequeue;

// function to allocate memor.
dequeue *initdequeue(int size);

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
bool isFull(dequeue *que);

int main()
{
    int data, choice;
    int size;
    dequeue *que;
    printf("Enter the size of the queue : ");
    scanf("%u", &size);
    if (size < max_size)
        que = initdequeue(size);
    else
        que = initdequeue(max_size);

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

    free(que->container);
    free(que);

    return 0;
}

dequeue *initdequeue(int size)
{
    dequeue *deque = (dequeue *)malloc(sizeof(dequeue));
    if (!deque)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    deque->size = size;
    deque->container = (int *)malloc(size * sizeof(int));
    deque->front = deque->rear = -1;
    return deque;
}

bool isEmpty(dequeue *que)
{
    return que->front == -1 && que->rear == -1;
}

bool isFull(dequeue *que)
{
    return que->front == ((que->rear + 1) % que->size);
}

void enqueueRear(dequeue *que, int data)
{
    if (isFull(que))
    {
        printf("Queue over flow, enqueuing failed.\n");
        return;
    }

    if (isEmpty(que))
        que->front = que->rear = 0;
    else
        que->rear = (que->rear + 1) % que->size;

    que->container[que->rear] = data;
}

void enqueueFront(dequeue *que, int data)
{
    if (isFull(que))
    {
        printf("Queue over flow, enqueuing failed.\n");
        return;
    }
    if (isEmpty(que))
        que->front = que->rear = 0;
    else
        que->front = (que->front - 1 + que->size) % que->size;
    que->container[que->front] = data;
}

int dequeueFront(dequeue *que)
{
    if (isEmpty(que))
    {
        printf("Queue under flow, dequeueing failed.\n");
        return -1;
    }
    int data = que->container[que->front];
    if (que->front == que->rear)
        que->front = que->rear = -1;
    else
        que->front = (que->front + 1) % que->size;
    return data;
}

int dequeueRear(dequeue *que)
{
    if (isEmpty(que))
    {
        printf("Queue under flow, dequeuing failed.\n");
        return -1;
    }
    int data = que->container[que->rear];
    if (que->front == que->rear)
        que->front = que->rear = -1;
    else
        que->rear = (que->rear - 1 + que->size) % que->size;
    return data;
}

int front(dequeue *que)
{
    return isEmpty(que) ? -1 : que->container[que->front];
}

int rear(dequeue *que)
{
    return isEmpty(que) ? -1 : que->container[que->rear];
}

void display(dequeue *que)
{
    if (isEmpty(que))
    {
        printf("Queue under flow, no elements to display.\n");
        return;
    }
    printf("The elements of the queue are, \n");
    int i = que->front;
    do
    {
        printf("%d ", que->container[i]);
        i = (i + 1) % que->size;
    } while (i != (que->rear+1) % que->size);
}