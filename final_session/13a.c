/* Develop a menu driven program to implement the following types of Queues by allocatingmemory dynamically.
i) Circular Queue
Note: Define Queue structure and implement the operation with array representation*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Queue
{
    int *items;
    int front, rear;
    int size;
} Queue;

Queue *initQueue(int size)
{
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    if (!queue)
    {
        printf("Memmorry allocation failed.\n");
        exit(1);
    }
    queue->size = size;
    queue->items = (int *)malloc(sizeof(int) * queue->size);
    if (!queue->items)
    {
        printf("Memmorry allocation failed.\n");
        free(queue);
        exit(1);
    }
    queue->front = queue->rear = -1;
    return queue;
}

bool isEmpty(const Queue *queue)
{
    return queue->front == -1 && queue->rear == -1;
}

bool isFull(const Queue *queue)
{
    return (queue->front == (queue->rear + 1) % queue->size);
}

void enqueue(Queue *queue, int data)
{
    if (isFull(queue))
    {
        printf("Queue overflow, enqueuing failed.\n");
        return;
    }
    if (isEmpty(queue))
        queue->front = queue->rear = 0;
    else
        queue->rear = (queue->rear + 1) % queue->size;

    queue->items[queue->rear] = data;
}

int dequeue(Queue *queue)
{
    if (isEmpty(queue))
    {
        printf("Queue underflow, dequeuing failed.\n");
        return -1;
    }
    int data = queue->items[queue->front];
    if (queue->front == queue->rear)
        queue->front = queue->rear = -1;
    else
        queue->front = (queue->front + 1) % queue->size;
    return data;
}

int front(const Queue *queue)
{
    return isEmpty(queue) ? -1 : queue->items[queue->front];
}

int rear(const Queue *queue)
{
    return isEmpty(queue) ? -1 : queue->items[queue->rear];
}

void display(const Queue *queue)
{
    if (isEmpty(queue))
    {
        printf("Queue under flow, display failed.\n");
        return;
    }
    printf("The elements of the queue is\n");
    int i = queue->front;
    while (i != queue->rear)
    {
        printf("%d ", queue->items[i]);
        i = (i + 1) % queue->size;
    }
    printf("%d\n", queue->items[i]);
}

int main()
{
    int size;
    printf("Enter size of the queue : ");
    scanf("%d", &size);
    Queue *queue = initQueue(size);

    int data, choice;

    do
    {
        printf("\nMenu\n1. Enqueue\n2. Dequeue\n3. Front\n4. Rear\n5. Display\n6. Exit\n");
        printf("Enter choice : ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter data : ");
            scanf("%d", &data);
            enqueue(queue, data);
            display(queue);
            break;
        case 2:
            data = dequeue(queue);
            printf("The data popped out is %d\n", data);
            display(queue);
            break;
        case 3:
            data = front(queue);
            if (data != -1)
                printf("The front data is %d\n", data);
            else
                printf("The queue is empty.\n");
            break;
        case 4:
            data = rear(queue);
            if (data != -1)
                printf("The rear data is %d\n", data);
            else
                printf("The queue is empty\n");
            break;
        case 5:
            display(queue);
            break;
        case 6:
            printf("Exiting...\n");
            break;
        default:
            printf("Invlaid choice, please try again.\n");
            break;
        }
    } while (choice != 6);
    free(queue->items);
    free(queue);
    return 0;
}