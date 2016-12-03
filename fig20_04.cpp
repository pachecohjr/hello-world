// Fig 20.3: listnode.h
// Template ListNode class definition
#ifndef _LISTNODE_H
#define _LISTNODE_H

// forward declaration of class List required to announce that class
// List exists so it can be used in the friend declaration at line 13
template<typename NODETYPE> class List;

template<typename NODETYPE>
class ListNode
{
  friend class List<NODETYPE>; // make List a friend
  
  public:
  ListNode (const NODETYPE &); // constructor
  NODETYPE getData() const; // return data in node
  private:
  NODETYPE data; // data
  ListNode<NODETYPE> *nextPtr; // next node in list  
}; // end class ListNode
