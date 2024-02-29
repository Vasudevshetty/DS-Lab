#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

// enum to find out the notation.
typedef enum Notation
{
    prefix,
    postfix,
} Notation;

typedef struct Node
{
    int data;
    struct Node *next;
} node;

typedef struct
{
    node *Top;
    int Count;
} Stack;

#define top stack->Top
#define count stack->Count

node *createNode(int data)
{
    node *newNode = (node *)malloc(sizeof(node));
    if (!newNode)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

Stack *initStack()
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    if (!stack)
    {
        printf("Memory allcation failed.\n");
        exit(1);
    }
    top = NULL;
    count = 0;
    return stack;
}

bool isEmpty(const Stack *stack)
{
    return !(top && count);
}

void push(Stack *stack, int data)
{
    node *newNode = createNode(data);
    if (isEmpty(stack))
        top = newNode;
    else
    {
        newNode->next = top;
        top = newNode;
    }
    count++;
}

int pop(Stack *stack)
{
    if (isEmpty(stack))
    {
        printf("Stack empty to pop.\n");
        return -1;
    }
    node *toDelete = top;
    int data = toDelete->data;
    top = toDelete->next;
    count--;
    return data;
}

int peek(const Stack *stack)
{
    return isEmpty(stack) ? -1 : top->data;
}
// the above is the stack implementation using linkedlist.

// the support fnction to calcuate the value of teh oeprations of operands speciefed,
int calculate(char operator, int operand1, int operand2)
{
    switch (operator)
    {
    case '+':
        return operand1 + operand2;
    case '-':
        return operand1 - operand2;
    case '*':
        return operand1 * operand2;
    case '/':
        return operand1 / operand2;
    }
    return -1;
}

bool isOperator(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// the function to evalute the expression based on the noatation the expression is followed, used dry principle to finish everything
// in a single function.
int evualate(const char *expression, Notation notation)
{
    Stack *stack = initStack();
    int i = 0, len = strlen(expression);
    while(i < len){
        char token = notation == prefix ? expression[len - i - 1] : expression[i];
        if(isalnum(token))
            push(stack, token - '0');
        else if(isOperator(token)){
            int operand1 = pop(stack);
            int operand2 = pop(stack);

            int result = notation == prefix ? calculate(token, operand1, operand2) : calculate(token, operand2, operand1);
            push(stack, result);
        }
        i++;
    }
    return pop(stack);
}

// driver code.
int main()
{
    char expression[100];
    int choice, result;
    char notation[10];
    printf("Enter the expression to calcualte : ");
    scanf("%s", expression);
    printf("Please enter the type of notation used in the expression : ");
    scanf("%s", notation);
    if(strcmp(notation, "prefix") == 0)
        result = evualate(expression, prefix);
    else if(strcmp(notation, "postfix") == 0)
        result = evualate(expression, postfix);
    else {
        printf("Please specify the correct type of notation (prefix or postfix).\n");
        main();
    }
    printf("The calcualted result of the expression is %d\n", result);
    printf("\n1. Try again\t 2. Exit.\n");
    printf("Enter choice: ");
    scanf("%d", &choice);
    printf("\n\n");
    if(choice == 1)
        main();
    else
        printf("Exiting....\n");
    return 0;
}