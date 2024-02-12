#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// element type to be generic as possible.
typedef struct
{
    int data;
    int priority;
} Element;

// utiilty class to create a element
Element *createElement(int data, int priority)
{
    Element *element = (Element *)malloc(sizeof(Element));
    if (!element)
    {
        printf("Memory allocation failed.\n");
        return NULL;
    }
    element->data = data;
    element->priority = priority;
    return element;
}
typedef struct Node
{
    Element *element;
    struct Node *next;
} node;

node *createNode(Element *element)
{
    node *newNode = (node *)malloc(sizeof(node));
    if (!newNode)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    newNode->element = element;
    newNode->next = NULL;
    return newNode;
}
typedef struct
{
    node *Front;
    node *Rear;
    int Count;
} priorityQueue;

// macros fro front and rear of list.
#define front que->Front
#define rear que->Rear
#define count que->Count

// utility class to create a queue.
priorityQueue *createQueue()
{
    priorityQueue *que = (priorityQueue *)malloc(sizeof(priorityQueue));
    if (!que)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    front = rear = NULL;
    count = 0;
    return que;
}

bool isEmpty(priorityQueue *que)
{
    return !(front && rear && count);
}

void enqueue(priorityQueue *que, Element *element)
{
    node *newNode = createNode(element);
    if (isEmpty(que))
    {
        front = rear = newNode;
    }
    else
    {
        rear->next = newNode;
        rear = newNode;
    }
    count++;
}

node *highestPriorityElement(priorityQueue *que)
{
    node *minPriority = front;
    node *temp = front->next;
    while (temp)
    {
        minPriority = minPriority->element->priority < temp->element->priority ? minPriority : temp;
        temp = temp->next;
    }
    return minPriority;
}

/*The design 1 is to manipulate the dequeeu function that is you search the highest priorty element, and delete the element.*/
Element *dequeue(priorityQueue *que)
{
    if (isEmpty(que))
    {
        printf("Queue under flow, no elements to delete.\n");
        return NULL;
    }
    node *toDelete = highestPriorityElement(que);
    Element *element = toDelete->element;
    if (toDelete == front)
        front = front->next;
    else
    {
        node *temp = front;
        while (temp->next != toDelete && temp)
            temp = temp->next;
        temp->next = toDelete->next;
    }
    count--;
    free(toDelete);
    return element;
}

Element *peekFront(priorityQueue *que)
{
    return isEmpty(que) ? NULL : front->element;
}

Element *peekRear(priorityQueue *que)
{
    return isEmpty(que) ? NULL : rear->element;
}

void display(priorityQueue *que)
{
    if (isEmpty(que))
    {
        printf("Queue under flow, no elementst to display.\n");
        return;
    }
    node *temp = front;
    printf("The elements of the queue are, \n");
    while (temp)
    {
        printf("Element => data : %d\tpriority : %d\n", temp->element->data, temp->element->priority);
        temp = temp->next;
    }
}

void destructQueue(priorityQueue *que)
{
    if (!isEmpty(que))
    {
        node *temp = front;
        while (temp)
        {
            node *next = temp->next;
            free(temp->element);
            free(temp);
            temp = next;
        }
    }
    free(que);
}

// driver code.
int main()
{
    priorityQueue *que = createQueue();
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
            if (!element)
                break;
            printf("The dequeued element's data is %d and priority is %d\n", element->data, element->priority);
            free(element);
            display(que);
            break;
        case 3:
            element = peekFront(que);
            element ? printf("The front element's data is %d and priority is %d\n", element->data, element->priority) : printf("Qeueue under flow, cannot peek.\n");
            break;
        case 4:
            element = peekRear(que);
            element ? printf("The rear element's data is %d and priority is %d\n", element->data, element->priority) : printf("Qeueue under flow, cannot peek.\n");
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
    destructQueue(que);
    return 0;
}