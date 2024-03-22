/*12. Develop a menu driven program to implement the following types of Queues by allocatingmemory dynamically.
Double ended Queue
Note: Define Queue structure and implement the operation with array representation*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Dequeue
{
    int *items;
    int front, rear;
    int size;
} Dequeue;

Dequeue *initQueue(int size)
{
    Dequeue *queue = (Dequeue *)malloc(sizeof(Dequeue));
    if (!queue)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    queue->size = size;
    queue->items = (int *)malloc(sizeof(int) * queue->size);
    if (!queue->items)
    {
        printf("Memory allocation failed.\n");
        free(queue);
        exit(1);
    }
    queue->front = queue->rear = -1;
    return queue;
}

bool isEmpty(const Dequeue *queue)
{
    return queue->front == -1 && queue->rear == -1;
}

bool isFull(const Dequeue *queue)
{
    return queue->rear == queue->size - 1;
}

void display(const Dequeue *queue)
{
    if (isEmpty(queue))
    {
        printf("Queue underflow, display failed.\n");
        return;
    }
    printf("The elements of the dequeu is \n");
    for (int i = queue->front; i <= queue->rear; i++)
        printf("%d ", queue->items[i]);
    printf("\n");
}
void enqueue_front(Dequeue *queue, int data)
{
    if(isFull(queue)){
        printf("Queue overflow, enqueueing failed.\n");
        return;
    }
    if(isEmpty(queue))
        queue->front = queue->rear = 0;
    else if(queue->front > 0)
        queue->front--;
    else{
        queue->rear++;
        for (int i = queue->rear; i >= queue->front; i--)
            queue->items[i] = queue->items[i - 1];
    }
    queue->items[queue->front] = data;
}

void enqueue_rear(Dequeue *queue, int data)
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

int dequeue_front(Dequeue *queue)
{
    if (isEmpty(queue))
    {
        printf("Queue underflow, dequein failed.\n");
        return -1;
    }
    int data = queue->items[queue->front];
    if (queue->front == queue->rear)
        queue->front = queue->rear = -1;
    else
        queue->front++;
    return data;
}

int dequeue_rear(Dequeue *queue)
{
    if (isEmpty(queue))
    {
        printf("Queue underflow, dequein failed.\n");
        return -1;
    }
    int data = queue->items[queue->rear];
    if(queue->front == queue->rear)
        queue->front = queue->rear = -1;
    else
        queue->rear--;
    return data;
}

int front(const Dequeue *queue)
{
    return isEmpty(queue) ? -1 : queue->items[queue->front];
}

int rear(const Dequeue *queue)
{
    return isEmpty(queue) ? -1 : queue->items[queue->rear];
}

int main()
{
    int size;
    printf("Enter size of the queue : ");
    scanf("%d", &size);
    Dequeue *queue = initQueue(size);

    int data, choice;

    do
    {
        printf("\nMenu\n1. Enqueue front\n2. Enqueue rear\n3. Dequeue front\n4. Dequeue rear\n");
        printf("5. Front\n6. Rear\n7. Display\n8. Exit\n");
        printf("Enter choice : ");
        scanf("%d", &choice);
        printf("\n");

        switch (choice)
        {
        case 1:
            printf("Enter data : ");
            scanf("%d", &data);
            enqueue_front(queue, data);
            display(queue);
            break;
        case 2:
            printf("Enter data : ");
            scanf("%d", &data);
            enqueue_rear(queue, data);
            display(queue);
            break;
        case 3:
            data = dequeue_front(queue);
            printf("The data popped out is %d\n", data);
            display(queue);
            break;
        case 4:
            data = dequeue_rear(queue);
            printf("The data popped out is %d\n", data);
            display(queue);
            break;
        case 5:
            data = front(queue);
            if (data != -1)
                printf("The front data is %d\n", data);
            else
                printf("The queue is empty.\n");
            break;
        case 6:
            data = rear(queue);
            if (data != -1)
                printf("The rear data is %d\n", data);
            else
                printf("The queue is empty\n");
            break;
        case 7:
            display(queue);
            break;
        case 8:
            printf("Exiting...\n");
            break;
        default:
            printf("Invlaid choice, please try again.\n");
            break;
        }
    } while (choice != 8);
    free(queue->items);
    free(queue);
    return 0;
}