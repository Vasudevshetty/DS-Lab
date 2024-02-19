/*Functions to convert the expression of infix to postfix or prefix based on the user requerst.*/

#include <stdio.h>
#include <string.h>
#include "stack_dynamic.h"
#include "stack_int.h"

int precedence(char c)
{
    if (c == '+' || c == '-')
        return 1;
    else if (c == '*' || c == '/')
        return 2;
    else if (c == '^')
        return 3;
    else
        return 0;
}

bool isOperand(char c)
{
    return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

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

typedef enum
{
    prefix,
    postfix,
} Notation;

char *reverse(char *expression)
{
    for (int i = 0, j = strlen(expression) - 1; i < j; i++, j--)
    {
        char temp = expression[i];
        expression[i] = expression[j];
        expression[j] = temp;
    }
    return expression;
}

char *convert(const char *expression, Notation notation)
{
    Stack *stack = createStack();
    int i = 0, j = 0, len = strlen(expression);
    char *result = (char *)malloc(sizeof(char) * len);
    if (!result)
    {
        printf("Memory allcoation failed.\n");
        exit(1);
    }

    while (i < len)
    {
        char token = notation == prefix ? expression[len - 1 - i] : expression[i];
        if (isOperand(token))
            result[j++] = token;
        else if (notation == prefix ? token == ')' : token == '(')
            push(stack, token);
        else if (notation == prefix ? token == '(' : token == ')')
        {
            while (!isEmpty(stack) && (notation == prefix ? peek(stack) != ')' : peek(stack) != '('))
                result[j++] = pop(stack);
            pop(stack);
        }
        else
        {
            while (!isEmpty(stack) &&
                   (notation == prefix ? precedence(token) < precedence(peek(stack)) : precedence(token) <= precedence(peek(stack))))
                result[j++] = pop(stack);
            push(stack, token);
        }
        i++;
    }
    while (!isEmpty(stack))
        result[j++] = pop(stack);
    result[j] = '\0';
    return notation == prefix ? reverse(result) : result;
}

int evaluate(const char *expression, Notation notation)
{
    StackInt *stack = createStackInt();
    int i = 0, len = strlen(expression);
    while (i < len)
    {
        char token = notation == prefix ? expression[len - i - 1] : expression[i];
        if (isOperand(token))
            pushInt(stack, token - '0');
        else if (isOperator(token))
        {
            int operand1 = popInt(stack);
            int operand2 = popInt(stack);
            int result = notation == prefix ? calculate(token, operand1, operand2) : calculate(token, operand2, operand1);
            pushInt(stack, result);
        }
        i++;
    }
    return peekInt(stack);
}

int main()
{
    char expression[100];
    int choice;
    do
    {
        printf("Enter the expresssion to operate : ");
        scanf("%s", expression);
        printf("Menu.\n1. Convert.\n2. Evaluate.\n3. Exit\n\n");
        printf("Enter choice : ");
        scanf("%d", &choice);
        int iChoice;
        switch (choice)
        {
        case 1:
            printf("Menu.\n1. Postfix\n2. Prefix\n");
            printf("Enter choice : ");
            scanf("%d", &iChoice);
            switch (iChoice)
            {
            case 1:
                printf("The postfix converted expression is : %s\n", convert(expression, postfix));
                break;
            case 2:
                printf("The postfix converted expression is : %s\n", convert(expression, prefix));
                break;
            }
            break;
        case 2:
            printf("Mention the type of the notation(prefix/postfix) (string) : ");
            char notation[10];
            scanf("%s", notation);
            printf("The evulated result of the %s expression is %d\n",
                   notation, evaluate(convert(expression, strcmp(notation, "postfix") ? postfix : prefix),
                    strcmp(notation, "postfix") ? postfix : prefix));
            break;
        case 3:
            printf("Exiting....\n");
            break;
        default:
            printf("Please input valid choice only...\n");
        }
        printf("\n\n");
    } while (choice != 3);

    return 0;
}