/*Implement Priority Queue with static and dynamic memory allocation
mechanisms using array storage representation. (Represent Queue using
structure)*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 100
typedef struct
{
    int data;
    int priority;
} Element;

Element defaultElement = {0, 0};
typedef struct
{
    Element *elements;
    // Element elements[MAX_SIZE]; (if need staticaly please implement this way.)
    int Front;
    int Rear;
    int Size;
} priorityQueue;

#define ele que->elements
#define front que->Front
#define rear que->Rear
#define size que->Size

priorityQueue *createPriorityQueue(int sz)
{
    priorityQueue *que = (priorityQueue *)malloc(sizeof(priorityQueue));
    if (!que)
    {
        printf("Memmory allocation failed.\n");
        exit(1);
    }
    size = sz > MAX_SIZE ? MAX_SIZE : sz;
    ele = (Element *)malloc(sizeof(Element) * size);
    if (!ele)
    {
        printf("Memmory allocation failed.\n");
        free(que);
        exit(1);
    }
    front = rear = -1;
    return que;
}

bool isEmpty(priorityQueue *que)
{
    return front == -1;
}

bool isFull(priorityQueue *que)
{
    return rear == size - 1;
}

void enqueue(priorityQueue *que, Element element)
{
    if (isFull(que))
    {
        printf("Queue overflow, enqueuing failed.\n");
        return;
    }
    if (isEmpty(que))
        front = rear = 0;
    else
        rear++;
    ele[rear] = element;
}

Element dequeue(priorityQueue *que)
{
    if (isEmpty(que))
    {
        printf("Queue underflow, dequeuing failed.\n");
        return defaultElement;
    }
    int min = ele[front].priority;
    int idx = front;
    for (int i = front + 1; i <= rear; i++){
        if(ele[i].priority < min){
            min = ele[i].priority;
            idx = i;
        }
    }
    Element element = ele[idx];
    for (int i = idx; i <= rear - 1; i++)
        ele[i] = ele[i + 1];
    rear--;
    return element;
}

Element peekFront(priorityQueue* que){
    return isEmpty(que) ? defaultElement : ele[front];
}

Element peekRear(priorityQueue* que){
    return isEmpty(que) ? defaultElement : ele[rear];
}

void display(priorityQueue* que){
    if(isEmpty(que)){
        printf("Queue under flow, no elements to display.\n");
        return;
    }
    printf("Elements of the queue are, \n");
    for (int i = front; i <= rear; i++){
        printf("Element => data : %d\tpriority : %d\t\n", ele[i].data, ele[i].priority);
    }
}

int main(){
    int sz;
    printf("Enter size of the queue : ");
    scanf("%d", &sz);
    priorityQueue *que = createPriorityQueue(sz);
    int data, priority;
    int choice;

    do{
        printf("Menu.\n1. Enqueue.\n2. Dequeue.\n3. Front.\n4. Rear\n5. Display\n6. Exit\n\n");
        printf("Enter choice : ");
        scanf("%d", &choice);
        Element element;
        switch(choice){
            case 1:
                printf("Enter data and priority : ");
                scanf("%d %d", &data, &priority);
                element.data = data;
                element.priority = priority;
                enqueue(que, element);
                display(que);
                break;
            case 2:
                element = dequeue(que);
                printf("The dequeued element's data is %d and priority is %d\n", element.data, element.priority);
                display(que);
                break;
            case 3: 
                element = peekFront(que);
                printf("The front element's data is %d and priority is %d\n", element.data, element.priority);
                break;
            case 4: 
                element = peekRear(que);
                printf("The rear element's data is %d and priority is %d\n", element.data, element.priority);
                break;
            case 5 :
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