#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define MAX 100

typedef struct Stack{
    int *items;
    int top;
} Stack;

Stack* initStack(){
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    if(!stack){
        printf("Memory allcoation failed.\n");
        exit(1);
    }
    stack->items = (int *)malloc(sizeof(int) * MAX);
    if(!stack->items){
        printf("Memory allcoation failed.\n");
        free(stack);
        exit(1);
    }
    stack->top = -1;
    return stack;
}

bool isEmpty(const Stack* stack){
    return stack->top == -1;
}

bool isFull(const Stack* stack){
    return stack->top == MAX - 1;
}

void push(Stack* stack, int data){
    if(isFull(stack)){
        printf("Stack full, cannot push.\n");
        return;
    }
    stack->items[++(stack->top)] = data;
}

int pop(Stack* stack){
    if(isEmpty(stack)){
        printf("Emtpy stack, cannot pop.\n");
        return -1;
    }

    int data = stack->items[stack->top];
    stack->top--;
    return data;
}

int peek(const Stack* stack){
    return isEmpty(stack) ? -1 : stack->items[stack->top];
}

void display(const Stack* stack){
    if(isEmpty(stack)){
        printf("Empty stack, cannot display.\n");
        return;
    }

    printf("The elements of the stack are,\n");
    for(int i = stack->top; i >= 0; i--)
        printf("%d ", stack->items[i]);
    printf("\n");
}

