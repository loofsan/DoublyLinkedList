//
//  DoublyLinkedList.h
//
//  Blank version of file for assignment
//
//  Created by Katz, Ariel on 2/14/23.
//
//  Lynn T. Aung
//  3-10-2024
// 

#ifndef DoublyLinkedList_h
#define DoublyLinkedList_h

#include "ListType.h"

using namespace std;

template <class Type>
class DoublyLinkedList: public ListType<Type> {
public:
    
    void print(bool forward) const ;
      //Function to output the data contained in each node.
      //If argument is true list prints forward
    // If forward is false list prints in reverse
    
    bool search(const Type& searchItem) const;
      //Function to determine whether searchItem is in the list.
      // Returns true if searchItem is in the

    void insertFirst(const Type& newItem);
      //Function to insert newItem at the beginning of the list.
      //newItem becomes head and count is incremented by 1.

    void insertLast(const Type& newItem);
      //Function to insert newItem at the end of the list.
      //newItem becomes tail and count is incremented by 1.
    
    void insertNode(const Type& newItem, int index);
      //Function to insert newItem at the given index.
    // If index is out of range print error
      //newItem becomes element at index and all other elements are shifted.
    // count is incremented by one.

    void deleteNode(const Type& deleteItem);
      //Function to delete deleteItem from the list.
      //Postcondition: If found, the node containing
      //               deleteItem is deleted from the list
      //               and count is decremented by 1.
    
};

template <class Type>
void DoublyLinkedList<Type>::print(bool forward) const
{
    NodeType<Type> *current; //pointer to traverse the list
    if (forward){
        current = this->head;    //start traversal from the head node
        while (current != NULL) //while more data to print
        {
            cout << current->data << " ";
            current = current->next;
        }
    } else {
        current = this->tail;    //start traversal from the tail node
        while (current != NULL) //while more data to print
        {
            cout << current->data << " ";
            current = current->prev;
        }
    }
    
}

template <class Type>
bool DoublyLinkedList<Type>::
                   search(const Type& searchItem) const
{
    NodeType<Type> *current; //pointer to traverse the list
    current = this->head; //start search at the beginning

    //as long as there is more to search
    //and the node hasn't been found - keep searching
    while (current != NULL )
        if (current->data == searchItem)
            return true;
        else{
            current = current->next; //step forward
        }
            
    return NULL;
}//end search

template <class Type>
void DoublyLinkedList<Type>::insertFirst(const Type& newItem){
    
    // Make a new node and add data
    NodeType<Type> *newNode = new NodeType<Type>;
    newNode->data = newItem;
    newNode->prev = NULL;

    if (this->count == 0) {
        this->head = newNode;
        newNode->next = NULL;
    } 
    else {
        // Assign next ptr and replace the head
        this->head->prev = newNode; 
        newNode->next = this->head;
        this->head = newNode;
    }

    this->count++;
}

template <class Type>
void DoublyLinkedList<Type>::insertLast(const Type& newItem){
    
    //Make a new node ptr
    NodeType<Type> *newNode = new NodeType<Type>;
    newNode->data = newItem;
    newNode->next = NULL;

    if (this->count == 0) {
        insertFirst(newItem);
    } 
    else {

        //Make current ptr and traverse
        NodeType<Type> *current;
        current = this->head;
        while(current->next != NULL) {

            current = current->next;
        }

        current->next = newNode;
        newNode->prev = current;
        this->tail = newNode;

        this->count++;

    }

}

template <class Type>
void DoublyLinkedList<Type>::insertNode(const Type& newItem, int index){

    // Edge Case 1: Index Not In Bound
    if (index < 0 || index > this->count) {
        cout << "Error: Index Out Of Range" << endl;
        return;
    }

    NodeType<Type> *newNode = new NodeType<Type>;
    newNode->data = newItem;

    // Edge Case 2: Index is the start
    if (index == 0) {
        insertFirst(newItem);
        return;
    }

    // Traverse with current 
    NodeType<Type> *current = this->head;
    for (int i = 0; i < index - 1; i++) {
        current = current->next;
    }

    newNode->next = current->next;
    newNode->prev = current;
    if (current->next != NULL) {
        current->next->prev = newNode;
    }
    current->next = newNode;

    if (index == this->count) {
        this->tail = newNode;
    }

    this->count++;
}

template <class Type>
void DoublyLinkedList<Type>::deleteNode(const Type& deleteItem) {

    // Edge Case 1: List Empty
    if (this->head == NULL) {
        cout << "Error: List is empty" << endl;
        return;
    }

    // Delete Head Node
    if (this->head->data == deleteItem) {
        NodeType<Type> *temp = this->head;
        this->head = this->head->next;
        if (this->head != NULL) {
            this->head->prev = NULL;
        } else {
            this->tail = NULL; 
        }
        delete temp;
        this->count--;
        return;
    }

    // Make current ptr and traverse
    NodeType<Type> *current = this->head;
    while (current != NULL && current->data != deleteItem) {
        current = current->next;
    }

    // Edge Case 2: Node with Data isn't found
    if (current == NULL) {
        cout << "Error: Node not found" << endl;
        return;
    }

    // Continue with the normal swap
    current->prev->next = current->next;
    if (current->next != NULL) {
        current->next->prev = current->prev;
    } else {
        this->tail = current->prev; 
    }
    delete current;
    this->count--;
}

#endif /* DoublyLinkedList_h */
