/*Develop a menu driven program to implement the following types of Queues by allocating
memory dynamically.
i) Circular Queue ii) Double ended Queue
Note: Define Queue structure and implement the operation*/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define MAX_SIZE 100
typedef struct Dequeue{
    int *items;
    int front, rear;
} Dequeue;

Dequeue* initDequeue(){
    Dequeue *que = (Dequeue *)malloc(sizeof(Dequeue));
    if(!que){
        printf("Memory allocation failed.\n");
        exit(1);
    }
    que->items = (int *)malloc(sizeof(int) * MAX_SIZE);
    que->front = que->rear = -1;
    return que;
}

bool isEmpty(Dequeue* que){
    return que->front == -1 && que->rear == -1;
}

void enqueue_front(Dequeue* que, int value){

}