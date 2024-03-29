/* Develop arr->menu driven program to implement various operations on array
storage representation with static and dynamic memory allocation.
i) Insert by position. ii) Delete by position. iii) Insert by key. iv) Delete by key.
v) Insert by order. vi) Search by key. vii) Search by position. viii) Reverse the contents.*/

#include <stdio.h>
#include <stdlib.h>

#define max_size 100
// maximum size of array.

typedef struct
{
    int *array;
    // pointer to store the base address of array.
    int size;
    // variable to create arr->array of size.
    int length;
    // variable to track down length.
} Array;
/* Created arr->structure called array with respective members.*/

// function to display.
// passing as arr->value is enough due to its operation of printing and not in requirement of any changes.
void display(const Array *arr)
{
    if (arr->length == 0)
    {
        printf("No elements to display...\n");
        return;
    }

    printf("Elements of the array are,\n");
    for (int i = 0; i < arr->length; i++)
    {
        printf("%d ", *(arr->array + i));
    }
    printf("\n");
}

// function to initalise the refernced array from main.
// passed as arr->refernce to use the same structure passed by main instead making arr copy.
Array *initArray()
{
    Array *arr = (Array *)malloc(sizeof(Array));
    if (!arr)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    printf("Enter the size of the array: ");
    scanf("%d", &arr->size);

    arr->array = (int *)calloc(arr->size, sizeof(int)); // initalised zero in the array.

    // condition in case memory allocation gets failed.
    if (arr->array == NULL)
    {
        printf("Memory allocation failed...\n");
        exit(1);
    }

    arr->length = 0; // set length as zero.
    return arr;
}

// function to destruct or to free the memory dynamically allocated.
void freeArray(Array *arr)
{
    free(arr->array);            // free dynamically created array.
    arr->array = NULL;           // set array pointer to null.
    arr->size = arr->length = 0; // deinitalise.
    free(arr);                   // free the array structure too.
}

// function to insert value at given position in the array.
/*Using structure, makes it easy to have organised pair of size, length and the array so as to track down easily with memory related issues.
Note the array is again being refernced to have changes in the array that is being passed from the main function.*/
void insertByPosition(Array *arr, int position, int value)
{

    // checking whether the position provided is valid.
    if (position < 0 || position >= arr->length)
    {
        printf("Invalid position to insert. Insertion failed.\n");
        return;
    }

    // checking whether the array of size is being filled out and manipulating across.
    //  i.e If the array is full, allocate more memory...
    if (arr->length == arr->size && arr->size != max_size)
    {
        arr->size++;
        // in that case extend the size to accmodate the new value instead of popping out one.
        arr->array = realloc(arr->array, arr->size * sizeof(int));
        // reallocation of memory is done to ensure the memory is given acc to.

        // further check if memory management fails.
        if (arr->array == NULL)
        {
            printf("Memory reallocation failed...\n");
            exit(1);
        }
    }

    // rearranging the array so as to make space for the value to inserted at that position.
    // shifting of the value at the neighbourhood position takes place.
    for (int i = arr->length; i > position; i--)
    {
        *(arr->array + i) = *(arr->array + i - 1);
    }

    *(arr->array + position) = value; // value is being inserted.

    // length variable is updated.
    arr->length++;

    printf("\nElement %d inserted at position %d.\n\n", value, position);

    // displaying
    display(arr);
}

// function to delete element at position and returning it.
// passed as arr->refernce to encounter changes.
int deleteByPosition(Array *arr, int position)
{

    // checking whether the given position is valid.
    if (position < 0 || position >= arr->length)
    {
        printf("Invalid position to delete. Deletion failed...\n");
        return -1;
    }

    if (arr->length == 0)
    {
        printf("No elements to delete..\n");
        return -1;
    }

    int deletedElement = arr->array[position]; // take the element to be deleted.

    // shifting the elements in place.
    for (int i = position; i < arr->length - 1; i++)
    {
        *(arr->array + i) = *(arr->array + i + 1);
    }

    // decrease the length due to deletion of arr->element.
    arr->length--;
    // optional to make the last element as zero as to understand the shift that occured due to deletion of element.
    arr->array[arr->length] = 0;

    printf("Deleted %d at position %d.\n", deletedElement, position);

    display(arr); // displaying of the array.
    return deletedElement;
}

// function to search the element by position and return with printing approprite msg.
// passed as arr->value since no changes are required.
int searchByPosition(const Array *arr, int position)
{
    // checking whether the position is valid or not.
    if (position < 0 || position > arr->length - 1)
    {
        printf("Not arr->valid positon to search.\n");
        return -1;
    }

    printf("Element %d found at position %d.\n", arr->array[position], position);

    return *(arr->array + position);
}

// function to search the element by key and return with printing approprite msg.
// passed as arr->value since no changes are required.
int searchByKey(const Array *arr, int key)
{
    // simple linear search technique.
    for (int i = 0; i < arr->length; i++)
    {
        if (arr->array[i] == key) // can be used pointer type too.
        {
            printf("Element %d found at position(index) %d.\n", key, i);
            return i;
        }
    }
    printf("No key found...Searching failed.\n");
    return -1;
}

// function to reverse the array.
// passed as arr->reference so as it have changes in the array.
void reverseArray(Array *arr)
{
    if (arr->length == 0)
    {
        printf("No elements to reverse.\n");
        return;
    }
    // swapping of the first and last counterparts happen in this logic, i.e first swaps with last, second with last-second , etc....
    for (int i = 0, j = arr->length - 1; i < j; i++, j--)
    {
        int temp = *(arr->array + i);
        *(arr->array + i) = *(arr->array + j);
        *(arr->array + j) = temp;
        // can be done using indexing too.
    }
    printf("Reversed array is,\n");
    display(arr);
}

// function to insert elements in order (either ascending, descending or any custom order.)
// insertion is done by comparing with the value and with the operation req like either ascending or descending likewise.
// passed as arr->reference to observe changes in the structure passed.
void insertByOrder(Array *arr, int value)
{
    int position = 0;

    while (position < arr->length && arr->array[position] < value)
        position++;

    /*Since inserting by order requires arr->positon to be inserted while maintaining the order, finding the correct position is the only
    task. Upon finding the position as described above in the while loop calling the function insertByPosition() makes the work complete.*/
    insertByPosition(arr, position, value);
}

// function to insert by key
void insertByKey(Array *arr, int key, int value)
{
    int position = searchByKey(arr, key);
    // the function returns the index of the key.

    if (position == -1)
    {
        printf("Key %d not found.. Insertion faild..\n", key);
        return;
    }
    // checking whether the postion was found or not if not message, else call the insertByPosition function.
    insertByPosition(arr, position, value);
}

// function to delete by key.
void deleteByKey(Array *arr, int key)
{
    int position = searchByKey(arr, key);
    // the function returns the index of the key.

    if (position == -1)
    {
        printf("Key %d not found.. Insertion faild..\n", key);
        return;
    }
    // checking whether the postion was found or not if not message, else call the deleteByPosition function.
    deleteByPosition(arr, position);
}

int main()
{
    int choice;
    int value, position, key;

    Array *arr = initArray();

    do
    {
        printf("\n");
        printf("Menu\n");
        printf("1. Insert by Position.\n");
        printf("2. Delete by Position.\n");
        printf("3. Insert by key.\n");
        printf("4. Delete by key.\n");
        printf("5. Insert by order.\n");
        printf("6. Search by key.\n");
        printf("7. Search by position.\n");
        printf("8. Reverse the contents.\n");
        printf("9. Display.\n");
        printf("10. Exit.\n");
        printf("\nEnter choice : ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("Enter the position to be inserted and the value : ");
            scanf("%d %d", &position, &value);
            insertByPosition(arr, position, value);
            break;
        case 2:
            printf("Enter position to be delete: ");
            scanf("%d", &position);
            deleteByPosition(arr, position);
            break;
        case 3:
            printf("Enter key and value to be inserted: ");
            scanf("%d %d", &key, &value);
            insertByKey(arr, key, value);
            break;
        case 4:
            printf("Enter key to be deleted: ");
            scanf("%d", &key);
            deleteByKey(arr, key);
            break;
        case 5:
            printf("Enter value to insert in order: ");
            scanf("%d", &value);
            insertByOrder(arr, value);
            break;
        case 6:
            printf("Enter position to be searched: ");
            scanf("%d", &position);
            searchByPosition(arr, position);
            break;
        case 7:
            printf("Enter key to be searched: ");
            scanf("%d", &key);
            searchByKey(arr, key);
            break;
        case 8:
            reverseArray(arr);
            break;
        case 9:
            display(arr);
            break;
        case 10:
            freeArray(arr);
            printf("Exiting....\n");
            break;
        default:
            printf("Enter valid choice... Please try again.\n");
            break;
        }
    } while (choice != 10);
    freeArray(arr);
    return 0;
}
