/* Develop a menu driven program to implement the following types of PriorityQueues by allocatingmemory dynamically.
i) Priority PriorityQueue
Note: Define PriorityQueue structure and implement the operation with array representation*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct PriorityQueue
{
    int *items;
    int front, rear;
    int size;
} PriorityQueue;

PriorityQueue *initPriorityQueue(int size)
{
    PriorityQueue *queue = (PriorityQueue *)malloc(sizeof(PriorityQueue));
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

bool isEmpty(const PriorityQueue *queue)
{
    return queue->front == -1 && queue->rear == -1;
}

bool isFull(const PriorityQueue *queue)
{
    return (queue->front == (queue->rear + 1) % queue->size);
}

void enqueue(PriorityQueue *queue, int data)
{
    if (isFull(queue))
    {
        printf("PriorityQueue overflow, enqueuing failed.\n");
        return;
    }
    if (isEmpty(queue))
    {
        queue->front = queue->rear = 0;
        queue->items[queue->rear] = data;
    }
    else
    {
        queue->rear++;
        int idx = queue->rear;

        while(idx > queue->front && queue->items[idx - 1] > data){
            queue->items[idx] = queue->items[idx - 1];
            idx--;
        }

        queue->items[idx] = data;
    }
}

int dequeue(PriorityQueue *queue)
{
    if (isEmpty(queue))
    {
        printf("PriorityQueue underflow, dequeuing failed.\n");
        return -1;
    }
    int data = queue->items[queue->front];
    if (queue->front == queue->rear)
        queue->front = queue->rear = -1;
    else
        queue->front++;
    return data;
}

int front(const PriorityQueue *queue)
{
    return isEmpty(queue) ? -1 : queue->items[queue->front];
}

int rear(const PriorityQueue *queue)
{
    return isEmpty(queue) ? -1 : queue->items[queue->rear];
}

void display(const PriorityQueue *queue)
{
    if (isEmpty(queue))
    {
        printf("PriorityQueue under flow, display failed.\n");
        return;
    }
    printf("The elements of the queue is\n");
    for (int i = queue->front; i <= queue->rear; i++)
        printf("%d ", queue->items[i]);
    printf("\n");
}

int main()
{
    int size;
    printf("Enter size of the queue : ");
    scanf("%d", &size);
    PriorityQueue *queue = initPriorityQueue(size);

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