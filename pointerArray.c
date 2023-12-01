/*Create a pointer ot an interger array . Read and display the contents of the array using pointer .
and also display the contents in reverse order using pointer.*/

#include <stdio.h>

int main()
{
    int n;
    printf("Enter the size of the array : ");
    scanf("%d", &n);

    // create a pointer and point to the array
    int array[n];
    int *ptr = array;

    // read the contents of the array using pointer.
    printf("Enter the elements of the array : ");
    for (int i = 0; i < n; i++)
        scanf("%d", ptr + i);
    printf("\n");

    // similarly print the contents using pointer.
    printf("The elements of the array is : ");
    for (int i = 0; i < n; i++)
        printf("%d ", *(ptr + i));
    printf("\n");

    // now print the array in reverse order.
    printf("The elemetns in reverse order is : ");
    for (int i = n - 1; i >= 0; i--)
        printf("%d ", *(ptr + i));
    printf("\n");

    // reasssign of pointer is not required becasue you are not mainiputlatin with pointer.,

    return 0;
}