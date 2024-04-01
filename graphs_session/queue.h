#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100

typedef struct Queue
{
    int *items;
    int front, rear;
} Queue;

Queue *initQueue()
{
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    if (!queue)
    {
        printf("Memroy allocatin failed.\n");
        exit(1);
    }
    queue->items = (int *)malloc(sizeof(int) * MAX);
    if (!queue->items)
    {
        printf("Memroy allocatin failed.\n");
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
    return queue->rear == MAX - 1;
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
        queue->rear++;

    queue->items[queue->rear] = data;
}

int dequeue(Queue *queue)
{
    if (isEmpty(queue))
    {
        printf("Queue underlfow, dequeuing failed.\n");
        return -1;
    }
    int data = queue->items[queue->front];
    if (queue->front == queue->rear)
        queue->front = queue->rear = -1;
    else
        queue->front++;
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
        printf("Memory allocation failed.\n");
        return;
    }

    printf("The elements of the queue are, \n");
    for (int i = queue->front; i <= queue->rear; i++)
        printf("%d ", queue->items[i]);
    printf("\n");
}