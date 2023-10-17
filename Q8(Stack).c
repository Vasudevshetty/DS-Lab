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
    int *container; // array to store elements(items)
    int top;        // the top pointer used to manipulate.
    int size;       // the size of the stack container.
};

// functions to create either by dynamic allocation or static allocation.
void createStaticStack(struct stack *s);
void createDynamicStack(struct stack *s, int size);

// condinational functions.
int isEmpty(struct stack s);
int isFull(struct stack s);

// operations
void push(struct stack *s, int data);
int pop(struct stack *s);
int peek(struct stack s);

// display function
void display(struct stack s);

int main()
{
    struct stack s;
    s.container = NULL;
    int size, choice, data;

    printf("Enter the mode of allocation.\n1. Static allocation.\n2. Dynamic allocation.\n");
    printf("Enter your choice : ");
    scanf("%d", &choice);

    if (choice == 1)
    {
        createStaticStack(&s);
    }
    else if (choice == 2)
    {
        printf("Enter the size of the stack : ");
        scanf("%d", &size);
        createDynamicStack(&s, size);
    }
    else
    {
        printf("Invalid choice.  Retry.\n");
        main();
    }
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
            push(&s, data);
            break;
        case 2:
            data = pop(&s);
            if (data != -1)
                printf("The popped element is %d.\n", data);
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

    free(s.container);
    return 0;
}

// function to initalise stack container staticly
void createStaticStack(struct stack *s)
{
    // memeory allocation is done for the predefined size.
    s->container = (int *)malloc(sizeof(int) * max_size);
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
    s->container = (int *)malloc(sizeof(int) * size);
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
void push(struct stack *s, int data)
{
    if (isFull(*s))
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
    if (isEmpty(*s))
    {
        printf("No elements in the stack to pop.\n");
        return -1;
    }
    int data = s->container[s->top--];
    return data;
}

// function to peek in the stack or to access the top element.
int peek(struct stack s)
{
    if (isEmpty(s))
        return -1;
    else
        return s.container[s.top];
}

// function to display the contents of the stack.
void display(struct stack s)
{
    if (isEmpty(s))
    {
        printf("Stack is empty.\n");
        return;
    }
    printf("Elements(contents) of stack are,\n");
    for (int i = 0; i <= s.top; i++)
    {
        printf("%d ", s.container[i]);
    }
    printf("\n");
}