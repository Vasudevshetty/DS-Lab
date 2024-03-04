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
int peek(Stack *stack)
{
    if (isEmpty(stack))
        return -1;
    else
        return stack->stackArray[stack->top];
}

/*
------------------------------ CONVERSION AND EVALUATION FUCNTIONS-------------------------------------------
*/

// suport functions.
/*1 to check whether the given token is operand. again bool is a datatype that returns only true or false.
usually we keep these functions int,  the function returns integer values, where 0 corresponds to false, and other than
zero is considered as true. so instead of that delimma use bool (shift towards OOPS (java or c++))
*/
bool isOperand(char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
}

// 2. precedence function.
int precedence(char c)
{
    if (c == '^' || c == '%')
        return 3;
    else if (c == '*' || c == '/')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
        return 0;
}

// lets keep the infix to postfix convert function to return the postifx covnerted string, (char array).
char *infixToPostfix(char *infix)
{
    // lets obtain the length of the string from string functions instead of sending one in the function.
    int i = 0, len = strlen(infix);
    char *postfix = (char *)malloc(sizeof(char) * len);
    int j = 0;

    // create the stack .
    Stack *stack = createStack();

    while (i < len)
    {
        char token = infix[i]; // capture the token

        if (isOperand(token)) // if token append to postfix string directly
            postfix[j++] = token;
        else if (token == '(') // if operning parenthisis push to stack.
            push(stack, token);
        else if (token == ')')
        {
            // if closing parenthis, empty out the stack until you find the operning parethisis(previoudly pushed)
            while (!isEmpty(stack) && peek(stack) == '(')
                postfix[j++] = pop(stack);
            pop(stack); // and then pop the opening parenthisis too.
        }
        else
        {
            /* else if it is a operator, push the operator if the operator is of higher precedence else,
            empty out the stack utnil you find the exact position int he stack where the oeprator gets fitted.*/
            while (!isEmpty(stack) && precedence(token) <= precedence(peek(stack)))
                postfix[j++] = pop(stack);
            push(stack, token);
        }
        i++; // increment the infix string pointer.
    }

    // empty out the stack.
    while (!isEmpty(stack))
        postfix[j++] = pop(stack);

    postfix[j] = '\0';

    return postfix;
}

// support fucntion for evaulate function.
bool isOperator(char c)
{
    return c == '*' || c == '-' || c == '+' || c == '/' || c == '^' || c == '$';
}

int evulatePostfix(char *postfix)
{
    int i = 0, len = strlen(postfix);
    Stack *stack = createStack();

    while (i < len)
    {
        char token = postfix[i];
        if (isOperand(token))
            push(stack, token - '0');
        else if (isOperator(token))
        {
            int operand2 = pop(stack);
            int operand1 = pop(stack);
            int result;

            switch (token)
            {
            case '+':
                result = operand1 + operand2;
                break;
            case '-':
                result = operand1 - operand2;
                break;
            case '*':
                result = operand1 * operand2;
                break;
            case '/':
                result = operand1 / operand2;
                break;
            // this case is merged coz both does the same case.
            case '%':
            case '$':
                result = pow(operand2, operand1);
                break;
            }

            // push the result later.
            push(stack, result);
        }
        i++;
    }
    return pop(stack);
}

int main()
{
    char infix[100], *postfix;
    scanf("%s", infix);
    postfix = infixToPostfix(infix);
    printf("%s", postfix);
    return 0;
}