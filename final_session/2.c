/*Develop a menu driven program to implement the following operations on an array of integers with dynamic
memory allocation. Display the array contents after each operation.
i) Insert by position ii) Delete by key iii) Search by position iv) Reverse the contents.
*/

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

void insertByPosition(Array *array, int data, int position)
{
    if (position < 0 || position > array->length)
    {
        printf("Invalid position to insert, Insertion failed.\n");
        return;
    }
    if (isFull(array))
    {
        printf("Array is full, cannot insert.\n");
        return;
    }

    for(int i = array->length; i > position; i--)
        array->items[i] = array->items[i - 1];

    array->items[position] = data;
    array->length++;
}

int searchByKey(const Array *array, int key)
{
    for (int i = 0; i < array->length; i++)
    {
        if (array->items[i] == key)
            return i;
    }
    return -1;
}

int deleteByKey(Array *array, int key)
{
    if (isEmpty(array))
    {
        printf("Array is empty, deletion of key failed.\n");
        return -1;
    }
    int position = searchByKey(array, key);
    if (position == -1)
    {
        printf("Key not found to delete.\n");
        return -1;
    }

    for (int i = position; i < array->length - 1; i++)
        array->items[i] = array->items[i + 1];

    array->length--;
    return position;
}

int searchByPosition(const Array *array, int position)
{
    if (position < 0 || position >= array->length)
    {
        printf("Invalid position to search.\n");
        return -1;
    }
    else
    {
        int data = array->items[position];
        printf("The element at the position is %d\n", data);
        return data;
    }
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

int main()
{
    Array *array = initArray();
    int data, key, position;
    int choice;

    do
    {
        printf("\nMenu\n");
        printf("1. Insert By Position\n2. Delete By Key\n3. Search By Postioin\n4. Reverse\n5. Exit\n");
        printf("Enter your choice : ");
        scanf("%d", &choice);

        printf("\n");

        switch (choice)
        {
        case 1:
            printf("Enter data & position : ");
            scanf("%d %d", &data, &position);
            insertByPosition(array, data, position);
            display(array);
            break;
        case 2:
            printf("Enter key : ");
            scanf("%d", &key);
            deleteByKey(array, key);
            display(array);
            break;
        case 3:
            printf("Enter position: ");
            scanf("%d", &position);
            searchByPosition(array, position);
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