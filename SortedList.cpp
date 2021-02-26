#include <iostream>
using namespace std;
#include "SortedList.h"

template <class ItemType>
SortedList<ItemType>::SortedList()
// No argument constructor
// Pre: None
// Post: List is initialized
{
    Length = 0;
    listData = NULL;
}

template <class ItemType>
SortedList<ItemType>::~SortedList()
// Class Deconstructor
// Deallocates all dynamically allocated data members
// Pre: List is initialized
{
    makeEmpty();
}

template <class ItemType>
bool SortedList<ItemType>::isEmpty() const
// Determines whether the list is empty
// Pre: List is initialized
// Post: Returns true if empty, false otherwise
{
    if(listData == NULL) {
        return true;
    } else {
        return false;
    }
}

template <class ItemType>
bool SortedList<ItemType>::isFull() const
// Determines if the list is full (memory is full)
// Pre: List is initialized
// Post: Returns true if there is no memory space to allocate a new node,
// flase otherwise
{
    Node<ItemType>* location;
    try
    {
        location = new Node<ItemType>;
        delete location;
        return false;
    }
    catch(const std::bad_alloc&)
    {
        return true;
    }
}

template <class ItemType>
int SortedList<ItemType>::getLength() const
// Returns numbet of elements in the list in O(1) time complexity
// Pre: List is initialized
// Post: Function value equals number of list elements
{
    return Length;
}

template <class ItemType>
void SortedList<ItemType>::makeEmpty()
// Deallocates all dynamically allocated data members.
// Reinitializes the list to empty state.
// Pre: None
// Post: List is empty.
{
    Node<ItemType>* tempPtr;
    while (listData != NULL)
    {
        tempPtr = listData;
        listData = listData->next;
        delete tempPtr;
    }
    Length = 0;
}

template <class ItemType>
ItemType SortedList<ItemType>::getAt(int index)
// Returns the element at specified position (index) int this list.
// Pre: List is initialiazed
// Post: Returns the element at index or throws IndexOutOfBoundsException
{
    if (index < 1 || index > Length) {
        throw OutOfBound();
    }

    // create pointer p and iterate through list index times and return info at
    // that spot
    Node<ItemType>* p = listData;
    for (int i = 1; i < index; i++) {
        p = p->next;
    }
    return p->info;
}

template <class ItemType>
void SortedList<ItemType>::putItem(ItemType newItem)
// Adds a new element to list. No duplicates and checks if space is avaliable
// to add a new element
// Pre: List is initialized
// Post: newItem is in the list if newItem's key was not in the list
// and throws exception of key is found, order is also conserved
{
    if (isFull()){
        throw FullList();
        return;
    }

    Node<ItemType>* predecessor = NULL;
    if (findItem(newItem, predecessor)) {
        throw DuplicateItem();
        return;
    }
    Node<ItemType>* newNode = new Node<ItemType>;
    newNode->info = newItem;
    // pred is NULL if the list is empty or item is smaller than listData->info
    // thus newNode should be set to the front
    if (predecessor == NULL) {
        newNode->next = listData;
        listData = newNode;
    } else {
        newNode->next = predecessor->next;
        predecessor->next = newNode;
    }
    Length++;
}

template <class ItemType>
void SortedList<ItemType>::deleteItem(ItemType item)
// Removes an element from the list using findItem
// Pre: List is initialized
// Post: item is not in the list
// exception is thrown if item was not found in the list
{
    Node<ItemType>* predecessor;
    Node<ItemType>* toBeDeleted;

    if (isEmpty()) {
        throw EmptyList();
        return;
    }

    bool found = findItem(item, predecessor);
    if (found == false) {
        throw DeletingMissingItem();
    }

    if (predecessor == NULL)
    {
        toBeDeleted = listData;
        listData = listData -> next;
    } else {
        toBeDeleted = predecessor -> next;
        if (toBeDeleted->next != NULL) {
            predecessor->next = toBeDeleted->next;
        } else {
            predecessor->next = NULL;
        }
    }
    delete toBeDeleted;
    Length--;
}

template <class ItemType>
void SortedList<ItemType>::printList(ofstream& outFile)
// Prints list elements
// Pre: list is initialized
// Post: list elements are written to the output file outFile
{
    outFile << "List Items: ";
    Node<ItemType>* p = listData;
    for (int i = 0; i < Length; i++) {
        outFile << p->info << "->";
        if (p->next != NULL){
            p = p->next;
        }
    }
    outFile<<"NULL \n";
}

template <class ItemType>
void SortedList<ItemType>::merge(SortedList& otherList)
// Merges the current list and otherList while mainting sortedness
// Pre: List is initialized. otherList is initialized and sorted
// Post: Function returns current list after inserting all elements of
// otherLost. Current list is sorted and with no duplicate keys.
// otherList is empty.
{
    // check if og list is empty
    if (listData == NULL) {
        listData = otherList.listData;
        Length = otherList.Length;
        otherList.listData = NULL;
        otherList.Length = 0;
        return;
    }

    //check if otherList is empty
    if (otherList.listData == NULL) {
        return;
    }

    Node<ItemType>* p = listData;
    Node<ItemType>* q = otherList.listData;
    Node<ItemType>* current;

    Length = Length + otherList.Length;
    otherList.Length = 0;

    if (p->info < q->info) {
        listData = p; // head
        current = p;
        p = p->next;
    } else if (p->info > q->info) {
        listData = q; // head
        current = q;
        q = q->next;
    } else {
        // p and q are equal, we will make p head
        listData = p;
        current = p;
        p = p-> next;
        Node<ItemType>* temp = q;
        q = q->next;
        delete temp;
        Length--;
    }

    while (p != NULL && q != NULL) {
        if (p->info < q->info){
            current->next = p;
            p = p->next;
            current = current->next;
        } else if(p->info > q->info){
            current->next = q;
            q = q->next;
            current = current->next;
        } else { //p and q are equal so set p and skip q
            current->next = p;
            p = p->next;
            Node<ItemType>* temp = q;
            q = q->next;
            delete temp;
            current = current->next;
            Length--;
        }
    }

    if (p == NULL) {
        current->next = q;
    }

    if (q == NULL) {
        current->next = p;
    }

    otherList.listData = NULL;
}

template <class ItemType>
bool SortedList<ItemType>::findItem(ItemType item, Node<ItemType>*& predecessor)
// Searches the list for item and returns a pointer to the item's
// predecessor node.
// Pre: list is initialized
// Post: (1) if item is in the list, function value = true
//       (2) if the item is not in the list, function value is false
//       (3) predecessor contains the address of item's predecessor node
//           if no predecessor exist, predecessor is set to NULL
{
    predecessor = NULL;
    if (listData == NULL || item < listData->info) {
        return false;
    }

    if (item == listData->info) {
        return true;
    }

    if (isFull()){
        throw FullList();
        return false;
    }

    Node<ItemType>* location;
    location = listData;
    bool found = false;

    if (Length == 1 && item > listData->info) {
        predecessor = location;
        return false;
    }

    while (location->next != NULL) { // && !found) {
        if (item == location->next->info ) {
            found = true;
            predecessor = location;
            return found;
        } else if(item < location->next->info){
            found = false;
            predecessor = location;
            return found;
        } else {
            location = location->next;
            predecessor = location;
        }
    }
    return found;
}
