/*create a pointer to an integer array and pass this as a parameter to a function called reverse which reverse the array contents using
pointer. Wrte different function called read(p) and display(p) to display the array contents using p before and after reverse.*/

#include <stdio.h>

void read(int *ptr, int n);
void display(int *ptr, int n);

void reverse(int *ptr, int n);
void swap(int *x, int *y);

int main()
{
    int n;
    printf("Enter the size of the array : ");
    scanf("%d", &n);

    int array[n], *ptr;
    ptr = array;

    read(ptr, n);
    display(ptr, n);
    reverse(ptr, n);
    display(ptr, n);

    return 0;
}

void read(int *ptr, int n)
{
    printf("Enter the elements of the array : ");
    for (int i = 0; i < n; i++)
        scanf("%d", ptr + i);
}

void display(int *ptr, int n)
{
    printf("The elements of the array are : ");
    for (int i = 0; i < n; i++)
        printf("%d ", *(ptr + i));

    printf("\n");
}

void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

void reverse(int *ptr, int n)
{
    int startIdx = 0;
    int endIdx = n - 1;

    while (startIdx < endIdx)
    {
        swap(ptr+startIdx, ptr+endIdx);
        startIdx++;
        endIdx--;
    }
}