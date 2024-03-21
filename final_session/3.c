/*Develop a menu driven program to implement the following operations on an array of integers with dynamic
memory allocation. Display the array contents after each operation.
i) Insert by order ii) Delete by position iii) Search by key iv) Reverse the contents*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Array
{
    int *items;
    int length;
} Array;

#define MAX 100

Array *initArray()
{
    Array *array = (Array *)malloc(sizeof(Array));
    if (!array)
    {
        printf("Memorry allcoation failed.\n");
        exit(1);
    }
    array->items = (int *)malloc(sizeof(int) * MAX);
    if (!array->items)
    {
        printf("Memory allocatin failed.\n");
        free(array);
        exit(1);
    }
    array->length = 0;
    return array;
}

bool isEmpty(const Array *array)
{
    return array->length == 0;
}

bool isFull(const Array *array)
{
    return array->length == MAX - 1;
}

void display(const Array *array)
{
    if (isEmpty(array))
    {
        printf("Array is empty, no elements to display.\n");
        return;
    }

    printf("The elements of the array are,\n");
    for (int i = 0; i < array->length; i++)
        printf("%d ", array->items[i]);
    printf("\nThe length of the array is %d\n", array->length);
}

void reverse(Array *array)
{
    if (isEmpty(array))
    {
        printf("Array is empty, cannot reverse.\n");
        return;
    }

    for (int i = 0, j = array->length - 1; i < j; i++, j--)
    {
        int temp = array->items[i];
        array->items[i] = array->items[j];
        array->items[j] = temp;
    }
}

void insertInOrder(Array *array, int data)
{
    if (isFull(array))
    {
        printf("Array is full, insertion failed.\n");
        return;
    }
    int position = 0;
    while (position < array->length && data >= array->items[position])
        position++;

    for(int i = array->length; i > position; i--)
        array->items[i] = array->items[i - 1];

    array->length++;
    array->items[position] = data;
}

int deleteByPostion(Array *array, int position)
{
    if (isEmpty(array))
    {
        printf("Memory allcoatin failed.\n");
        return -1;
    }
    if (position < 0 || position >= array->length)
    {
        printf("Invalid position to delete, deleteion failed.\n");
        return -1;
    }

    int data = array->items[position];
    for (int i = position; i < array->length - 1; i++)
        array->items[i] = array->items[i + 1];

    array->length--;
    return data;
}

int searchByKey(const Array *array, int key)
{
    if (isEmpty(array))
    {
        printf("Array is empty, search failed.\n");
        return -1;
    }

    for (int i = 0; i < array->length; i++)
    {
        if (array->items[i] == key)
        {
            printf("Key found at position %d\n", i);
            return i;
        }
    }
    printf("Key not found.\n");
    return -1;
}

int main()
{
    Array *array = initArray();
    int data, key, position;
    int choice;

    do
    {
        printf("\nMenu\n");
        printf("1. Insert in Order\n2. Delete by position\n3. Search by Key\n4. Reverse\n5. Exit\n");
        printf("Enter your choice : ");
        scanf("%d", &choice);

        printf("\n");

        switch (choice)
        {
        case 1:
            printf("Enter data : ");
            scanf("%d", &data);
            insertInOrder(array, data);
            display(array);
            break;
        case 2:
            printf("Enter position: ");
            scanf("%d", &position);
            deleteByPostion(array, position);
            display(array);
            break;
        case 3:
            printf("Enter key : ");
            scanf("%d", &key);
            searchByKey(array, key);
            break;
        case 4:
            reverse(array);
            display(array);
            break;
        case 5:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice, please try again.\n");
            break;
        }
    } while (choice != 5);

    free(array->items);
    free(array);
    return 0;
}