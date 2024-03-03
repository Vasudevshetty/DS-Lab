/*. Develop a menu driven program to convert infix expression to postfix expression using
stack and evaluate the postfix expression. (Test for nested parenthesized expressions)
Note: Define Stack structure and implement the operations. Use different stacks for
conversion and evaluation*/

#include <stdio.h>
#include <stdlib.h>

// this header is to use bool for the functions (that return true or false.)
#include <stdbool.h>
// this header is to use string functions in conversion and evaulation.
#include <string.h>

/*Since they have specifically mentioned to use stack structures for operation(conversion and evaulation).
We create a integer type of stack, and operations (push and pop) for it.

----- PLEASE NOTE THIS POINT CAREFULLY..-------

For conversion, usually character type of stack is used, since we don't change any characters in the expression string,
we can make use of the created integer stack itself. (Ascii values of the characters get stored.)

OR ELSE, we have to create two types of stack, one for character type(CONVERSION fn) and one for integer type(EVAULATION fn).
Remembering the above fact, can make u use a single stack for both the operations i.e integer type.
*/

// STACK STURCUTRE.
/*The stack created is of type integer and i prefer doing it using dynamic memory allocation(malloc) for stackArray, one
can even prefer taking it linkedlist type or static type.*/
struct Stack
{
    int *stackArray; // the array (container) for the stack.
    int top;         // the top pointer to manipulate the stack.
};

// define the size of the stack, since for these kind of operations we will keep it 100 as default.
#define SIZE 100

// typedefine the stack, to avoid repaeting struct prefix everywhere, which looks clumsy.
typedef struct Stack Stack;

// function to create and initalisation of the stack,
Stack *createStack()
{
    // allocate memory dynamiclaly to the stack sturcture and check its allocaiton
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    if (stack == NULL)
    {
        printf("Memory allcoation failed.\n");
        exit(1);
    }

    // allocate memory dynamiclaly to the stackArray of the structure and check its allocaiton
    stack->stackArray = (int *)malloc(sizeof(int) * SIZE);
    if (stack->stackArray == NULL)
    {
        printf("Memory allcoation failed.\n");
        exit(1);
    }
    stack->top = -1;
    return stack;
}

/*lets create checkers (Stack's state checking functions.)
bool makes the code readable, it is also a datatype that can store only two values true or false.
Created these type of functions to avoid errors in push and pop, and make the code readable.*/

// 1. Stack Under Flow condition (isEmpty condition).
bool isEmpty(Stack *stack)
{
    return stack->top == -1; // returns true if the stack is empty or false.
}

// 2. Stack Over flow condition (isFull condition)
bool isFull(Stack *stack)
{
    return stack->top == SIZE - 1; // this the condition when our stack array is overflowing. (top cannot be incremented.)
}

// operations on stack.

// 1. push
void push(Stack *stack, int value)
{
    if (isFull(stack))
    { // checking whether there is space in the stack's array.
        printf("Stack overflow, cannot push value to the stack.\n");
        return;
    }
    stack->stackArray[++stack->top] = value;
}

// 2. pop
int pop(Stack *stack)
{
    if (isEmpty(stack))
    {
        printf("Stack underflow, cannot pop value from the stack.");
        return -1;
    }

    // this also can be written directly as return stack->stackArray[stack->top--];

    int data = stack->stackArray[stack->top]; // caputre the data.
    stack->top--;                             // decrement top.
    return data;
}

// 3. peek (stackTop() fucntion)
int peek(Stack* stack){
    if(isEmpty(stack))
        return -1;
    else
        return stack->stackArray[stack->top];
}

/*
------------------------------ CONVERSION AND EVALUATION FUCNTIONS-------------------------------------------
*/

