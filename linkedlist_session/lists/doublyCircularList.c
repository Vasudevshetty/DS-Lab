/*Develop a menu driven program to implement Circular Double linked list with
Header node to perform various operations such as
i) Insertion and Deletion at front/rear
ii) Insertion and Deletion at the specified position
iii) Delete by Key
iv) Search by key
v) Create an ordered list
vi) Reverse a list
vii) Creating a copy of the list */

/*I have used tail pointer for both double linked list and circular double linked list, which makes it proficient in
many operations, although not easier to readable and take some storage and increases complexity, it helps in better
understanding of how memmory allocatoins linkedlist operations work.

One can prefer ignoring tail pointer and rear operations time complexity drops to O(n), (as shown in linked list and circular
linked list) where n is the length of the linked list.*/

#include <stdio.h>
#include <stdlib.h>

// structure to store the node of the double linked list.
typedef struct Node
{
    int data;
    struct Node *next;
    struct Node *prev;
} node;

// structure to store the double linkedlist's head and tail and its length.
typedef struct
{
    struct Node *head;
    struct Node *tail;
    int length;
} circularDoubleLinkedList;

// function to check conditions.
int isEmpty(const circularDoubleLinkedList *);
int isCircular(const circularDoubleLinkedList *);
int isSorted(const circularDoubleLinkedList *);

// function to initalise the node and list.
void initNode(node *, int);
circularDoubleLinkedList *initCircularDoubleLinkedList();
node *createNode(int);

// function to insert.
void insertAtHead(circularDoubleLinkedList *, int);
void insertAtRear(circularDoubleLinkedList *, int);
void insertAtPosition(circularDoubleLinkedList *, int, int);

// functions to delete.
int deleteAtHead(circularDoubleLinkedList *);
int deleteAtRear(circularDoubleLinkedList *);
int deleteAtPosition(circularDoubleLinkedList *, int);

// operation on keys.
node *searchByKey(const circularDoubleLinkedList *, int);
int deleteByKey(circularDoubleLinkedList *, int);

// other operatins.
void createOrderedList(circularDoubleLinkedList *, int);
void reverse(circularDoubleLinkedList *);
circularDoubleLinkedList *copyList(const circularDoubleLinkedList *);

// display function.
void display(const circularDoubleLinkedList *);

void destructList(circularDoubleLinkedList *);

int main()
{
    circularDoubleLinkedList *myList = initCircularDoubleLinkedList();
    circularDoubleLinkedList *copy;
    int choice, data, position, key;

    do
    {
        printf("\n\n");
        printf("Menu.\n");
        printf("1. Insert at head(front).\n");
        printf("2. Insert at rear\n");
        printf("3. Insert at specific position.\n");
        printf("4. Delete from head(front).\n");
        printf("5. Delete from rear(tail).\n");
        printf("6. Delete from specific position.\n");
        printf("7. Delete by key.\n");
        printf("8. Search by key.\n");
        printf("9. Create a ordered list.\n");
        printf("10. Reverse the linked list.\n");
        printf("11. Create a copy of the list.\n");
        printf("12.Display the list.\n");
        printf("13.Exit.\n");

        printf("Enter the choice of operation : ");
        scanf("%d", &choice);
        printf("\n\n");

        // added menu driven feature intend as you need.

        switch (choice)
        {
        case 1:
            printf("Enter data to insert at front: ");
            scanf("%d", &data);
            insertAtHead(myList, data);
            display(myList);
            break;
        case 2:
            printf("Enter data to insert at rear: ");
            scanf("%d", &data);
            insertAtRear(myList, data);
            display(myList);
            break;
        case 3:
            printf("Enter data to insert: ");
            scanf("%d", &data);
            printf("Enter position to insert at: ");
            scanf("%d", &position);
            insertAtPosition(myList, data, position);
            display(myList);
            break;
        case 4:
            deleteAtHead(myList);
            display(myList);
            break;
        case 5:
            deleteAtRear(myList);
            display(myList);
            break;
        case 6:
            printf("Enter position to delete: ");
            scanf("%d", &position);
            deleteAtPosition(myList, position);
            display(myList);
            break;
        case 7:
            printf("Enter key to delete: ");
            scanf("%d", &key);
            deleteByKey(myList, key);
            display(myList);
            break;
        case 8:
            printf("Enter key to search: ");
            scanf("%d", &key);
            searchByKey(myList, key);
            break;
        case 9:
            printf("Enter data to insert in the ordered list: ");
            scanf("%d", &data);
            createOrderedList(myList, data);
            display(myList);
            break;
        case 10:
            reverse(myList);
            printf("Reversed list is,\n");
            display(myList);
            break;
        case 11:
            copy = copyList(myList);
            display(myList);
            printf("Copied list is,\n");
            display(copy);
            destructList(copy);
            break;
        case 12:
            display(myList);
            break;
        case 13:
            printf("Exiting the program....\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
    } while (choice != 13);
    destructList(myList);
    return 0;
}

void destructList(circularDoubleLinkedList *myList)
{
    node *temp = myList->head->next;
    do
    {
        node *next = temp->next;
        free(temp);
        temp = next;
    } while (temp != myList->head->next);
    free(myList->head);
    free(myList->tail);
    free(myList);
}

node *createNode(int data)
{
    node *newNode = (node *)malloc(sizeof(node));
    if (!newNode)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    initNode(newNode, data);
    return newNode;
}

// function to initalise nodes.
void initNode(node *Node, int data)
{
    Node->data = data;
    Node->next = Node;
    Node->prev = Node;
}

// function to initalise linked list.
circularDoubleLinkedList *initCircularDoubleLinkedList()
{
    circularDoubleLinkedList *myList = (circularDoubleLinkedList *)malloc(sizeof(circularDoubleLinkedList));
    if (!myList)
    {
        printf("Memeory allocation failed.\n");
        exit(1);
    }
    myList->head = createNode(0);
    myList->head->next = NULL;
    myList->tail = NULL;
    myList->length = 0;
    return myList;
}

// function to check whether the list is empty or not.
int isEmpty(const circularDoubleLinkedList *myList)
{
    return !(myList->length && myList->head->next && myList->tail);
}

// function to check whether the given list is circular or not.
int isCircular(const circularDoubleLinkedList *myList)
{
    if (isEmpty(myList))
    {
        return 0;
        // empty list isn't circular.
    }

    // check whether the head and tail are valid pointers.
    if (!myList->head->next || !myList->tail)
        return 0;

    /*If not using tail pointer, then you have to try a different approach.*/

    // if you are using a tail pointer then obivously tail's next and head's prev should pointing to each other.
    if (myList->head->next->prev != myList->tail || myList->tail->next != myList->head->next)
        return 0;
    else
        return 1;
}

// function to insert at head of the linkedlist.
void insertAtHead(circularDoubleLinkedList *myList, int data)
{
    // check whether the list is circular, if not to maintain circularity return.
    if (!isCircular(myList))
    {
        // again check whether the list is not emtpy if it isn't empty and not circular then print.
        if (!isEmpty(myList))
        {
            printf("List isn't circular.\n");
            return;
        }
        // if it is empty insert the head since empty list is always consdiered not circular.
        // so the order of the 2 if conditon can be reversed but works the same.
    }

    // create a new node, if allocated iniatlise.
    node *newNode = createNode(data);

    // check whether the list is empty that is head is null.
    if (!myList->head->next)
    {
        // if so insert the head. no other changes required.
        myList->head->next = newNode;
        myList->tail = newNode;
    }
    else
    {
        // if the list is already present and you have to insert, then

        // adjust the new node's next and and old head's prev to new node.
        newNode->next = myList->head->next;
        myList->head->next->prev = newNode;
        // make the newnode as head.
        myList->head->next = newNode;

        // make it circular by changing the links of the tail and head pointer. (which was previously pointing to old head).
        myList->tail->next = myList->head->next;
        myList->head->next->prev = myList->tail;
    }

    // increment the length.
    myList->length++;
}

// function to insert at rear of the linked list.
void insertAtRear(circularDoubleLinkedList *myList, int data)
{
    // check whetehr empty and is circular .
    if (!isEmpty(myList))
    {
        if (!isCircular(myList))
        {
            // if not empty and not circular, to maintain ciruclarity return by printing message.
            printf("List isn't circular.\n");
            return;
        }
        // if it isn't the case, then rear and head remaains the same so as to call insert at head fn().
    }
    else
        return insertAtHead(myList, data);

    // create a newnode and if alloated inatilase.
    node *newNode = createNode(data);

    // then find the tail pointer and update accordingly.

    // adjust the new node to the rear part.
    newNode->prev = myList->tail;
    myList->tail->next = newNode;

    // make the new node as new tail.
    myList->tail = newNode;

    // make it circular.
    myList->tail->next = myList->head->next;
    myList->head->next->prev = myList->tail;

    // increment the lenght.
    myList->length++;
}

// function to insert at any given position.
void insertAtPosition(circularDoubleLinkedList *myList, int data, int position)
{
    // check whether the list is circular.
    if (!isEmpty(myList) && !isCircular(myList))
    {
        printf("List isn't circular. Insertion failed.\n");
        return;
    }

    // check if the position is head or rear if so call corresponding fn.
    if (position <= 0)
        return insertAtHead(myList, data);
    if (position >= myList->length)
        return insertAtRear(myList, data);
    /* consider anything below zero and above length as head and rear parts since the list is circular.
    or you can directly ignore by printing invalid position to insert.*/

    // create a new node, if allocated initalise.
    node *newNode = createNode(data);

    // having a pointer to traverse go to the just before desired position.
    node *temp = myList->head->next;
    for (int i = 0; i < position - 1; i++)
        temp = temp->next;

    // add the newnode and change links prev and next.
    // connect the newnodes links.
    newNode->next = temp->next;
    newNode->prev = temp;

    //  connect the newnode.
    temp->next->prev = newNode; // make sure to change the link of the inital temp's next node' prev which was pointing to temp
    temp->next = newNode;       // connect the next of temp to new node.

    // increment the length.
    myList->length++;
}

// function to delete at head.
int deleteAtHead(circularDoubleLinkedList *myList)
{
    // check whether it is empty, if empty return.
    if (isEmpty(myList))
    {
        printf("No elements to delete.");
        return -1;
    }
    else
    {
        // if it isn't empty then check circularity if circular proceed else return with error msg.
        if (!isCircular(myList))
        {
            printf("List isn't circular.\n");
            return -1;
        }
    }
    // special case if the list contains only one element.
    if (myList->length == 1)
    {
        int data = myList->head->next->data;
        free(myList->head->next);
        initCircularDoubleLinkedList(myList);
        return data;
    }

    // take the todelete pointer and extract data.
    node *toDelete = myList->head->next;
    int data = toDelete->data;

    // change the head to new head.(immediate next node).
    myList->head->next = toDelete->next;

    // make it circular by updating the links since head has changed.
    myList->tail->next = myList->head->next;
    myList->head->next->prev = myList->tail;

    // delete the head.
    free(toDelete);

    // decrement the length along return the data.
    myList->length--;
    return data;
}

// function to delete at rear part of the linked list.
int deleteAtRear(circularDoubleLinkedList *myList)
{
    // check whether the list is valid for deletion.
    if (isEmpty(myList))
    {
        printf("No elements to delete.\n");
        return -1;
    }
    else
    {
        if (!isCircular(myList))
        {
            printf("List isn't circular.\n");
            return -1;
        }
    }

    // special case if the list contains only one element.
    if (myList->length == 1)
    {
        int data = myList->tail->data;
        free(myList->tail);
        initCircularDoubleLinkedList(myList);
        return data;
    }

    // get the pointer to the rear part.
    node *toDelete = myList->tail;

    // befor procedding check whether it is the only node, if so call delete at head fn.
    if (!toDelete->prev)
        return deleteAtHead(myList);

    int data = toDelete->data; // extract the data.

    // change the links...
    myList->tail = toDelete->prev;
    myList->tail->next = myList->head->next;
    myList->head->next->prev = myList->tail;

    free(toDelete); // delete the memory.

    // decrement the length and return.
    myList->length--;
    return data;
}

// function to delete at given position of the linkedlist.
int deleteAtPosition(circularDoubleLinkedList *myList, int position)
{
    // check if it is a valid list.
    if (!isCircular(myList))
    {
        printf("List isn't circular.\n");
        return -1;
    }
    if (isEmpty(myList))
    {
        printf("No elements to delete.\n");
        return -1;
    }

    // if position is a head.
    if (position <= 0)
        return deleteAtHead(myList);
    // if position belongs to rear.
    if (position >= myList->length)
        return deleteAtRear(myList);

    // using a temp pointer move to the desired position.
    node *temp = myList->head->next;
    for (int i = 0; i < position - 1; i++)
        temp = temp->next;

    // extract the data from the to be deleted element.
    node *toDelete = temp->next;
    int data = toDelete->data;

    // change the links.
    temp->next = toDelete->next;
    toDelete->next->prev = temp;

    // delete the memory decrease the lenght and return the data.
    free(toDelete);
    myList->length--;
    return data;
}

// function to return the address of the node if the key is present.
node *searchByKey(const circularDoubleLinkedList *myList, int key)
{
    // check is it valid list or not.
    if (isEmpty(myList))
    {
        printf("No elements to search.\n");
        return NULL;
    }
    else
    {
        if (!isCircular(myList))
        {
            printf("List isn't circular. Search incompatible.\n");
            return NULL;
        }
    }

    // using a pointer traverse while traversing serach the key if present return else slide through.
    node *temp = myList->head->next;
    do
    {
        if (temp->data == key)
        {
            printf("Element found.\n");
            return temp;
        }
        else
            temp = temp->next;
    } while (temp != myList->head->next);

    // upon successful traversing if you didn't find the element return null with a msg.
    printf("Element not found.\n");
    return NULL;
}

// function to delete by key.
int deleteByKey(circularDoubleLinkedList *myList, int key)
{
    // check whether the given list is valid.
    if (isEmpty(myList))
    {
        printf("No elements to delete.\n");
        return -1;
    }
    else
    {
        if (!isCircular(myList))
        {
            printf("List isn't circular. Deletion incompatible.\n");
            return -1;
        }
    }

    // take out the pointer from the serach funtion.
    node *toDelete = searchByKey(myList, key);

    if (!toDelete)
    { // if it is null directly return msg is printed once by serach function if found.
        return -1;
    }

    // check by any chance the key belongs to rear or head part.
    if (toDelete == myList->head->next)
        return deleteAtHead(myList);
    if (toDelete == myList->tail)
        return deleteAtRear(myList);

    // if it isn't head or tail take out the data.
    int data = toDelete->data;

    // this is the advantage of double lineked list without traversing and finding the node of the todelete we can delete.

    // change the links with prev and next, skip that position.
    toDelete->prev->next = toDelete->next;
    toDelete->next->prev = toDelete->prev;

    // free the  memeory and return the data along decreaseing the lenght.
    free(toDelete);
    myList->length--;
    return data;
}

// functiont to check whether it is sorted or not.
int isSorted(const circularDoubleLinkedList *myList)
{
    if (!isCircular(myList) || isEmpty(myList))
    {
        return 0; // Not sorted or not circular
    }

    node *temp = myList->head->next;
    do
    {
        if (temp->data <= temp->next->data)
        {
            temp = temp->next;
        }
        else
        {
            return 0; // List is not sorted
        }
    } while (temp->next != myList->head->next);

    return 1; // List is sorted
}

// function to create a ordered list.
void createOrderedList(circularDoubleLinkedList *myList, int data)
{
    // check whether the list is empty or the data is the least.
    if (isEmpty(myList) || data <= myList->head->next->data)
    {
        return insertAtHead(myList, data);
    }
    // check whether the data is the highest.
    if (data >= myList->tail->data)
    {
        return insertAtRear(myList, data);
    }

    // if wanted we can add a sort check in between and if needed sort the linked list and then proceed.

    // create a newnode if it isn't least or highest, if allocated initalise.
    node *newNode = createNode(data);

    // using a pointer find the position where the data fits in order.
    node *temp = myList->head->next;
    while (temp->next->data < newNode->data)
        temp = temp->next;

    // change the links to insert the data.
    newNode->next = temp->next;
    temp->next = newNode;
    temp->next->prev = newNode;
    newNode->prev = temp;

    // increment the length.
    myList->length++;
}

// function to reverse the linked list.
void reverse(circularDoubleLinkedList *myList)
{
    if (!isEmpty(myList) && !isCircular(myList))
    {
        printf("List isn't circualr. Reversal incompatible.\n");
        return;
    } // empty list or single element list is consdiered reversed.(returns the same.)

    // have three pointers.
    node *current = myList->head->next;
    node *prev = myList->tail;
    node *next;

    // traverse along
    do
    {
        // store the next
        next = current->next;

        // reverse the links.
        current->next = prev;
        current->prev = next;

        // slide through.
        prev = current;
        current = next;
    } while (current != myList->head->next);

    // update the head and tail.
    myList->head->next = myList->tail;
    myList->tail = current;
}

// function to copy the list to a new list and return the copy.
circularDoubleLinkedList *copyList(const circularDoubleLinkedList *original)
{
    // create a new list named copy and iniatlised.
    circularDoubleLinkedList *copy = initCircularDoubleLinkedList();

    // check whether the list is empty if empty return the intialised list.
    if (isEmpty(original))
        return copy;

    // have a pointer on origianl list and traverse along traversing insert the data at rear part of the list.
    node *temp = original->head->next;
    do
    {
        insertAtRear(copy, temp->data);
        temp = temp->next;
    } while (temp != original->head);

    // upon copying return the list.
    return copy;
}

// function to display.
void display(const circularDoubleLinkedList *myList)
{
    // checking whether the list is empty
    if (isEmpty(myList))
    {
        printf("No elements to display.\n");
        return;
    }

    // checking whether the given list is circular or not.
    if (!isCircular(myList))
    {
        printf("Linked list isn't circular. Operation failed.\n");
        return;
    }

    node *temp = myList->head->next;

    /*Using the temp pointer we traverse along the linked list until we find again the head of the linked list.(note the usage
    of do-while loop).*/
    printf("Elements of the linked list are,\n");
    do
    {
        printf("%d<=>", temp->data);
        temp = temp->next;
    } while (temp != myList->head->next);
    printf("%d\n", myList->head->next->data);
    // above intedentation is to look like ex.(1->2->3->1).
}