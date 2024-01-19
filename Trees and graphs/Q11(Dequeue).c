/*Implement Double Ended Queue with static and dynamic memory allocation 
mechanisms using array storage representation. (Represent Queue using 
structure)*/

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
} deque;

// function to allocate memory.
deque *initDeque(int size);

// operations
void enqueueFront(deque *q, int data);
void enqueueRear(deque *q, int data);
int dequeueFront(deque *q);
int dequeueRear(deque *q);
int front(deque *q);
int rear(deque *q);

// supporting functions
void display(deque *q);
int isEmpty(deque *q);
int isFull(deque *q);

int main()
{
    int data, choice;
    int size;
    deque *q;
    printf("Enter the size of the queue : ");
    scanf("%u", &size);
    if (size < max_size)
        q = initDeque(size);

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

