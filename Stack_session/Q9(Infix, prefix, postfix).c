/*
Convert infix expression to postfix expression.
Convert infix expression to prefix Evaluate the postfix expression*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max_size 100

// structure to create a stack with members.
struct stack
{
    char *container; // array to store elements(items)
    int top;         // the top pointer used to manipulate.
    int size;        // the size of the stack container.
};
// function to initalise stack container staticly
void createStaticStack(struct stack *s)
{
    // memeory allocation is done for the predefined size.
    s->container = (char *)malloc(sizeof(char) * max_size);
    if (!s->container)
    {
        printf("Memory allocation failed.\n");
        return;
    }
    s->top = -1;
    s->size = max_size;
}

// function to initalise stack conatiner dynamicaly
void createDynamicStack(struct stack *s, int size)
{
    // memory allocation is done for the size inputed.
    s->container = (char *)malloc(sizeof(char) * size);
    if (!s->container)
    {
        printf("Memory allocation failed.\n");
        return;
    }
    s->top = -1;
    s->size = size;
}

// function to check whether the stack is empty or not.
int isEmpty(struct stack s)
{
    return s.top == -1;
}

// function to check whether the stack is full or not.
int isFull(struct stack s)
{
    return s.top == s.size - 1;
}

// function to push into stack
void push(struct stack *s, char data)
{
    if (isFull(*s))
    {
        printf("Stack is full, cannot push.\n");
        return;
    }
    s->container[++s->top] = data;
    // printf("Element pushed to the stack.\n");
}

// function to pop out of the stack
char pop(struct stack *s)
{
    if (isEmpty(*s))
    {
        printf("No elements in the stack to pop.\n");
        return -1;
    }
    char data = s->container[s->top--];
    return data;
}

// function to peek in the stack or to access the top element.
char peek(struct stack s)
{
    if (isEmpty(s))
        return -1;
    else
        return s.container[s.top];
}

// the above stack is changed for characters now.

// precedence and isOperand functions
int precedence(char x);
int isOperand(char x);

// fucntion to convert infix expression to postfix.
void infixToPostfix(const char *infix, char *postfix);

// fucntion to convert infix expression to prefix.
void infixToPrefix(const char *infix, char *prefix);

// function to evaulate postfix.
int evaluatePostfix(const char postfix);

int main()
{
    char infix[] = "(a+b)+(a/b)*(a*b)";
    char postfix[strlen(infix)];

    infixToPostfix(infix, postfix);

    printf("%s", postfix);
    return 0;
}

// function to give the precednece of the operator.
int precedence(char x)
{
    if (x == '+' || x == '-')
        return 1;
    else if (x == '*' || x == '/')
        return 2;
    return 0;
}

// function to check whether it is a operand or not.
int isOperand(char x)
{
    return ((x >= '0' && x <= '9') || (x >= 'A' && x <= 'Z') || (x >= 'a' && x <= 'z'));
}

// create a function to convert infix expression to postfix.
void infixToPostfix(const char *infix, char *postfix)
{
    // create a stack for operators and opeartor manipulation and allocate memory dynamically
    struct stack expression;
    createDynamicStack(&expression, strlen(infix));

    // create iterators for infix string and postfix string.
    int i = 0, j = 0;

    // traverse the entire infix string until you reach the end.
    while (infix[i] != '\0')
    {
        // upon traversing take out the character
        char token = infix[i];

        // check whether the obtained token is a operand
        if (isOperand(token))
        {
            // if found as operand since it's postfix add it directly to postfix string
            postfix[j++] = token;
        }
        else if (token == '(')
        { // suppose it is a opening bracket push it the stack.
            push(&expression, token);
        }
        else if (token == ')')
        {
            // suppose it is a closing bracket empty the stack until you find the openning bracket of the respective closing bracket.
            while (!isEmpty(expression) && peek(expression) != '(')
            {
                postfix[j++] = pop(&expression);
            }
            // upon emptying the stack until the respective openning bracket discard the openning bracket.
            if (!isEmpty(expression) && peek(expression) == '(')
            {
                pop(&expression);
            }
        }
        else
        {// if the token is a opperator.

            // check whether the current token is the highest precedent within the stack else not pop until you find the least.
            while (!isEmpty(expression) && precedence(token) <= precedence(peek(expression)))
            {
                postfix[j++] = pop(&expression);
            }
            // push the operator to the stack.
            push(&expression, token);
        }

        // increment the iterator of the infix string.
        i++;
    }

    // empty out the stack 
    while(!isEmpty(expression)){
        postfix[j++] = pop(&expression);
    }

    // null terminate the postfix string.
    postfix[j] = '\0';
}
