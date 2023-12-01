/*Create a pointer called p1, p2 and p3 and an integer value x where p1 points to p2, p2 points to p3,
p3 ponts to x , demonstrate how to read and reterive the value of x using p1, p2 and p3.*/

#include <stdio.h>

int main()
{
    // create 3 pointers
    int *p3, **p2, ***p1;
    int x;
    printf("Enter the value of x: ");
    scanf("%d", &x);

    // assign the pointer as given
    p3 = &x;
    p2 = &p3;
    p1 = &p2;

    printf("The value of x using p1 pointer is : %d\n", ***p1);
    printf("The value of x using p2 pointer is : %d\n", **p2);
    printf("The value of x using p3 pointer is : %d\n", *p3);

    return 0;
}