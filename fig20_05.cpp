// Fig. 20.4: list.h
// Template List class definition
#ifndef _LIST_H
#define _LIST_H

#include <iostream>
#include <listnode.h>  // ListNode class definition

template<typename NODETYPE>
class List
{
  public:
  List(); // constructor
  ~List();  // destructor
  void insertAtFront(const NODETYPE & ); 
  void insertAtBack (const NODETYPE & );
  bool removeFromFront (NODETYPE & );
  bool removeFromBack (NODETYPE & );
  bool isEmpty() const;
  bool print() const;
  
  private:
  ListNode<NODETYPE> *firstPtr_; // pointer to first node
  ListNode<NODETYPE> *lastPtr_;  // pointer to last node  

// utility function to allocate new node
ListNode <NODETYPE> *getNewNode (const NODETYPE & );
}; // end class List

// default constructor
template<typename NODETYPE>
List<NODETYPE>::List()
  : firstPtr(0), lastPtr(0)
{
  
}

// destructor
List<NODETYPE>::~List()
{
  if (!isEmpty())
  {
   std::cout << "Destroying nodes...\n";
    
    ListNode<NODETYPE> *currentPtr = firstPtr_;
    List<NODETYPE> *tempPtr;
    
    while (currentPtr != 0) // delete remaining nodes
    {
      tempPtr = currentPtr;
      std::cout << tempPtr->data_ << '\n';
      currentPtr = currentPtr->nextPtr;
      delete tempPtr;
    } // end while
  } // end if
  
  std::cout << "All nodes destroyed\n\n";
} // end List destructor


// insert node at front of list
template <typename NODETYPE>
void List<NODETYPE>::insertAtFront(const NODETYPE &value)
{
  ListNode<NODETYPE> *newPtr = getNewNode(value); // new node
  
  if (isEmpty())
    firstPtr = lastPtr_ = newPtr; // new list has only one node
  else // list is not empty
  {
    newPtr->nextPtr = firstPtr_; // point new node to previous 1st node
    firstPtr_ = newPtr; // aim firstPtr at new node;
  } // end else
} // end function insertAtFront

// insert node at back of list
template <typename NODETYPE>
void List<NODETYPE>::insertAtBack(const NODETYPE &value)
{
  List<NODETYPE> *newPtr = getNewNode(value); // new node
  
  if (isEmpty()) // list is empty
    firstPtr = lastPtr = newPtr; // new list has only one node
  else
  {
    lastPtr_->nextPtr = newPtr; // updated previous last node
    lastPtr_ = newPtr; // new last node
  } // end else
} // end function insertAtBack

// delete node from front of list
template <typename NODETYPE>
 bool List<NODETYPE>::removeFromFront(NODETYPE &value)
 {
   if (isEmpty()) // List is empty
     return false; // delete unsuccessful
   else 
   {
     List<NODETYPE> *tempPtr = firstPtr_; // hold tempPtr to delete 
     
     if (firstPtr_ == lastPtr_) 
       firstPtr_ = lastPtr_ = 0; // no node remains after removal
     else
       firstPtr = firstPtr_->nextPtr; // point to previous 2nd node
     
     value = tempPtr->data_; // return data being removed
     delete tempPtr; // reclaim previous front node
     return true; // delete successful
   } // end else
 } // end function removeFromFront

// delete node from back of list
template <typename NODETYPE>
bool List<NODETYPE>::removeFromBack(NODETYPE &value)
{
  if (isEmpty()) // List is empty
    return false; // delete unsuccessful
  else
  {
    ListNode<NODETYPE> *tempPtr = lastPtr_; // hold tempPtr to delete
    
    if (firstPtr_ == lastPtr_) // List has one element
      firstPtr_ = lastPtr_ = 0; // no nodes remain after removal
    else
    {
      ListNode<NODETYPE> *currentPtr = firstPtr_; 
      
      // locate second-to-last element
      while (currentPtr->nextPtr != lastPtr_)
        currentPtr = currentPtr->nextPtr; // move to next node
      
      lastPtr_ = currentPtr; // remove last node
      currentPtr->nextPtr = 0; // this is now the the last node
    } // end else
    
    value = tempPtr->data_; // return value from old last node
    delete tempPtr; // reclaim former last node
    return true; // delete successful
  } // end else
} // end function removeFromBack

// is list Empty?
template <typename NODETYPE>
bool List<NODETYPE>::isEmpty() const
{
  return firstPtr == 0;
} // end function isEmpty

// return pointer to newly allocated node
template <typename NODETYPE>
List<NODETYPE> *List<NODETYPE>::getNewNode(
  const NODETYPE &value)
{
  return new ListNode<NODETYPE>(value);
} // end function getNewNode

// display contents of List
template<typename NODETYPE>
void List<NODETYPE>::print() const
{
  if (isEmpty()) // List is empty
  {
    std::cout << "The list is empty\n\n";
    return;
  } // end if
  
  ListNode<NODETYPE> *currentPtr = firstPtr_; 
  
  std::cout << "The list: ";
  
  while (currentPtr != 0) // get element data
  {
    std::cout << currentPtr->data << ' ';
    currentPtr = currentPtr->nextPtr;
  } // end while
  
  std::cout << "\n\n";
}  // end function print

#endif 
