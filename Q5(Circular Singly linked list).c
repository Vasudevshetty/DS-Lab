/*Develop a menu driven programme to implement circular singly linked list with various operations such as
i) Insertion and Deletion at front/rear
ii) Insertion and Deletion at the specified position
iii) Delete by Key
iv) Search by key
v) Create an ordered list
vi) Reverse a list
vii) Creating a copy of the list*/

#include <stdio.h>
#include <stdlib.h>

// structure for nodes, having its data and pointer to next.
struct node
{
    int data;
    struct node *next;
};

// structure for linkedlist.
struct linkedListCircular
{
    struct node *head;
    int length;
};

// function to check whether the linkedlist is emptpy. (type int returns 1(true) if empty else 0(false))
int isEmpty(struct linkedListCircular l)
{
    return !(l.head && l.length);
    /*this corresponds to the condition (l.head == NULL && l.length == 0) a boolean condtion where
    if both are true returns 1 the empty condtion and vice-versa*/
}

// function to confirm whether the linkedlist is circular or not.
// returns 1(true) and 0(false) being int in return.
int isCircular(struct linkedListCircular l);

// function to check whether the function is sorted.
int isSorted(struct linkedListCircular l);

// initalisation functions for node and linkedlist.
void initNode(struct node *Node, int data);
void initLinkedList(struct linkedListCircular *l);

// Insertion functions.
void insertAtHead(struct linkedListCircular *l, int data);
void insertAtRear(struct linkedListCircular *l, int data);
void insertAtPosition(struct linkedListCircular *l, int data, int position);

// deletion functions.
/*Delete functions return the value that got deleted.*/
int deleteAtHead(struct linkedListCircular *l);
int deleteAtRear(struct linkedListCircular *l);
int deleteAtPosition(struct linkedListCircular *l, int position);

// operation on keys.
struct node *searchByKey(struct linkedListCircular l, int key);
int deleteByKey(struct linkedListCircular *l, int key);

// operations on linkedlist.
void createOrderedList(struct linkedListCircular *l, int data);
void reverse(struct linkedListCircular *l);
struct linkedListCircular copyList(struct linkedListCircular orginal);

// display function.
void display(struct linkedListCircular l);

int main()
{
    struct linkedListCircular l;
    initLinkedList(&l);
    struct linkedListCircular copy;
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
        printf("6. Delete from specific position/\n");
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
            printf("\n\n");
            display(l);
            break;
        case 2:
            printf("Enter data to insert at rear: ");
            scanf("%d", &data);
            insertAtRear(&l, data);
            printf("\n\n");
            display(l);
            break;
        case 3:
            printf("Enter data to insert: ");
            scanf("%d", &data);
            printf("Enter position to insert at: ");
            scanf("%d", &position);
            insertAtPosition(&l, data, position);
            printf("\n\n");
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
            printf("\n\n");
            display(l);
            break;
        case 7:
            printf("Enter key to delete: ");
            scanf("%d", &key);
            deleteByKey(&l, key);
            printf("\n\n");
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
            printf("\n\n");
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

// function to initalise linkedlist with head pointing to null and length zero.
void initLinkedList(struct linkedListCircular *l)
{
    l->head = NULL;
    l->length = 0;
}

// function to initalise node with data and pointer pointing to itself.
void initNode(struct node *Node, int data)
{
    Node->data = data;
    Node->next = Node; // since circular it points to itself.
}

// function to check whether the given linkedlist is circular or not.
int isCircular(struct linkedListCircular l)
{
    // An empty list is not considerd circular.
    if (isEmpty(l))
    {
        printf("Empty list isn't considered circular.\n");
        return 0; // false.
    }

    struct node *slow = l.head; // tortoise
    struct node *fast = l.head; // hare

    // fast poniter moves 2 steps at a time.
    // slow pointer moves 1 step at a time.

    while (fast && slow)
    {
        fast = fast->next->next;
        slow = slow->next;

        // if the list is circular the fast and slow pointer at some point becomes same(meet).
        if (fast == slow)
        {
            return 1; // true.
        }
    }

    // if it isn't.
    printf("List isn't circular.\n");
    return 0;
}

// function to insert at head of the linkedlist.
void insertAtHead(struct linkedListCircular *l, int data)
{
    // checks whether the linkedlist is empty or not.
    if (!isEmpty(*l))
    {
        // if not empty and not circular you cannot insert head to a normal linkedlist.
        if (!isCircular(*l))
        {
            printf("List isn't circular being not empty, Operation failed.\n");
            return;
        }
        // if not circular and empty insert the head because empty list aren't circular.
    }

    // create new node initalise
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    // check whether allocated.
    if (!newNode)
    {
        printf("Memory allocation failed.\n");
        return;
    }
    initNode(newNode, data);

    // linkedlist head is null or empty make the newnode as head since intalisation makes it point to itself.
    if (!l->head)
        l->head = newNode;
    else
        newNode->next = l->head; // if it isn't empty just add the head part to the newnode's next.
    struct node *temp = l->head;

    // upon insertion the linked list turns linear with a loop so as to make it circular.

    // we access the last element.
    while (temp->next != l->head)
    {
        temp = temp->next;
    }
    // change the link and form a loop and make it circular.
    temp->next = newNode;

    // change the head since newnode becomes the new head.
    l->head = newNode;
    // increment the length due to insertion.
    l->length++;
}

// function to insert at rear of the linkedlist.
void insertAtRear(struct linkedListCircular *l, int data)
{
    // check whether the list is empty or not.
    if (!isEmpty(*l))
    {
        // if not empty check whether it isn't circular
        if (!isCircular(*l))
        {
            // to maintain circularity print a message and return.
            printf("List isn't circular, insertion failed.\n");
            return;
        }
    }
    else
    {
        // if empty insert this as a head node or a single node since insertion at rear becomes equal to insertion at head.
        return insertAtHead(l, data);
    }

    // create a newNode and check alloation if allocated initalise.
    struct node *newNode = (struct node *)malloc(sizeof(struct node));

    if (!newNode)
    {
        printf("Memory allocation failed.\n");
        return;
    }
    initNode(newNode, data);

    // find the last node which makes it circular.
    struct node *temp = l->head;

    while (temp->next != l->head)
    {
        temp = temp->next;
    }
    // make the newnode as last node.
    temp->next = newNode;
    // make it circular.
    newNode->next = l->head;

    l->length++;
    // increment the length.
}

void insertAtPosition(struct linkedListCircular *l, int data, int position)
{
    // check the list is empty or not
    if (!isEmpty(*l))
    {
        // if not empty check whether it is circular.
        if (!isCircular(*l))
        {
            // if isn't circular so as to maintain circularity print and return.
            printf("List isn't circular. Insertion.\n");
            return;
        }
    }
    // if the position is less than 0 treat them as insertion at head.
    if (position <= 0)
        return insertAtHead(l, data);

    // if the position is greater than length of the linkedlist consider them as insertion at rear.
    if (position >= l->length)
        return insertAtRear(l, data);

    // create a new node check it's allocation and if allocated inatilase.
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    if (!newNode)
    {
        printf("Memory allocation failed. Insertion failed.\n");
        return;
    }
    initNode(newNode, data);

    // create a temp pointer reach upto the just before desired position.
    struct node *temp = l->head;
    for (int i = 0; i < position - 1; i++)
        temp = temp->next;

    // update the pointers to insert new node at that position.
    newNode->next = temp->next;
    temp->next = newNode;

    // increment the length.
    l->length++;
}

int deleteAtHead(struct linkedListCircular *l)
{
    // if empty we can't delete.
    if (isEmpty(*l))
    {
        printf("No elements to delete\n");
        return -1;
    }
    else
    {
        // if not empty check whether it isn't circular
        if (!isCircular(*l))
        {
            // if it isn't circular print msg and return since to maintain circularity
            printf("List isn't circular. Deletion failed.\n");
            return -1;
        }
    }

    // take out the data of the head.
    int data = l->head->data;
    // store the new head's address.
    struct node *newHead = l->head->next;

    // traverse until the last node.
    struct node *temp = l->head;
    while (temp->next != l->head)
    {
        temp = temp->next;
    }

    // make it circular by connecting it into new head.
    temp->next = newHead;
    free(l->head); // delete old head.

    // make new head as list's head.
    l->head = newHead;

    // decrement the length and return the data.
    l->length--;
    return data;
}

// function to delete at rear of the linked list.
int deleteAtRear(struct linkedListCircular *l)
{
    // checks whether it is emtpy.
    if (isEmpty(*l))
    {
        printf("No elements to delete.\n");
        return -1;
    }
    else
    {
        // if not empty checks whether it isn't circular.
        if (!isCircular(*l))
        {
            // if not circular, deletion gets incompatible so returns with a error msg.
            printf("List isn't circular. Deletion is incompatible.\n");
            return -1;
        }
    }

    // traverse until last-second node.
    struct node *temp = l->head;
    while (temp->next->next != l->head)
    {
        temp = temp->next;
    }

    // take the last node to todelete extract data.
    struct node *toDelete = temp->next;
    int data = toDelete->data;

    // change the link of the last-second node(new rear element) to head of list to maintian circularity.
    temp->next = l->head;
    free(toDelete); // alongside delete the node.

    // alongside decrement the length of the list with returning the data.
    l->length--;
    return data;
}

// function to delete at given position in a linked list.
int deleteAtPosition(struct linkedListCircular *l, int position)
{
    // check whether it is empty.
    if (isEmpty(*l))
    {
        printf("No elements to delete.\n");
        return -1;
    }
    else
    {
        // check if it is circular.
        if (!isCircular(*l))
        {
            // if it isn't to maintain circularity return with a erro msg.
            printf("List isn't circular. Deletion incompatible.\n");
            return -1;
        }
    }

    // check the validity of position.

    // if the position is less than or equal to zero considered it as head.
    if (position <= 0)
        return deleteAtHead(l);

    // if the position is greater or equal to length of list then consider it as tail (rear).
    if (position >= l->length)
        return deleteAtRear(l);

    // if it lies in the range take a pointer and move upto desired position.
    struct node *temp = l->head;
    for (int i = 0; i < position - 1; i++)
        temp = temp->next;

    // take out the address and extract data of the element at that position.
    struct node *toDelete = temp->next;
    int data = toDelete->data;

    // change the links (skip the to be deleted element).
    temp->next = toDelete->next;
    free(toDelete);

    // decrement the length and return the data.
    l->length--;
    return data;
}

// function to search a key and return the address(node's).
struct node *searchByKey(struct linkedListCircular l, int key)
{
    // as usual check whether it is empty and circular.
    if (isEmpty(l))
    {
        printf("No elements to search.\n");
        return NULL;
    }
    else
    {
        if (!isCircular(l))
        {
            // if not empty and not circular print msg and return.
            printf("List isn't circular, Search is incompatible.\n");
            return NULL;
        }
    }

    // traverse the linked list alongside checking whether it is equal to key.
    struct node *temp = l.head;

    do
    {
        if (temp->data == key)
        {
            printf("Element found.\n");
            return temp;
        }
        temp = temp->next;
    } while (temp != l.head);

    printf("No element found.\n");
    return NULL;
}

// function to delete the key present in a linkedlist.
int deleteByKey(struct linkedListCircular *l, int key)
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

    // access the node fromt the search fn
    struct node *toDelete = searchByKey(*l, key);

    // if the fn returns null then print element not found to delete and return.
    if (!toDelete)
    {
        printf("Element not found. Deletion failed.\n");
        return -1;
    }

    // if present, extract the data.
    int data = toDelete->data;
    // then check whether it is head.
    if (toDelete == l->head)
        return deleteAtHead(l);

    // similarly check whether it is rear element(last). since circular the condition corrsponds to last ele.
    if (toDelete->next == l->head)
        return deleteAtRear(l);

    // it isn't the head or rear then, you can either fetch the node and return or count the position and call deletebyposition fn.
    struct node *temp = l->head;
    // here we find the node just before the node having the key is found.
    while (temp->next != l->head && temp->next == toDelete)
    {
        temp = temp->next;
    }

    // the links are changed as if it is skipped(deleted).
    temp->next = toDelete->next;
    free(toDelete); // deallocate the memory.

    // decrement the length and return the data.
    l->length--;
    return data;
}

// function to check whether the list is sorted in ascending order or not.
int isSorted(struct linkedListCircular l)
{
    // if the list is empty return as true (sorted).
    if (isEmpty(l))
    {
        return 1;
    }

    // using temp pointer check whether every pair is in sorted order.
    struct node *temp = l.head;
    do
    {
        // if any found as not sorted return false.
        if (temp->data > temp->next->data)
        {
            return 0;
        }
        temp = temp->next;
    } while (temp != l.head);

    // if it gets out of the loop it means the list is sorted in ascending order.
    return 1;
}

// function to create a ordered list.
void createOrderedList(struct linkedListCircular *l, int data)
{
}

// function to reverse the linkedlist.
void reverse(struct linkedListCircular *l)
{
    // if the list is empty or either the list conatins only one element the list is already reversed.
    if (isEmpty(*l) || l->length == 1)
    {
        return;
    }

    // have three pointers.
    struct node *current = l->head;
    struct node *prev = NULL;
    struct node *next;

    // change links along traversing.
    do
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    } while (current != l->head);

    // do paperwork to realise.
    /*It is similar to reversing a normal linked list olny thing is to make it circular upon reversal.
    as shown in the next fwe lines.*/

    // update the head since rear element now becomes head.
    l->head->next = prev;
    l->head = prev;
}

// function to copy the list to another list and return.
struct linkedListCircular copyList(struct linkedListCircular l)
{

    struct linkedListCircular copy;
    initLinkedList(&copy);
    // create a structure for storing copy and return with initalisation.

    struct node *orginalHead = l.head;
    // with the pointer upon the orginal list.
    do
    {
        // upon traversing fetch the data and insert in the copy list alongside.
        insertAtRear(&copy, orginalHead->data);
        orginalHead = orginalHead->next;
    } while (orginalHead != l.head);

    // upon successfull copying return the copy.
    return copy;
}

void display(struct linkedListCircular l)
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
        printf("%d->", temp->data);
        temp = temp->next;
    } while (temp != l.head);
    printf("%d\n", l.head->data);
    // above intedentation is to look like ex.(1->2->3->1).
}