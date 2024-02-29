/*Implement Priority Queue with static and dynamic memory allocation
mechanisms using array storage representation. (Represent Queue using
structure)*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*This is desing 1 of the prioty queue where we manipulate the DEQUEUE operation of the regualr queue operations,
where we search for the highest priority element and dequeue it, The time it takes for this operation is nearly linear time.
O(n). (can be upgraded to O(logn) by using binary heap or heapify.).
Desing 2 will be added in one more subdivision.*/


#define MAX_SIZE 100
typedef struct
{
    int data;
    int priority;
} Element;

// default value to return when we won't find any element.
Element defaultElement = {0, 0};


// this is a asceding type of priorty queue.
typedef struct
{
    Element elements[MAX_SIZE];
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
    /*This is for dynamic memory allcoation nothign to change.*/
    // size = sz > MAX_SIZE ? MAX_SIZE : sz;
    // ele = (Element *)malloc(sizeof(Element) * size);
    // if (!ele)
    // {
    //     printf("Memmory allocation failed.\n");
    //     free(que);
    //     exit(1);
    // }
    size = MAX_SIZE;
    front = rear = -1;
    return que;
}

//support functions.
bool isEmpty(priorityQueue *que)
{
    return front == -1;
}

bool isFull(priorityQueue *que)
{
    return rear == size - 1;
}

/*The functions dequeue, enqueue, peek front and rear accepts and returns the copy of the element, 
this is also a way, which is not the optimised as we pass as a pointer, since element is a  samll structure, copying indeeed
is easier. The other way passing and accepting element as pointer will be demonstrated on the dynamic implmentation of the 
priority queue in the next subdivision. */


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
    // find the min of the priority (i.e highest priority)
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

//drive code.
int main(){
    priorityQueue *que = createPriorityQueue();
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
    free(que);
    return 0;
}