/*Implement ordinary Queue with static and dynamic memory allocation
mechanisms using array storage representation.(Represent Queue using structure)*/

#include <stdio.h>
#include <stdlib.h>

#define max_size 100

// structure to store queue members.
struct queue
{
    int *container; // array to store the elements.
    int front;      // pointer to manipulate from the front of the queue.
    int rear;       // pointer to manipulate from the rear of the queue.
    int size;       // variable to store the size of the container.
};

// functions to allcoate memeory.
void createStaticQueue(struct queue *q);
void createDynamicQueue(struct queue *q, int size);

// condtions.
int isEmpty(struct queue q);
int isFull(struct queue q);

// operations.
void enqueue(struct queue *q, int data);
int dequeue(struct queue *q);
int front(struct queue q);
int rear(struct queue q);

// display function
void display(struct queue q);

int main()
{
    int data, choice, size;
    struct queue q;
    q.container = NULL;

    printf("Enter mode of allocation.\n1. Static\n2. Dynamic\n");
    printf("Enter the choice: ");
    scanf("%d", &choice);

    if (choice == 1)
    {
        createStaticQueue(&q);
    }
    else if (choice == 2)
    {
        printf("Enter the size of the queue: ");
        scanf("%d", &size);
        createDynamicQueue(&q, size);
    }
    else
    {
        printf("Invalid choice. Retry...\n");
        main();
    }

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
            enqueue(&q, data);
            break;
        case 2:
            data = dequeue(&q);
            if (data != -1)
                printf("The dequeued data is %d\n", data);
            break;
        case 3:
            if(front(q) != -1)
            printf("The front of the data is %d\n", front(q));
            break;
        case 4:
            if(rear(q) != -1)
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

    free(q.container);
    return 0;
}

// function to create static memory allcoated queue.
/*The memory is allocateed at the compile time itslef though it is allocated at heap.*/
void createStaticQueue(struct queue *q)
{
    q->container = (int *)malloc(max_size * sizeof(int));
    if (!q->container)
    {
        printf("Memory allcoation failed.\n");
        return;
    }
    q->front = -1;
    q->rear = -1;
    q->size = max_size;
}

// function to create dynamic memory allocated queue.
/*Since dynamic memory for the array is allocated at run time upon reciveing input from the user.*/
void createDynamicQueue(struct queue *q, int size)
{
    q->container = (int *)malloc(size * sizeof(int));
    if (!q->container)
    {
        printf("Memory allocation failed.\n");
        return;
    }
    q->front = -1;
    q->rear = -1;
    q->size = size;
}

// function to check whether the queue is empty.
int isEmpty(struct queue q)
{
    return q.front == -1 && q.rear == -1;
}

// function to check whetehr the queue is full.
int isFull(struct queue q)
{
    return q.rear == q.size - 1;
}

// operations
// function to enqueu into the queue
void enqueue(struct queue *q, int data)
{
    // check whether the queue is full, if full cannot enqueue
    if (isFull(*q))
    {
        printf("Queue is full, enqueue failed.\n");
        return;
    }
    else if (isEmpty(*q))
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
    if (isEmpty(*q))
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
int front(struct queue q)
{
    // check whether the queue is empty before accessing.
    if (isEmpty(q))
    {
        printf("Queue is empty, No front element.\n");
        return -1;
    }

    return q.container[q.front];
}

int rear(struct queue q)
{
    // check whether the queue is empty before accessing.
    if (isEmpty(q))
    {
        printf("Queue is empty, No rear element.\n");
        return -1;
    }

    return q.container[q.rear];
}

// function to display the queue contenets.
void display(struct queue q){
    // check whetehr if it is empty.
    if(isEmpty(q)){
        printf("Queue is empty, no elements to display.\n");
        return;
    }

    printf("Queue elements : ");
    for(int i = q.front; i <= q.rear; i++){
        printf("%d ", q.container[i]);
    }
    printf("\n");
}