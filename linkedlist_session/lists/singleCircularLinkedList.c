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
typedef struct node
{
    int data;
    struct node *next;
} Node;

// structure for linkedlist.
typedef struct
{
    struct node *head;
    int length;
} linkedListCircular;

// function to check whether the linkedlist is emptpy. (type int returns 1(true) if empty else 0(false))
int isEmpty(const linkedListCircular *myList)
{
    return !(myList->head->next && myList->length);
    /*this corresponds to the condition (myList->head->next == NULL && myList->length == 0) a boolean condtion where
    if both are true returns 1 the empty condtion and vice-versa*/
}

// function to confirm whether the linkedlist is circular or not.
// returns 1(true) and 0(false) being int in return.
int isCircular(const linkedListCircular *);

// function to check whether the function is sorted.
int isSorted(const linkedListCircular *);

// initalisation functions for Node and linkedlist.
void initNode(Node *, int);
linkedListCircular *initLinkedList();
Node *createNode(int);

// Insertion functions.
void insertAtHead(linkedListCircular *, int);
void insertAtRear(linkedListCircular *, int);
void insertAtPosition(linkedListCircular *, int, int);

// deletion functions.
/*Delete functions return the value that got deleted.*/
int deleteAtHead(linkedListCircular *);
int deleteAtRear(linkedListCircular *);
int deleteAtPosition(linkedListCircular *, int);

// operation on keys.
Node *searchByKey(const linkedListCircular *, int);
int deleteByKey(linkedListCircular *, int);

// operations on linkedlist.
void createOrderedList(linkedListCircular *, int);
void reverse(linkedListCircular *);
linkedListCircular *copyList(const linkedListCircular *);

// display function.
void display(const linkedListCircular *);

// destructing function for allocated momory.
void destructList(linkedListCircular *myList)
{
    Node *temp = myList->head->next;
    while (temp != myList->head->next)
    {
        Node *next = temp->next;
        free(temp);
        temp = next;
    }
    free(myList->head);
    free(myList);
}

int main()
{
    linkedListCircular *myList = initLinkedList();
    linkedListCircular *copy;
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
            insertAtHead(myList, data);
            printf("\n\n");
            display(myList);
            break;
        case 2:
            printf("Enter data to insert at rear: ");
            scanf("%d", &data);
            insertAtRear(myList, data);
            printf("\n\n");
            display(myList);
            break;
        case 3:
            printf("Enter data to insert: ");
            scanf("%d", &data);
            printf("Enter position to insert at: ");
            scanf("%d", &position);
            insertAtPosition(myList, data, position);
            printf("\n\n");
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
            printf("\n\n");
            display(myList);
            break;
        case 7:
            printf("Enter key to delete: ");
            scanf("%d", &key);
            deleteByKey(myList, key);
            printf("\n\n");
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
            printf("\n\n");
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
    destructList(copy);
    return 0;
}

// function to create a node.
Node *createNode(int data)
{
    // create new Node initalise
    Node *newNode = (Node *)malloc(sizeof(Node));
    // check whether allocated.
    if (!newNode)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    initNode(newNode, data);
    return newNode;
}

// function to initalise linkedlist with head pointing to null and length zero.
linkedListCircular *initLinkedList()
{
    linkedListCircular *list = (linkedListCircular *)malloc(sizeof(linkedListCircular));
    if (!list)
    {
        printf("Memeory allocation failed.\n");
        exit(1);
    }
    list->head = createNode(0);
    list->head->next = NULL;
    list->length = 0;
    return list;
}

// function to initalise Node with data and pointer pointing to itself.
void initNode(Node *Node, int data)
{
    Node->data = data;
    Node->next = Node; // since circular it points to itself.
}

// function to check whether the given linkedlist is circular or not.
int isCircular(const linkedListCircular *myList)
{
    // An empty list is not considerd circular.
    if (isEmpty(myList))
    {
        printf("Empty list isn't considered circular.\n");
        return 0; // false.
    }

    Node *slow = myList->head->next; // tortoise
    Node *fast = myList->head->next; // hare

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
void insertAtHead(linkedListCircular *myList, int data)
{
    // checks whether the linkedlist is empty or not.
    if (!isEmpty(myList))
    {
        // if not empty and not circular you cannot insert head to a normal linkedlist.
        if (!isCircular(myList))
        {
            printf("List isn't circular being not empty, Operation failed.\n");
            return;
        }
        // if not circular and empty insert the head because empty list aren't circular.
    }

    Node *newNode = createNode(data);

    // linkedlist head is null or empty make the newnode as head since intalisation makes it point to itself.
    if (isEmpty(myList))
    {
        myList->head->next = newNode;
        myList->length++;
        return;
    }
    else
        newNode->next = myList->head->next; // if it isn't empty just add the head part to the newnode's next.

    Node *temp = myList->head->next;

    // upon insertion the linked list turns linear with a loop so as to make it circular.

    // we access the last element.
    while (temp->next != myList->head->next)
    {
        temp = temp->next;
    }
    // change the link and form a loop and make it circular.
    temp->next = newNode;

    // change the head since newnode becomes the new head.
    myList->head->next = newNode;
    // increment the length due to insertion.
    myList->length++;
}

// function to insert at rear of the linkedlist.
void insertAtRear(linkedListCircular *myList, int data)
{
    // check whether the list is empty or not.
    if (!isEmpty(myList))
    {
        // if not empty check whether it isn't circular
        if (!isCircular(myList))
        {
            // to maintain circularity print a message and return.
            printf("List isn't circular, insertion failed.\n");
            return;
        }
    }
    else
    {
        // if empty insert this as a head Node or a single Node since insertion at rear becomes equal to insertion at head.
        return insertAtHead(myList, data);
    }

    Node *newNode = createNode(data);

    // find the last Node which makes it circular.
    Node *temp = myList->head->next;

    while (temp->next != myList->head->next)
    {
        temp = temp->next;
    }
    // make the newnode as last Node.
    temp->next = newNode;
    // make it circular.
    newNode->next = myList->head->next;

    myList->length++;
    // increment the length.
}

void insertAtPosition(linkedListCircular *myList, int data, int position)
{
    // check the list is empty or not
    if (!isEmpty(myList))
    {
        // if not empty check whether it is circular.
        if (!isCircular(myList))
        {
            // if isn't circular so as to maintain circularity print and return.
            printf("List isn't circular. Insertion.\n");
            return;
        }
    }
    // if the position is less than 0 treat them as insertion at head.
    if (position <= 0)
        return insertAtHead(myList, data);

    // if the position is greater than length of the linkedlist consider them as insertion at rear.
    if (position >= myList->length)
        return insertAtRear(myList, data);

    Node *newNode = createNode(data);

    // create a temp pointer reach upto the just before desired position.
    Node *temp = myList->head->next;
    for (int i = 0; i < position - 1; i++)
        temp = temp->next;

    // update the pointers to insert new Node at that position.
    newNode->next = temp->next;
    temp->next = newNode;

    // increment the length.
    myList->length++;
}

int deleteAtHead(linkedListCircular *myList)
{
    // if empty we can't delete.
    if (isEmpty(myList))
    {
        printf("No elements to delete\n");
        return -1;
    }
    else
    {
        // if not empty check whether it isn't circular
        if (!isCircular(myList))
        {
            // if it isn't circular print msg and return since to maintain circularity
            printf("List isn't circular. Deletion failed.\n");
            return -1;
        }
    }

    // take out the data of the head.
    int data = myList->head->next->data;
    // store the new head's address.
    Node *newHead = myList->head->next->next;

    // traverse until the last Node.
    Node *temp = myList->head->next;

    if (temp->next == myList->head->next)
    {
        free(myList->head->next);
        myList->head->next = NULL;
        myList->length--;
        return data;
    }

    while (temp->next != myList->head->next)
    {
        temp = temp->next;
    }

    // make it circular by connecting it into new head.
    temp->next = newHead;
    free(myList->head->next); // delete old head.

    // make new head as list's head.
    if (newHead)
        myList->head->next = newHead;

    // decrement the length and return the data.
    myList->length--;
    return data;
}

// function to delete at rear of the linked list.
int deleteAtRear(linkedListCircular *myList)
{
    // checks whether it is emtpy.
    if (isEmpty(myList))
    {
        printf("No elements to delete.\n");
        return -1;
    }
    else
    {
        // if not empty checks whether it isn't circular.
        if (!isCircular(myList))
        {
            // if not circular, deletion gets incompatible so returns with a error msg.
            printf("List isn't circular. Deletion is incompatible.\n");
            return -1;
        }
    }

    // traverse until last-second Node.
    Node *temp = myList->head->next;

    // added edge case where the list conatins only one element.
    if (temp->next == myList->head->next)
        return deleteAtHead(myList);

    while (temp->next->next != myList->head->next)
    {
        temp = temp->next;
    }

    // take the last Node to todelete extract data.
    Node *toDelete = temp->next;
    int data = toDelete->data;

    // change the link of the last-second Node(new rear element) to head of list to maintian circularity.
    temp->next = myList->head->next;
    free(toDelete); // alongside delete the Node.

    // alongside decrement the length of the list with returning the data.
    myList->length--;
    return data;
}

// function to delete at given position in a linked list.
int deleteAtPosition(linkedListCircular *myList, int position)
{
    // check whether it is empty.
    if (isEmpty(myList))
    {
        printf("No elements to delete.\n");
        return -1;
    }
    else
    {
        // check if it is circular.
        if (!isCircular(myList))
        {
            // if it isn't to maintain circularity return with a erro msg.
            printf("List isn't circular. Deletion incompatible.\n");
            return -1;
        }
    }

    // check the validity of position.

    // if the position is less than or equal to zero considered it as head.
    if (position <= 0)
        return deleteAtHead(myList);

    // if the position is greater or equal to length of list then consider it as tail (rear).
    if (position >= myList->length)
        return deleteAtRear(myList);

    // if it lies in the range take a pointer and move upto desired position.
    Node *temp = myList->head->next;
    for (int i = 0; i < position - 1; i++)
        temp = temp->next;

    // take out the address and extract data of the element at that position.
    Node *toDelete = temp->next;
    int data = toDelete->data;

    // change the links (skip the to be deleted element).
    temp->next = toDelete->next;
    free(toDelete);

    // decrement the length and return the data.
    myList->length--;
    return data;
}

// function to search a key and return the address(Node's).
Node *searchByKey(const linkedListCircular *myList, int key)
{
    // as usual check whether it is empty and circular.
    if (isEmpty(myList))
    {
        printf("No elements to search.\n");
        return NULL;
    }
    else
    {
        if (!isCircular(myList))
        {
            // if not empty and not circular print msg and return.
            printf("List isn't circular, Search is incompatible.\n");
            return NULL;
        }
    }

    // traverse the linked list alongside checking whether it is equal to key.
    Node *temp = myList->head->next;

    do
    {
        if (temp->data == key)
        {
            printf("Element found.\n");
            return temp;
        }
        temp = temp->next;
    } while (temp != myList->head->next);

    printf("No element found.\n");
    return NULL;
}

// function to delete the key present in a linkedlist.
int deleteByKey(linkedListCircular *myList, int key)
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

    // access the Node fromt the search fn
    Node *toDelete = searchByKey(myList, key);

    // if the fn returns null then print element not found to delete and return.
    if (!toDelete)
    {
        printf("Element not found. Deletion failed.\n");
        return -1;
    }

    // if present, extract the data.
    int data = toDelete->data;
    // then check whether it is head.
    if (toDelete == myList->head->next)
        return deleteAtHead(myList);

    // similarly check whether it is rear element(last). since circular the condition corrsponds to last ele.
    if (toDelete->next == myList->head->next)
        return deleteAtRear(myList);

    // it isn't the head or rear then, you can either fetch the Node and return or count the position and call deletebyposition fn.
    Node *temp = myList->head->next;
    // here we find the Node just before the Node having the key is found.
    while (temp->next != myList->head->next && temp->next != toDelete)
    {
        temp = temp->next;
    }

    // the links are changed as if it is skipped(deleted).
    temp->next = toDelete->next;
    free(toDelete); // deallocate the memory.

    // decrement the length and return the data.
    myList->length--;
    return data;
}

// function to check whether the list is sorted in ascending order or not.
int isSorted(const linkedListCircular *myList)
{
    // if the list is empty return as true (sorted).
    if (isEmpty(myList))
    {
        return 1;
    }

    // using temp pointer check whether every pair is in sorted order.
    Node *temp = myList->head->next;
    do
    {
        // if any found as not sorted return false.
        if (temp->data > temp->next->data)
        {
            return 0;
        }
        temp = temp->next;
    } while (temp != myList->head->next && temp->next != NULL);

    // if it gets out of the loop it means the list is sorted in ascending order.
    return 1;
}

// function to create a ordered list.
void createOrderedList(linkedListCircular *myList, int data)
{
    // check whether the list is valid.
    if (!isEmpty(myList))
    {
        if (!isCircular(myList))
        {
            printf("List isn't circular. Insertion failed.\n");
            return;
        }
    }
    else
    {
        // if it is empty insert at head.
        return insertAtHead(myList, data);
    }

    /*If wanted we can add the isSorted condition to maintain proper working of this function.*/

    // suppose the data is the least, insert at head.
    if (data < myList->head->next->data)
        return insertAtHead(myList, data);

    // suppose the data is not the least or the largest find its position.
    int position = 0;
    Node *temp = myList->head->next;

    do
    {
        if (data > temp->data)
        {
            temp = temp->next;
            position++;
        }
        else
        {
            // upon finding its position insert.
            return insertAtPosition(myList, data, position);
        }
    } while (temp != myList->head->next);

    // suppose if it is the highest. (only comes out of loop if it is highest). insert at rear.
    return insertAtRear(myList, data);
}

// function to reverse the linkedlist.
void reverse(linkedListCircular *myList)
{
    // if the list is empty or either the list conatins only one element the list is already reversed.
    if (isEmpty(myList) || myList->length == 1)
    {
        return;
    }

    // have three pointers.
    Node *current = myList->head->next;
    Node *prev = NULL;
    Node *next;

    // change links along traversing.
    do
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    } while (current != myList->head->next);

    // do paperwork to realise.
    /*It is similar to reversing a normal linked list olny thing is to make it circular upon reversal.
    as shown in the next fwe lines.*/

    // update the head since rear element now becomes head.
    myList->head->next->next = prev;
    myList->head->next = prev;
}

// function to copy the list to another list and return.
linkedListCircular *copyList(const linkedListCircular *myList)
{
    linkedListCircular *copy = initLinkedList();
    // create a structure for storing copy and return with initalisation.

    // added is list is empty condition so not to throw garbage value.
    if (isEmpty(myList))
    {
        return copy;
    }

    Node *orginalHead = myList->head->next;
    // with the pointer upon the orginal list.
    do
    {
        // upon traversing fetch the data and insert in the copy list alongside.
        insertAtRear(copy, orginalHead->data);
        orginalHead = orginalHead->next;
    } while (orginalHead != myList->head->next);

    // upon successfull copying return the copy.
    return copy;
}

void display(const linkedListCircular *myList)
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

    Node *temp = myList->head->next;

    /*Using the temp pointer we traverse along the linked list until we find again the head of the linked list.(note the usage
    of do-while loop).*/
    printf("Elements of the linked list are,\n");
    do
    {
        printf("%d->", temp->data);
        temp = temp->next;
    } while (temp != myList->head->next);
    printf("%d\n", myList->head->next->data);
    // above intedentation is to look like ex.(1->2->3->1).
}