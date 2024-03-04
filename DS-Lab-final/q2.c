/*Develop a menu driven program to implement the following operations on an array of
integers with dynamic memory allocation. Display the array contents after each operation.
i) Insert by position ii) Delete by key iii) Search by position iv) Reverse the contents.*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 100
typedef struct Array
{
    int *arr;
    int length;
} Array;

Array *initArray()
{
    Array *array = (Array *)malloc(sizeof(Array));
    if (!array)
    {
        printf("Memory allocatin failed.\n");
        exit(1);
    }
    array->arr = (int *)malloc(sizeof(int) * MAX_SIZE);
    if (!array->arr)
    {
        printf("Memory allcoatin failed.\n");
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

void display(const Array *array)
{
    if (isEmpty(array))
    {
        printf("No elements to display.\n");
        return;
    }
    printf("Elements of the array are, \n");
    for (int i = 0; i < array->length; i++)
        printf("%d ", array->arr[i]);
    printf("\nThe length of the array is %d\n", array->length);
}

void reverse(Array *array)
{
    if (isEmpty(array))
    {
        printf("No elements to reverse.\n");
        return;
    }
    for (int i = 0, j = array->length - 1; i < j; i++, j--)
    {
        int temp = array->arr[i];
        array->arr[i] = array->arr[j];
        array->arr[j] = temp;
    }
}

int search(const Array *array, int position)
{
    return isEmpty(array) && (position < 0 || position >= array->length) ? -1 : array->arr[position];
}

void insert(Array *array, int value, int position)
{
    if (position < 0 || position > array->length)
    {
        printf("Invalid position to insert.\n");
        return;
    }

    for (int i = array->length - 1; i >= position; i--)
        array->arr[i + 1] = array->arr[i];
    array->arr[position] = value;
    array->length++;
}

int delete(Array* array, int key){
    if(isEmpty(array)){
        printf("Array is empty, cannot delete.\n");
        return -1;
    }

    int position = 0;
    for (position = 0; position < array->length; position++){
        if(array->arr[position] == key)
            break;
    }

    if(position == array->length){
        printf("Key not found to delete.\n");
        return -1;
    }

    for (int i = position; i < array->length - 1; i++)
        array->arr[i] = array->arr[i + 1];

    array->length--;
    return position;
}

int main(){
    Array *array = initArray();

    insert(array, 1, 0);
    insert(array, 3, 1);
    insert(array, 9, 2);
    insert(array, 2, 3);
    insert(array, 8, 4);

    display(array);
    reverse(array);
    display(array);

    delete (array, 3);
    display(array);
    delete (array, 9);
    display(array);
    delete(array, 10);
    display(array);

    delete (array, 1);
    delete (array, 8);
    delete (array, 2);
    delete (array, 3);
    display(array);
    return 0;
}