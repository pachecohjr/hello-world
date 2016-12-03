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
