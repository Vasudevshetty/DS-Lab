/*Develop a menu driven program to implment a singly linked list with various operations such as,
i) Insertion and deletion from front/rear.
ii) Insertion and Deletion at specific position.
iii) Delete by key. iv) Search by key.
v) Create a ordered list.
vi) Reverse a list.
vii) Creating a copy of list.*/

/*Note when structure is passed as a refernce it encounters changes since the orginal stucture's pointer is passed, whereas
when it is passed as a value, it just creates a local copy of it and no changes are encountered.*/

#include <stdio.h>
#include <stdlib.h>

// structure for the nodes of linked list which contains data and a pointer to the next Node as its members.
typedef struct node
{
    int data;
    struct node *next;
}Node;

// structure of linkedlist with Node pointer of the head of the linkedlist(first Node) and its length.
typedef struct
{
    Node *head;
    int length;
} linkedList;

// function to check whether the linkedlist is emptpy. (type int returns 1(true) if empty else 0(false))
int isEmpty(linkedList *l)
{
    return !(l->head->next && l->length);
    /*this corresponds to the condition (l.head == NULL && l.length == 0) a boolean condtion where
    if both are true returns 1 the empty condtion and vice-versa*/
}

// function to check whether the function is sorted.
int isSorted(linkedList *l);

// initalisation functions for Node and linkedlist.
Node *createNode(int data);
void initNode(Node *Node, int data);
linkedList* initLinkedList();

// Insertion functions.
void insertAtHead(linkedList *l, int data);
void insertAtRear(linkedList *l, int data);
void insertAtPosition(linkedList *l, int data, int position);

// deletion functions.
/*Delete functions return the value that got deleted.*/
int deleteAtHead(linkedList *l);
int deleteAtRear(linkedList *l);
int deleteAtPosition(linkedList *l, int position);

// operation on keys.
Node *searchByKey(linkedList *l, int key);
int deleteByKey(linkedList *l, int key);

// operations on linkedlist.
void createOrderedList(linkedList *l, int data);
void reverse(linkedList *l);
linkedList* copyList(linkedList *orginal);

// display function.
void display(linkedList *l);

// destructor function for memory allocated using malloc.
void destructLinkedList(linkedList *l){
    Node* temp = l->head->next;
    while(temp){
        Node* next = temp->next;
        free(temp);
        temp = next;
    }
    l->head->next = NULL;
}

int main()
{
    linkedList *l = initLinkedList();
    linkedList *copy;
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
            deleteAtHead(l);
            display(l);
            break;
        case 5:
            deleteAtRear(l);
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
            searchByKey(&l, key);
            display(l);
            break;
        case 9:
            printf("Enter data to insert in the ordered list: ");
            scanf("%d", &data);
            createOrderedList(&l, data);
            display(l);
            break;
        case 10:
            reverse(l);
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
            printf("Exiting the program.\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
    } while (choice != 13);
    
    //deallocate the memmory for the list.
    destructLinkedList(l);
    free(l);

    return 0;
}

// function to create Node and return the address of the Node.
Node *createNode(int data)
{
    // create a new Node and check whether the memory allocation is done or not.
    Node *newNode = (Node *)malloc(sizeof(Node));
    //(newNode == NULL) this is the condition.
    if (!newNode)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    // initalise the allocated new Node.
    initNode(newNode, data);
    return newNode;
}

// function to initalise with the data given where its pointer(next) is always set to null.
void initNode(Node *node, int data)
{
    node->data = data;
    node->next = NULL;
}

// function to initalise the linkedlist with null and length zero instead of garbage dump.
linkedList* initLinkedList()
{
    linkedList *l = (linkedList*) malloc (sizeof(linkedList));
    if(!l){
        printf("Memory allcocation failed.\n");
        exit(1);
    }
    // default head for further purpose.
    l->head = createNode(0);
    l->length = 0;
    return l;
}

// function to insert at head of the linkedlist(first Node.).
void insertAtHead(linkedList *l, int data)
{
    Node *newNode = createNode(data);

    // set the newNode's next to current head if there exits already a linkedlist.
    newNode->next = l->head->next;
    // else case is taken care of by the initNode function initalising newNode's next to null
    // set the head's next of the linkedlist as the new Node.
    l->head->next = newNode;
    // increment the length of the linkedlist.
    l->length++;
}

// function to insert a Node at rear end of the linkedlist.
void insertAtRear(linkedList *l, int data)
{
    // A pointer temperary variable used to traverse along the linkedlist.
    Node *temp = l->head->next;

    // if the head is null or the linkedlist is empty condtion. calling the insertAtHead fun.
    if (isEmpty(l))
    {
        insertAtHead(l, data);
        return;
    }

    // move the temp variable(slide along) until you find the null.
    while (temp != NULL && temp->next != NULL)
    {
        temp = temp->next;
    }

    Node *newNode = createNode(data);

    // set the temp (last Node)'s next pointer to newNode.
    temp->next = newNode;

    // increment the length variable.
    l->length++;
}

// function to insert at specific position.
void insertAtPosition(linkedList *l, int data, int position)
{
    // checking whether the given position given is valid or not.
    if (position < 0 || position > l->length)
    {
        printf("Invalid position to insert. Please enter a valid one.\n");
        return;
        /*There are two possiblities to deal here, either to ignore and prompt for a valid position.
        or to insert at rear by passing the linkedlist and data to the insertAtRear().*/
        // I have ignored and prompting for a valid position.
    }

    Node *newNode = createNode(data);

    Node *temp = l->head->next;

    // dealing with the head case.
    if (position == 0)
    {
        newNode->next = temp;
        l->head->next = newNode;
    }
    else
    {
        // moving towards the position using pointer.
        for (int i = 0; i < position - 1; i++)
            temp = temp->next;
        if (temp)
        {
            /*if(temp) corressponds to temp != NULL. i.e if temp == NULL the value is a zero which is false
            anything other than true is considered as true.*/

            newNode->next = temp->next;
            temp->next = newNode;
        }
        // performing change of links correctly.
    }
    // incrementing the length of the linkedlist by one.
    l->length++;
}

// function to delete the head of the linkedlist.
int deleteAtHead(linkedList *l)
{
    // checking whether the list is empty.
    if (isEmpty(l))
    {
        printf("No elements to delete.\n");
        return -1;
    }

    // creating a pointer to store the toDelete element.
    Node *toDelete = l->head->next;
    // get the data of the element.
    int data = toDelete->data;
    // change the head of the element.
    l->head->next = toDelete->next;
    // delete the current head (todelete)
    free(toDelete);

    // decrement the length.
    l->length--;
    // check whether the length is zero if make the head of the linkedlist null. (linkedlist empty condition.)..
    if (l->length == 0)
        l->head->next = NULL;

    // return the data of the element deleted.
    return data;
}

// function to delete at rear of the linkedlist.
int deleteAtRear(linkedList *l)
{
    // check whether the linkedlist is empty.
    if (isEmpty(l))
    {
        printf("No elements to delete.\n");
        return -1;
    }

    // base case .. if the length = 1 or only head makes the entire linkedlist.
    if (l->length == 1)
    {
        int data = l->head->next->data;
        free(l->head->next);
        initLinkedList(l);
        return data;
    }

    // pointer to find the last element.
    Node *temp = l->head->next;

    // traverse (slide) until the second last element.
    while (temp->next->next)
    {
        // Note the condition (temp->next->next != NULL), we traverse until the last-second element not becomes null
        temp = temp->next;
    }

    /*upon exiting this loop we will have last second element's address(pointer) in temp variable.
      changing the last-sec element's next to null we actually lose the link of the rear(last) element and taking out the data we free it.
    */

    // create a Node to store the rear element's pointer.
    Node *toDelete = temp->next;
    // store the data of that element.
    int data = toDelete->data;
    // change the last-second element's next pointer to null.
    temp->next = NULL;
    // delete the rear element and due to the previous line manipulation the rear becomes last-second element (temp)
    free(toDelete);

    // decrement the length and return the deleted element's data.
    l->length--;
    return data;
}

// function to delete at a given position of the linkedlist.
int deleteAtPosition(linkedList *l, int position)
{

    // checking whether the given linkedlist is empty.
    if (isEmpty(l))
    {
        printf("No elements to delete.\n");
        return -1;
    }

    // checking whether the given position is valid or not.
    if (position < 0 || position > l->length)
    {
        printf("Not a valid position to delete.\n");
        return -1;
    }

    // if the position given is head (0th position.)
    if (position == 0)
        return deleteAtHead(l);

    Node *temp = l->head->next;
    // using the temp pointer reach to the position.

    for (int i = 0; i < position - 1; i++)
        temp = temp->next;

    // access the pointer of the position's element so as to free (delete.)
    Node *toDelete = temp->next;
    // change the links (skip the to be deleted element)
    temp->next = toDelete->next;
    // collect the data to return.
    int data = toDelete->data;
    // delete the element.
    free(toDelete);

    // decrement the length due to deletion and return the data of the deleted element.
    l->length--;
    return data;
}

// function to search a key and return the address of the Node(pointer)
/*This function's return value is intentionaly made Node pointer since it makes easier for the deleteByKey function easier. and it can
be even made as a message printing function or returning true(1) or false(0) functions too.*/
Node *searchByKey(linkedList *l, int key)
{
    // check whether the list is empty.
    if (isEmpty(l))
    {
        printf("No elements to search..\n");
        return NULL;
    }

    // pointer to traverse.
    Node *temp = l->head->next;
    // along traversing check whether the elements data matches key.
    while (temp)
    {
        if (temp->data == key)
        {
            printf("Element found.\n");
            return temp;
        }
        temp = temp->next;
    }

    // if upon complete traversing the element isn't found then print and return NULL.
    printf("Element not found.\n");
    return NULL;
}

// function to delete a element by having a key.
int deleteByKey(linkedList *l, int key)
{
    // get the Node from the searchByKey()
    Node *toDelete = searchByKey(l, key);

    // check if it is null it is either the element is empty or
    // the element is not found then print and return correspondingly.
    if (!toDelete)
    {
        printf("No element found to delete.\n");
        return -1;
    }

    // check the deletion conditions.
    if (toDelete == l->head->next)
    {
        // if it is head then just make the next element as head.
        l->head->next = toDelete->next;
    }
    else
    {
        Node *temp = l->head->next;

        // if it isn't the head, then traverse until the next element is toDelete (key containing element) or previous element to toDelete.
        while (temp && temp->next != toDelete)
        {
            temp = temp->next;
        }
        // check finally if the previous element to toDelete is not null to avoid dereferncing and if, then change the link.
        if (temp)
            temp->next = toDelete->next;
    }

    // collect the data and return while returning delete the memory for toDelete.
    int data = toDelete->data;
    free(toDelete);
    return data;
}

// function to check whether the linkedlist is sorted or not.
int isSorted(linkedList *l)
{
    Node *temp = l->head->next;

    // track the prev and next elements along checking whether they are sorted.
    while (temp && temp->next)
    {
        // if not sorted return false (0)
        if (temp->data < temp->next->data)
            temp = temp->next;
        else
            return 0;
    }
    // if the complete list is sorted then return true(1)
    return 1;
}

/*creation of linkedlist using this function must be a sorted list initally,
else the code doesn't work, it do work but operation will not be as intended.*/
// function to create ordered list. (acsending/sorted order).
void createOrderedList(linkedList *l, int data)
{
    // create a new Node and check whether the memory allocation is done or not.
    Node *newNode = (Node *)malloc(sizeof(Node));
    //(newNode == NULL) this is the condition.
    if (!newNode)
    {
        printf("Memory allocation failed.\n");
        return;
    }

    // ensure the linkedlist is sorted.
    if (isSorted(l))
    {

        // base case, where the length is 0 or the data is the least then insert at head.
        if (l->length == 0 || l->head->next->data >= data)
        {
            insertAtHead(l, data);
            return;
        }

        // initalise new Node.
        initNode(newNode, data);

        // using temp pointer slide through until you find the element which is lesser than the newNode's data.
        Node *temp = l->head->next;
        while (temp->next && temp->next->data < newNode->data)
        {
            temp = temp->next;
        }

        // change the links.
        newNode->next = temp->next;
        temp->next = newNode;

        // increment the length of the linkedlist.
        l->length++;
    }
    else
    {
        printf("Linkedlist is not sorted. Insertion failed.\n");
        return;
    }
}

// function to reverse a linkedlist.
void reverse(linkedList *l)
{

    if (isEmpty(l))
    {
        printf("No elements to reverse the linkedlist.\n");
        return;
    }
    // we have three pointers so as to manipulte the changes.
    Node *currentNode = l->head->next;
    Node *previousNode = NULL;
    Node *nextNode; // this remains unintalised.

    /*previousNode -> currentNode -> nextNode is the convenetional way we described. upon iterating inside the loop.
    we change this as nextNode->currentNode->previousNode.*/

    while (currentNode)
    {
        // initally we store the current Node's next pointer.
        nextNode = currentNode->next;

        // upon storing we then change the next pointer of the current Node to the previous Node.
        currentNode->next = previousNode;

        // then previous Node now becomes the currentnode.
        previousNode = currentNode;

        // then currentNode now becomes previous Node for the next iteration.
        currentNode = nextNode;
    }

    // this can be understood only with paperwork....

    // previousNode upon complete iteration becomes the new head.
    l->head->next = previousNode;
}

// function to create a copy of the linked list and return a new linkedlist.
linkedList* copyList(linkedList *orginal)
{
    linkedList *copy = initLinkedList(); // initalize the linkedlist.

    // traverse the orginal list and insert elements into the copy.
    Node *temp = orginal->head->next;
    while (temp)
    {
        insertAtRear(copy, temp->data); // insert each element to the rear of the linkedlist.
        temp = temp->next;
    }

    // return the copy linkedlist.
    return copy;
}

void display(linkedList *l)
{
    Node *temp = l->head->next;
    // keeping a pointer to slide through the linkedlist.

    // checking whether the linkedlist is empty or not.
    if (isEmpty(l))
    {
        printf("No elements to display..\n");
        return;
    }

    // sliding through the linkedlist using the pointer alongwise printing the elements.
    printf("Elements of the linked list are,\n");
    while (temp != NULL)
    {
        printf("%d->", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}
