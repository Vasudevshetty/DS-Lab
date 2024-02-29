/*Implement ordinary Queue with static and dynamic memory allocation
mechanisms using array storage representation.(Represent Queue using structure)*/

#include <stdio.h>
#include <stdlib.h>

#define max_size 100

// structure to store queue members.
struct queue
{
    int container[max_size]; // array to store the elements.
    int front;               // pointer to manipulate from the front of the queue.
    int rear;                // pointer to manipulate from the rear of the queue.
    int size;                // variable to store the size of the container.
};

// functions to allcoate memeory.
struct queue *createStaticQueue();

// condtions.
int isEmpty(const struct queue *);
int isFull(const struct queue *);

// operations.
void enqueue(struct queue *, int);
int dequeue(struct queue *);
int front(const struct queue *);
int rear(const struct queue *);

// display function
void display(const struct queue *);

int main()
{
    int data, choice;
    struct queue *q = createStaticQueue();

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

    return 0;
}

// function to create static memory allcoated queue.
/*The memory is allocateed at the compile time itslef though it is allocated at heap.*/
struct queue *createStaticQueue()
{
    struct queue *q = (struct queue *)malloc(sizeof(struct queue));
    if (!q)
    {
        printf("Memory allcoatin failed.\n");
        exit(1);
    }
    q->front = -1;
    q->rear = -1;
    q->size = max_size;
    return q;
}

// function to check whether the queue is empty.
int isEmpty(const struct queue *q)
{
    return q->front == -1 && q->rear == -1;
}

// function to check whetehr the queue is full.
int isFull(const struct queue *q)
{
    return q->rear == q->size - 1;
}

// operations
// function to enqueu into the queue
void enqueue(struct queue *q, int data)
{
    // check whether the queue is full, if full cannot enqueue
    if (isFull(q))
    {
        printf("Queue is full, enqueue failed.\n");
        return;
    }
    else if (isEmpty(q))
    {
        // if suppose it is the first element to enqueue intailise front
        q->front = 0;
    }

    // increment the rear first and add to the queue.
    q->rear = q->rear + 1;
    q->container[q->rear] = data;
    // printf("Data enqueued.\n"); // if necessary add this statement
}

// function to dequeue from the queue
int dequeue(struct queue *q)
{
    // check whether the queue is empty.
    if (isEmpty(q))
    {
        printf("Queue is empty, dequeue failed.\n");
        return -1;
    }

    int data = q->container[q->front];

    // check suppose if it is the last element of the queue
    if (q->front == q->rear)
    {
        // reset the front and rear pointers
        q->front = q->rear = -1;
    }
    else
    {
        q->front = q->front + 1;
        // move the front the element is dequeued.
    }

    // printf("Dequeued data is %d", data); // if required add it

    return data;
}

// support function returning front and rear values
int front(const struct queue *q)
{
    // check whether the queue is empty before accessing.
    if (isEmpty(q))
    {
        printf("Queue is empty, No front element.\n");
        return -1;
    }

    return q->container[q->front];
}

int rear(const struct queue *q)
{
    // check whether the queue is empty before accessing.
    if (isEmpty(q))
    {
        printf("Queue is empty, No rear element.\n");
        return -1;
    }

    return q->container[q->rear];
}

// function to display the queue contenets.
void display(const struct queue *q)
{
    // check whetehr if it is empty.
    if (isEmpty(q))
    {
        printf("Queue is empty, no elements to display.\n");
        return;
    }

    printf("Queue elements : ");
    for (int i = q->front; i <= q->rear; i++)
    {
        printf("%d ", q->container[i]);
    }
    printf("\n");
}