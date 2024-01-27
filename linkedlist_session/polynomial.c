#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int coeff;
    int exp;
} Term;

typedef struct Node
{
    Term *term;
    struct Node *next;
} node;

typedef struct
{
    struct Node *head;
    int length;
    int degree;
} polynomial;

Term *createTerm(int coeff, int exp);
node *createNode(Term *term);
polynomial *initPolynomial();

polynomial *add(polynomial *poly1, polynomial *poly2);
void insert(polynomial *poly, Term *term);
void createPolynomial(polynomial *poly);
void destructList(polynomial *poly);
void display(polynomial *poly);

int main()
{
    polynomial *poly = initPolynomial();
    int coeff, exp, choice;
    polynomial *poly1 = initPolynomial();
    polynomial *poly2 = initPolynomial();
    polynomial *sum = initPolynomial();
    do
    {
        printf("Menu.\n1. Insert.\n2. Display.\n3. Add\n4. Exit\n");
        printf("Enter choice : ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("Enter co-efficent and exponent of the term: ");
            scanf("%d %d", &coeff, &exp);
            Term *term = createTerm(coeff, exp);
            insert(poly, term);
            display(poly);
            term = NULL;
            break;
        case 2:
            display(poly);
            break;
        case 3:
            createPolynomial(poly1);
            createPolynomial(poly2);
            sum = add(poly1, poly2);
            display(sum);
            destructList(poly1);
            destructList(poly2);
            destructList(sum);
            break;
        case 4:
            printf("Exiting....\n");
            destructList(poly);
            break;
        default:
            printf("Invalid choice... please try again..\n");
        }
        printf("\n\n");
    } while (choice != 4);

    return 0;
}

Term *createTerm(int coeff, int exp)
{
    Term *term = (Term *)malloc(sizeof(Term));
    if (!term)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    term->coeff = coeff;
    term->exp = exp;
    return term;
}

node *createNode(Term *term)
{
    node *newNode = (node *)malloc(sizeof(node));
    if (!newNode)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    newNode->term = term;
    newNode->next = NULL;
    return newNode;
}

polynomial *initPolynomial()
{
    polynomial *poly = (polynomial *)malloc(sizeof(polynomial));
    if (!poly)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    Term *term = createTerm(0, 0);
    poly->head = createNode(term);
    poly->length = 0;
    poly->degree = 0;
    return poly;
}

int isSorted(polynomial *poly)
{
    node *temp = poly->head->next;
    while (temp && temp->next)
    {
        if (temp->term->exp > temp->next->term->exp)
            temp = temp->next;
        else
            return 0;
    }
    return 1;
}

int isEmpty(polynomial *poly) { return (poly->head->next == NULL && poly->length == 0); }

void insert(polynomial *poly, Term *term)
{
    node *newNode = createNode(term);

    if (isEmpty(poly) || poly->head->next->term->exp <= term->exp)
    {
        newNode->next = poly->head->next;
        poly->head->next = newNode;
        poly->length++;
        if (poly->length == 1)
        {
            poly->degree = term->exp;
        }
        return;
    }

    if (isSorted(poly))
    {
        node *temp = poly->head->next;
        while (temp->next && temp->next->term->exp > term->exp)
        {
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
        poly->length++;
    }
    else
    {
        printf("Polynomial list isn't sorted.\n");
        // Handle sorting issue here
    }
}

void display(polynomial *poly)
{
    if (isEmpty(poly))
    {
        printf("Polynomial expression is empty.\n");
        return;
    }
    node *temp = poly->head->next;
    printf("The Polynomial expresssion is, \n");
    while (temp)
    {
        if (temp->term->exp == 0)
            printf("%+d\n", temp->term->coeff);
        else
        {
            printf("%+dx^%+d", temp->term->coeff, temp->term->exp);
        }
        temp = temp->next;
    }
}

void destructList(polynomial *poly)
{
    node *temp = poly->head->next;
    while (temp)
    {
        node *next = temp->next;
        free(temp);
        temp = next;
    }
    free(poly);
}

polynomial *add(polynomial *poly1, polynomial *poly2)
{
    polynomial *poly = initPolynomial();
    node *temp1 = poly1->head->next;
    node *temp2 = poly2->head->next;

    while (temp1 && temp2)
    {
        if (temp1->term->exp > temp2->term->exp)
        {
            insert(poly, createTerm(temp1->term->coeff, temp1->term->exp));
            temp1 = temp1->next;
        }
        else if (temp1->term->exp < temp2->term->exp)
        {
            insert(poly, createTerm(temp2->term->coeff, temp2->term->exp));
            temp2 = temp2->next;
        }
        else
        {
            insert(poly, createTerm(temp1->term->coeff + temp2->term->coeff, temp1->term->exp));
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
        poly->length++;
    }
    while (temp1)
    {
        insert(poly, createTerm(temp1->term->coeff, temp1->term->exp));
        temp1 = temp1->next;
    }
    while (temp2)
    {
        insert(poly, createTerm(temp2->term->coeff, temp2->term->exp));
        temp2 = temp2->next;
    }
    poly->degree = poly->head->next->term->exp;
    destructList(poly1);
    destructList(poly2);
    return poly;
}

void createPolynomial(polynomial *poly)
{
    int terms;
    printf("Enter the no of terms: ");
    scanf("%d", &terms);

    for (int i = 0; i < terms; i++)
    {
        int coeff, exp;
        printf("Enter the coeff and exp of the term : ");
        scanf("%d %d", &coeff, &exp);
        insert(poly, createTerm(coeff, exp));
    }
}
