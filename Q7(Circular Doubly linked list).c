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
struct node
{
    int data;
    struct node *next;
    struct node *prev;
};

// structure to store the double linkedlist's head and tail and its length.
struct circularDoubleLinkedList
{
    struct node *head;
    struct node *tail;
    int length;
};

// function to check conditions.
int isEmpty(struct circularDoubleLinkedList l);
int isCircular(struct circularDoubleLinkedList l);
int isSorted(struct circularDoubleLinkedList l);

// function to initalise the node and list.
void initNode(struct node *Node, int data);
void initCircularDoubleLinkedList(struct circularDoubleLinkedList *l);

// function to insert.
void insertAtHead(struct circularDoubleLinkedList *l, int data);
void insertAtRear(struct circularDoubleLinkedList *l, int data);
void insertAtPosition(struct circularDoubleLinkedList *l, int data, int position);

// functions to delete.
int deleteAtHead(struct circularDoubleLinkedList *l);
int deleteAtRear(struct circularDoubleLinkedList *l);
int deleteAtPosition(struct circularDoubleLinkedList *l, int position);

// operation on keys.
struct node *searchByKey(struct circularDoubleLinkedList l, int key);
int deleteByKey(struct circularDoubleLinkedList *l, int key);

// other operatins.
void createOrderedList(struct circularDoubleLinkedList *l, int data);
void reverse(struct circularDoubleLinkedList *l);
struct circularDoubleLinkedList copyList(struct circularDoubleLinkedList l);

// display function.
void display(struct circularDoubleLinkedList l);

int main()
{
    struct circularDoubleLinkedList l;
    initCircularDoubleLinkedList(&l);
    struct circularDoubleLinkedList copy;
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
            insertAtHead(&l, data);
            display(l);
            break;
        case 2:
            printf("Enter data to insert at rear: ");
            scanf("%d", &data);
            insertAtRear(&l, data);
            display(l);
            break;
        case 3:
            printf("Enter data to insert: ");
            scanf("%d", &data);
            printf("Enter position to insert at: ");
            scanf("%d", &position);
            insertAtPosition(&l, data, position);
            display(l);
            break;
        case 4:
            deleteAtHead(&l);
            display(l);
            break;
        case 5:
            deleteAtRear(&l);
            display(l);
            break;
        case 6:
            printf("Enter position to delete: ");
            scanf("%d", &position);
            deleteAtPosition(&l, position);
            display(l);
            break;
        case 7:
            printf("Enter key to delete: ");
            scanf("%d", &key);
            deleteByKey(&l, key);
            display(l);
            break;
        case 8:
            printf("Enter key to search: ");
            scanf("%d", &key);
            searchByKey(l, key);
            break;
        case 9:
            printf("Enter data to insert in the ordered list: ");
            scanf("%d", &data);
            createOrderedList(&l, data);
            display(l);
            break;
        case 10:
            reverse(&l);
            printf("Reversed list is,\n");
            display(l);
            break;
        case 11:
            copy = copyList(l);
            display(l);
            printf("Copied list is,\n");
            display(copy);
            break;
        case 12:
            display(l);
            break;
        case 13:
            printf("Exiting the program....\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
    } while (choice != 13);
    return 0;
}

// function to initalise nodes.
void initNode(struct node *Node, int data)
{
    Node->data = data;
    Node->next = Node;
    Node->prev = Node;
}

// function to initalise linked list.
void initCircularDoubleLinkedList(struct circularDoubleLinkedList *l)
{
    l->head = NULL;
    l->tail = NULL;
    l->length = 0;
}

// function to check whether the list is empty or not.
int isEmpty(struct circularDoubleLinkedList l)
{
    return !(l.length && l.head && l.tail);
}

// function to check whether the given list is circular or not.
int isCircular(struct circularDoubleLinkedList l)
{
    if (isEmpty(l))
    {
        return 0;
        // empty list isn't circular.
    }

    // check whether the head and tail are valid pointers.
    if (!l.head || !l.tail)
        return 0;

    /*If not using tail pointer, then you have to try a different approach.*/

    // if you are using a tail pointer then obivously tail's next and head's prev should pointing to each other.
    if (l.head->prev != l.tail || l.tail->next != l.head)
        return 0;
    else
        return 1;
}

// function to insert at head of the linkedlist.
void insertAtHead(struct circularDoubleLinkedList *l, int data)
{
    // check whether the list is circular, if not to maintain circularity return.
    if (!isCircular(*l))
    {
        // again check whether the list is not emtpy if it isn't empty and not circular then print.
        if (!isEmpty(*l))
        {
            printf("List isn't circular.\n");
            return;
        }
        // if it is empty insert the head since empty list is always consdiered not circular.
        // so the order of the 2 if conditon can be reversed but works the same.
    }

    // create a new node, if allocated iniatlise.
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    if (!newNode)
    {
        printf("Memory allocation failed.\n");
        return;
    }
    else
        initNode(newNode, data);

    // check whether the list is empty that is head is null.
    if (!l->head)
    {
        // if so insert the head. no other changes required.
        l->head = newNode;
        l->tail = newNode;
    }
    else
    {
        // if the list is already present and you have to insert, then

        // adjust the new node's next and and old head's prev to new node.
        newNode->next = l->head;
        l->head->prev = newNode;
        // make the newnode as head.
        l->head = newNode;

        // make it circular by changing the links of the tail and head pointer. (which was previously pointing to old head).
        l->tail->next = l->head;
        l->head->prev = l->tail;
    }

    // increment the length.
    l->length++;
}

// function to insert at rear of the linked list.
void insertAtRear(struct circularDoubleLinkedList *l, int data)
{
    // check whetehr empty and is circular .
    if (!isEmpty(*l))
    {
        if (!isCircular(*l))
        {
            // if not empty and not circular, to maintain ciruclarity return by printing message.
            printf("List isn't circular.\n");
            return;
        }
        // if it isn't the case, then rear and head remaains the same so as to call insert at head fn().
    }
    else
        return insertAtHead(l, data);

    // create a newnode and if alloated inatilase.
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    if (!newNode)
    {
        printf("Memory allcoation failed.\n");
        return;
    }
    else
        initNode(newNode, data);

    // then find the tail pointer and update accordingly.

    // adjust the new node to the rear part.
    newNode->prev = l->tail;
    l->tail->next = newNode;

    // make the new node as new tail.
    l->tail = newNode;

    // make it circular.
    l->tail->next = l->head;
    l->head->prev = l->tail;

    // increment the lenght.
    l->length++;
}

// function to insert at any given position.
void insertAtPosition(struct circularDoubleLinkedList *l, int data, int position)
{
    // check whether the list is circular.
    if (!isEmpty(*l) && !isCircular(*l))
    {
        printf("List isn't circular. Insertion failed.\n");
        return;
    }

    // check if the position is head or rear if so call corresponding fn.
    if (position <= 0)
        return insertAtHead(l, data);
    if (position >= l->length)
        return insertAtRear(l, data);
    /* consider anything below zero and above length as head and rear parts since the list is circular.
    or you can directly ignore by printing invalid position to insert.*/

    // create a new node, if allocated initalise.
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    if (!newNode)
    {
        printf("Memory allcation failed.\n");
        return;
    }
    else
        initNode(newNode, data);

    // having a pointer to traverse go to the just before desired position.
    struct node *temp = l->head;
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
    l->length++;
}

// function to delete at head.
int deleteAtHead(struct circularDoubleLinkedList *l)
{
    // check whether it is empty, if empty return.
    if (isEmpty(*l))
    {
        printf("No elements to delete.");
        return -1;
    }
    else
    {
        // if it isn't empty then check circularity if circular proceed else return with error msg.
        if (!isCircular(*l))
        {
            printf("List isn't circular.\n");
            return -1;
        }
    }
    // special case if the list contains only one element.
    if (l->length == 1)
    {
        int data = l->head->data;
        free(l->head);
        initCircularDoubleLinkedList(l);
        return data;
    }

    // take the todelete pointer and extract data.
    struct node *toDelete = l->head;
    int data = toDelete->data;

    // change the head to new head.(immediate next node).
    l->head = toDelete->next;

    // make it circular by updating the links since head has changed.
    l->tail->next = l->head;
    l->head->prev = l->tail;

    // delete the head.
    free(toDelete);

    // decrement the length along return the data.
    l->length--;
    return data;
}

// function to delete at rear part of the linked list.
int deleteAtRear(struct circularDoubleLinkedList *l)
{
    // check whether the list is valid for deletion.
    if (isEmpty(*l))
    {
        printf("No elements to delete.\n");
        return -1;
    }
    else
    {
        if (!isCircular(*l))
        {
            printf("List isn't circular.\n");
            return -1;
        }
    }

    // special case if the list contains only one element.
    if (l->length == 1)
    {
        int data = l->tail->data;
        free(l->tail);
        initCircularDoubleLinkedList(l);
        return data;
    }

    // get the pointer to the rear part.
    struct node *toDelete = l->tail;

    // befor procedding check whether it is the only node, if so call delete at head fn.
    if (!toDelete->prev)
        return deleteAtHead(l);

    int data = toDelete->data; // extract the data.

    // change the links...
    l->tail = toDelete->prev;
    l->tail->next = l->head;
    l->head->prev = l->tail;

    free(toDelete); // delete the memory.

    // decrement the length and return.
    l->length--;
    return data;
}

// function to delete at given position of the linkedlist.
int deleteAtPosition(struct circularDoubleLinkedList *l, int position)
{
    // check if it is a valid list.
    if (!isCircular(*l))
    {
        printf("List isn't circular.\n");
        return -1;
    }
    if (isEmpty(*l))
    {
        printf("No elements to delete.\n");
        return -1;
    }

    // if position is a head.
    if (position <= 0)
        return deleteAtHead(l);
    // if position belongs to rear.
    if (position >= l->length)
        return deleteAtRear(l);

    // using a temp pointer move to the desired position.
    struct node *temp = l->head;
    for (int i = 0; i < position - 1; i++)
        temp = temp->next;

    // extract the data from the to be deleted element.
    struct node *toDelete = temp->next;
    int data = toDelete->data;

    // change the links.
    temp->next = toDelete->next;
    toDelete->next->prev = temp;

    // delete the memory decrease the lenght and return the data.
    free(toDelete);
    l->length--;
    return data;
}

// function to return the address of the node if the key is present.
struct node *searchByKey(struct circularDoubleLinkedList l, int key)
{
    // check is it valid list or not.
    if (isEmpty(l))
    {
        printf("No elements to search.\n");
        return NULL;
    }
    else
    {
        if (!isCircular(l))
        {
            printf("List isn't circular. Search incompatible.\n");
            return NULL;
        }
    }

    // using a pointer traverse while traversing serach the key if present return else slide through.
    struct node *temp = l.head;
    do
    {
        if (temp->data == key)
        {
            printf("Element found.\n");
            return temp;
        }
        else
            temp = temp->next;
    } while (temp != l.head);

    // upon successful traversing if you didn't find the element return null with a msg.
    printf("Element not found.\n");
    return NULL;
}

// function to delete by key.
int deleteByKey(struct circularDoubleLinkedList *l, int key)
{
    // check whether the given list is valid.
    if (isEmpty(*l))
    {
        printf("No elements to delete.\n");
        return -1;
    }
    else
    {
        if (!isCircular(*l))
        {
            printf("List isn't circular. Deletion incompatible.\n");
            return -1;
        }
    }

    // take out the pointer from the serach funtion.
    struct node *toDelete = searchByKey(*l, key);

    if (!toDelete)
    { // if it is null directly return msg is printed once by serach function if found.
        return -1;
    }

    // check by any chance the key belongs to rear or head part.
    if (toDelete == l->head)
        return deleteAtHead(l);
    if (toDelete == l->tail)
        return deleteAtRear(l);

    // if it isn't head or tail take out the data.
    int data = toDelete->data;

    // this is the advantage of double lineked list without traversing and finding the node of the todelete we can delete.

    // change the links with prev and next, skip that position.
    toDelete->prev->next = toDelete->next;
    toDelete->next->prev = toDelete->prev;

    // free the  memeory and return the data along decreaseing the lenght.
    free(toDelete);
    l->length--;
    return data;
}

// functiont to check whether it is sorted or not.
int isSorted(struct circularDoubleLinkedList l)
{
    if (!isCircular(l) || isEmpty(l))
    {
        return 0; // Not sorted or not circular
    }

    struct node *temp = l.head;
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
    } while (temp->next != l.head);

    return 1; // List is sorted
}

// function to create a ordered list.
void createOrderedList(struct circularDoubleLinkedList *l, int data)
{
    // check whether the list is empty or the data is the least.
    if (isEmpty(*l) || data <= l->head->data)
    {
        return insertAtHead(l, data);
    }
    // check whether the data is the highest.
    if (data >= l->tail->data)
    {
        return insertAtRear(l, data);
    }

    // if wanted we can add a sort check in between and if needed sort the linked list and then proceed.

    // create a newnode if it isn't least or highest, if allocated initalise.
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    if (!newNode)
    {
        printf("Memory allocation failed.\n");
        return;
    }
    else
        initNode(newNode, data);

    // using a pointer find the position where the data fits in order.
    struct node *temp = l->head;
    while (temp->next->data < newNode->data)
        temp = temp->next;

    // change the links to insert the data.
    newNode->next = temp->next;
    temp->next = newNode;
    temp->next->prev = newNode;
    newNode->prev = temp;

    // increment the length.
    l->length++;
}

// function to reverse the linked list.
void reverse(struct circularDoubleLinkedList *l)
{
    if (!isEmpty(*l) && !isCircular(*l))
    {
        printf("List isn't circualr. Reversal incompatible.\n");
        return;
    } // empty list or single element list is consdiered reversed.(returns the same.)

    // have three pointers.
    struct node *current = l->head;
    struct node *prev = l->tail;
    struct node *next;

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
    } while (current != l->head);

    // update the head and tail.
    l->head = l->tail;
    l->tail = current;
}

// function to copy the list to a new list and return the copy.
struct circularDoubleLinkedList copyList(struct circularDoubleLinkedList original)
{
    // create a new list named copy and iniatlised.
    struct circularDoubleLinkedList copy;
    initCircularDoubleLinkedList(&copy);

    // check whether the list is empty if empty return the intialised list.
    if (isEmpty(original))
        return copy;

    // have a pointer on origianl list and traverse along traversing insert the data at rear part of the list.
    struct node *temp = original.head;
    do
    {
        insertAtRear(&copy, temp->data);
        temp = temp->next;
    } while (temp != original.head);

    // upon copying return the list.
    return copy;
}

// function to display.
void display(struct circularDoubleLinkedList l)
{
    // checking whether the list is empty
    if (isEmpty(l))
    {
        printf("No elements to display.\n");
        return;
    }

    // checking whether the given list is circular or not.
    if (!isCircular(l))
    {
        printf("Linked list isn't circular. Operation failed.\n");
        return;
    }

    struct node *temp = l.head;

    /*Using the temp pointer we traverse along the linked list until we find again the head of the linked list.(note the usage
    of do-while loop).*/
    printf("Elements of the linked list are,\n");
    do
    {
        printf("%d<=>", temp->data);
        temp = temp->next;
    } while (temp != l.head);
    printf("%d\n", l.head->data);
    // above intedentation is to look like ex.(1->2->3->1).
}