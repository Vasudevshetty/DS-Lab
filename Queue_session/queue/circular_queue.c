/*Implement Circular Queue with static and dynamic memory allocation
mechanisms using array storage representation.(Represent circularQueue using structure)
*/

#include <stdio.h>
#include <stdlib.h>

#define max_size 100

// create a circular queue struct
typedef struct
{
    int *container; // to store the values.
    int front;      // pointer to manipulate from front.
    int rear;       // pointer to manipulate from rear.
    int size;       // variable size.
} circularQueue;

// function to allocate memory.
circularQueue *initCircularQueue(int size);

// operations
void enqueue(circularQueue *q, int data);
int dequeue(circularQueue *q);
int front(circularQueue *q);
int rear(circularQueue *q);

// supporting functions
void display(circularQueue *q);
int isEmpty(circularQueue *q)
{
    return q->front == -1 && q->rear == -1;
}
int isFull(circularQueue *q)
{
    return (q->front == (q->rear + 1) % q->size);
}

int main()
{
    int data, choice;
    int size;
    circularQueue *q;
    printf("Enter the size of the queue : ");
    scanf("%u", &size);
    if (size < max_size)
        q = initCircularQueue(size);

    do
    {
        printf("\n\n");
        printf("Menu\n");
        printf("1. Enqueue(push).\n");
        printf("2. Dequeue(pop). \n");
        printf("3. Front(peek).\n");
        printf("4. Rear(peek).\n");
        printf("5. Display\n");
        printf("6. Exit.\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter the data to enqueue: ");
            scanf("%d", &data);
            enqueue(q, data);
            display(q);
            break;
        case 2:
            data = dequeue(q);
            if (data != -1)
                printf("The dequeued data is %d\n", data);
            display(q);
            break;
        case 3:
            if (front(q) != -1)
                printf("The front of the data is %d\n", front(q));
            break;
        case 4:
            if (rear(q) != -1)
                printf("The rear of the data is %d\n", rear(q));
            break;
        case 5:
            display(q);
            break;
        case 6:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice. Try again.\n");
            break;
        }
    } while (choice != 6);

    free(q->container);
    free(q);

    return 0;
}

// function defination
circularQueue *initCircularQueue(int size)
{
    circularQueue *queue = (circularQueue *)malloc(sizeof(circularQueue));
    if (!queue)
    {
        printf("Memeory allocation failed.\n");
        exit(1);
    }
    queue->size = size;
    queue->container = (int *)calloc(queue->size, sizeof(int));
    if (!queue->container)
    {
        printf("Memeory allocation failed.\n");
        free(queue);
        exit(1);
    }

    queue->front = queue->rear = -1;
    return queue;
}

void enqueue(circularQueue *q, int data)
{
    if (isFull(q))
    {
        printf("Queue is full, enqueue failed.\n");
        return;
    }

    if (isEmpty(q))
        q->front = q->rear = 0;
    else
        q->rear = (q->rear + 1) % q->size;

    *(q->container + q->rear) = data;
}

int dequeue(circularQueue *q)
{
    if (isEmpty(q))
    {
        printf("Queue is empty, dequeue failed.\n");
        return -1;
    }

    int data = *(q->container + q->front);
    if (q->front == q->rear)
        q->front = q->rear = -1;
    else
        q->front = (q->front + 1) % q->size;

    return data;
}

int front(circularQueue *q)
{
    if (q->front != -1)
        return *(q->container + q->front);
    else
        return -1;
}
int rear(circularQueue *q)
{
    if (q->rear != -1)
        return *(q->container + q->rear);
    else
        return -1;
}

void display(circularQueue *q)
{
    if (isEmpty(q))
    {
        printf("Queue is empty, display failed.\n");
        return;
    }

    int i = q->front;
    printf("The elements of the circular queue are, \n");
    while (i != q->rear)
    {
        printf("%d ", *(q->container + i));
        i = (i + 1) % q->size;
    }
    printf("%d\n", *(q->container + q->rear));
}
