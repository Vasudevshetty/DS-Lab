/*Implement Priority Queue with static and dynamic memory allocation
mechanisms using array storage representation. (Represent Queue using
structure)*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*This is design 2 of the prioty queue where we manipulate the ENQUEUE operation of the regualr queue operations,
where we insert the element in order. The time is again linear O(n) but this is better when compared to desing1.*/

#define MAX_SIZE 100
typedef struct
{
    int data;
    int priority;
} Element;

Element *createElement(int data, int priority)
{
    Element *element = (Element *)malloc(sizeof(Element));
    if (!element)
    {
        printf("Memmory allocation failed.\n");
        exit(1);
    }
    element->data = data;
    element->priority = priority;
    return element;
}

// this is a descending type of priorty queue.
typedef struct
{
    Element elements[MAX_SIZE];
    // Element *elments; // if need dyanmically use this..
    // Element elements[MAX_SIZE]; (if need staticaly please implement this way.)
    int Front;
    int Rear;
    int Size;
} priorityQueue;

// macros for easier access.
#define ele que->elements
#define front que->Front
#define rear que->Rear
#define size que->Size

// utility function to create a priorty queue with initailsation in heap.
priorityQueue *createPriorityQueue()
{
    priorityQueue *que = (priorityQueue *)malloc(sizeof(priorityQueue));
    if (!que)
    {
        printf("Memmory allocation failed.\n");
        exit(1);
    }
    size = MAX_SIZE;
    /*this is dynamic memory allcoation.*/
    // size = sz > MAX_SIZE ? MAX_SIZE : sz;
    // ele = (Element *)malloc(sizeof(Element) * size);
    // if (!ele)
    // {
    //     printf("Memmory allocation failed.\n");
    //     free(que);
    //     exit(1);
    // }
    front = rear = -1;
    return que;
}

// support functions.
bool isEmpty(priorityQueue *que)
{
    return front == -1 && rear == -1;
}

bool isFull(priorityQueue *que)
{
    return rear == size - 1;
}

/*The functions dequeue, enqueue, peek front and rear accepts and returns the pointer of the element,
so unnessacary copying will be avoided. This is the significant way of achieving it. The element created in
the respective activation frames are passed as a reference avoiding copying of it and the element can be accessed in
the respective functions.*/

void enqueue(priorityQueue *que, Element *element)
{
    if (isFull(que))
    {
        printf("Queue overflow, enqueuing failed.\n");
        return;
    }
    if (isEmpty(que))
    {
        front = rear = 0;
        ele[rear] = *element;
        return;
    }
    else
        rear++;
    int idx = rear;
    // since this a descending queue, the lowest prioirty task wil be enqueued at front.
    while (idx > front && ele[idx - 1].priority < element->priority)
    {
        ele[idx] = ele[idx - 1];
        idx--;
    }
    ele[idx] = *element;
}

Element *dequeue(priorityQueue *que)
{
    if (isEmpty(que))
    {
        printf("Queue underflow, dequeuing failed.\n");
        return NULL;
    }
    Element *element = &ele[front];
    if (front == rear)
        front = rear = -1;
    else
        front++;
    return element;
}

Element *peekFront(priorityQueue *que)
{
    return isEmpty(que) ? NULL : &ele[front];
}

Element *peekRear(priorityQueue *que)
{
    return isEmpty(que) ? NULL : &ele[rear];
}

void display(priorityQueue *que)
{
    if (isEmpty(que))
    {
        printf("Queue under flow, no elements to display.\n");
        return;
    }
    printf("Elements of the queue are, \n");
    for (int i = front; i <= rear; i++)
    {
        printf("Element => data : %d\tpriority : %d\t\n", ele[i].data, ele[i].priority);
    }
}

// drive code.
int main()
{
    priorityQueue *que = createPriorityQueue();
    int data, priority;
    int choice;

    do
    {
        printf("Menu.\n1. Enqueue.\n2. Dequeue.\n3. Front.\n4. Rear\n5. Display\n6. Exit\n\n");
        printf("Enter choice : ");
        scanf("%d", &choice);
        Element *element;
        switch (choice)
        {
        case 1:
            printf("Enter data and priority : ");
            scanf("%d %d", &data, &priority);
            element = createElement(data, priority);
            enqueue(que, element);
            display(que);
            break;
        case 2:
            element = dequeue(que);
            if(element) printf("The dequeued element's data is %d and priority is %d\n", element->data, element->priority);
            display(que);
            break;
        case 3:
            element = peekFront(que);
            !element ? printf("Queue underflow, no elements to peek.\n")
             : printf("The front element's data is %d and priority is %d\n", element->data, element->priority);
            break;
        case 4:
            element = peekRear(que);
            !element ? printf("Queue underflow, no elements to peek.\n")
             : printf("The rear element's data is %d and priority is %d\n", element->data, element->priority);
            break;
        case 5:
            display(que);
            break;
        case 6:
            printf("Exiting...\n");
            break;
        default:
            printf("Enter valid choice only, please try again.\n");
        }
        printf("\n\n");
    } while (choice != 6);
    free(ele);
    free(que);
    return 0;
}