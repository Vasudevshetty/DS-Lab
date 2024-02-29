/*Develop a menu driven program to implement Stack with static and dynamic
memory allocation mechanisms using array storage representation. (Represent
Stack using structure)
*/

#include <stdio.h>
#include <stdlib.h>

#define max_size 100

// structure to create a stack with members.
struct stack
{
    int container[max_size]; // array to store elements(items)
    int top;                 // the top pointer used to manipulate.
    int size;                // the size of the stack container.
};

// function to allcoate memory allcoation.
struct stack *createStaticStack();

// condinational functions.
int isEmpty(const struct stack *);
int isFull(const struct stack *);

// operations
void push(struct stack *, int);
int pop(struct stack *);
int peek(const struct stack *);

// display function
void display(const struct stack *);

int main()
{
    struct stack *s = createStaticStack();
    int choice, data;

    do
    {
        printf("\n\n");
        printf("Menu.\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Peek\n");
        printf("4. Display\n");
        printf("5.Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        printf("\n\n");
        switch (choice)
        {
        case 1:
            printf("Enter the element to push: ");
            scanf("%d", &data);
            push(s, data);
            display(s);
            break;
        case 2:
            data = pop(s);
            if (data != -1)
                printf("The popped element is %d.\n", data);
            display(s);
            break;
        case 3:
            printf("The element on the top of the stack is %d.\n", peek(s));
            break;
        case 4:
            display(s);
            break;
        case 5:
            printf("Exiting...");
            break;
        default:
            printf("Invalid choice.. please try again. \n");
            break;
        }
    } while (choice != 5);

    return 0;
}

// function to initalise stack container staticly
struct stack *createStaticStack()
{
    // memeory allocation is done for the predefined size.
    struct stack *s = (struct stack *)malloc(sizeof(struct stack));
    if (!s)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    s->top = -1;
    s->size = max_size;
    return s;
}

// function to check whether the stack is empty or not.
int isEmpty(const struct stack *s)
{
    return s->top == -1;
}

// function to check whether the stack is full or not.
int isFull(const struct stack *s)
{
    return s->top == s->size - 1;
}

// function to push into stack
void push(struct stack *s, int data)
{
    if (isFull(s))
    {
        printf("Stack is full, cannot push.\n");
        return;
    }
    s->container[++s->top] = data;
    printf("Element pushed to the stack.\n");
}

// function to pop out of the stack
int pop(struct stack *s)
{
    if (isEmpty(s))
    {
        printf("No elements in the stack to pop.\n");
        return -1;
    }
    int data = s->container[s->top--];
    return data;
}

// function to peek in the stack or to access the top element.
int peek(const struct stack *s)
{
    if (isEmpty(s))
        return -1;
    else
        return s->container[s->top];
}

// function to display the contents of the stack.
void display(const struct stack *s)
{
    if (isEmpty(s))
    {
        printf("Stack is empty.\n");
        return;
    }
    printf("Elements(contents) of stack are,\n");
    for (int i = 0; i <= s->top; i++)
    {
        printf("%d ", s->container[i]);
    }
    printf("\n");
}