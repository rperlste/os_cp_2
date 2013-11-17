/*
 *    Robbie Perlstein
 *    101130094
 *    Advanced Programming
 *    Spring 2013
 *    Forward Linked List
 *    
 *    Class declaration for a single-ended, singly-f_linked list with iterator
 *    support. Compatible with C++ STL
 */

/************************ PRE / POST CONDITIONS ********************************
fw_list();
PRE:    None.
POST:   Creates an empty list.

fw_list( const fw_list<T>& );
PRE:    None.
POST:   Copies a list, creating new elements in free store.

fw_list( iterator, iterator );
PRE:    None.
POST:   Copies a list from the first iterator to the second, or when the first
        iterator reaches the end of the list.

fw_list( T*, T* );
PRE:    T* points an array. The second argument is a within the arrays size.
POST:   Creates a list from an array of type T.

~fw_list();
PRE:    None.
POST:   Deletes any objects in the list.

// Constant members
unsigned size() const
PRE:    None.
POST:   Returns the size of the list.

bool empty() const
PRE:    None.
POST:   Returns true if the list is empty, else false.

const T& front() const;
PRE:    None.
POST:   Returns the first element of the list. Throws an exception if list
        is empty.

const iterator find( const T& ) const;
PRE:    None.
POST:   Returns an iterator for the first element that matches the parameter,
        or returns the end iterator.

// Modification members
void push_front( const T& );
PRE:    None.
POST:   Pushes a new element onto the front of the list, making it the head.

void pop_front();
PRE:    None.
POST:   Pops the first element off the list if one exists.

iterator find( const T& );
PRE:    None.
POST:   Returns an iterator for the first element that matches the parameter,
        or returns the end iterator.

void insert( const T&, unsigned );
PRE:    None.
POST:   Inserts an element into the list at a position, where offsets start
        at 0. Inserts at the end if the position provided is not accessible.

void insert_after( iterator, const T& );
PRE:    Iterator must be for the this list.
POST:   Inserts an element after the iterator provided.

bool erase_one( const T& );
PRE:    None.
POST:   Erases the first instance of an element found. Returns true if erased.

unsigned erase( const T& );
PRE:    None.
POST:   Erases all instances of an element. Returns the quantity erased.

void clear();
PRE:    None.
POST:   Deletes all elements of the list.

fw_list<T>& operator =  ( const fw_list<T>& );
PRE:    None.
POST:   Copies a list, creating new elements in free store, overwriting the 
        original list.

void operator += ( const fw_list<T>& );
PRE:    None.
POST:   Appends a list onto the end of this list in order.

template<T> friend std::ostream& 
                operator << ( std::ostream&, const fw_list<T>& );
PRE:    Data type T supports ostream operator <<
POST:   Prints a formatted list output to a stream.

iterator begin() const;
PRE:    None.
POST:   Returns an iterator for the first element in the list. If the list is
        empty it returns the end iterator.

iterator end() const;
PRE:    None.
POST:   Returns an end iterator.

node*   copy(node*);
PRE:    None.
POST:   Returns a node* to a node copy in free store.

******** NOTE - THE SAME PRE/POST APPLIES FOR THE SPECIALIZATION
******** EXCEPT FOR ONE ADDITION - IF THE POINTER CANNOT BE DEREFERENCED
******** TO A VALUE TYPE, THEN THERE WILL BE UNDEFINED BEHAVIOR

*******************************************************************************/

#ifndef _FwLinkedList_H
#define _FwLinkedList_H

#include <iostream>
#include <exception>

template <typename T> class fw_list;

#include "node_iterator.h"


// Class definition
template <typename T>
class fw_list {
public:
    typedef fw_node_iterator<T> iterator;

    // Constructors
    fw_list();
    fw_list( const fw_list<T>& );
    fw_list( iterator, iterator );
    fw_list( T*, T* );
    ~fw_list();

    // Constant members
    unsigned        size() const { return used; }
    bool            empty() const { return used==0; }
    const T&        front() const;
    const T&        back() const;
    const iterator  find( const T& ) const;

    // Modification members
    void            push_front( const T& );
    void            pop_front();
    void            push_back( const T& );
    void            pop_back();
    iterator        find( const T& );
    void            insert( const T&, unsigned );
    void            insert_after( iterator, const T& );
    bool            erase_one( const T& );
    unsigned        erase( const T& );
    void            clear();

    // Operators
    fw_list<T>&     operator =  ( const fw_list<T>& );
    void            operator += ( const fw_list<T>& );

    // Friends
    friend class    fw_node_iterator<T>;

    // Forward iterator support
    iterator        begin() const;
    iterator        end() const;

private:
    // Nest our f_linked-fw_list node
    struct node
    {
        node(const T& val=T(), node* n=0, node* t=0):data(val),f_link(n),b_link(t) { }
        T           data;
        node*       f_link;
        node*       b_link;
    };
    node*           head;
    node*           tail;
    unsigned        used;
    node*           copy(node*);
};

template <typename T>
fw_list<T>::fw_list() {
  used = 0;
  head = 0;
  tail = 0;
}

template <typename T>
fw_list<T>::~fw_list() {
  node* temp = head;
  while( used > 0 ) {
    head = head->f_link;
    delete temp;
    temp = head;
    -- used;
  }
}


template <typename T>
fw_list<T>::fw_list( const fw_list<T>& rList ) {
  used = 0;
  head = 0;
  tail = 0;
  *this = rList;
}

template <typename T>
const T& fw_list<T>::front() const {
  if( used == 0 )
    throw std::exception(
    std::string( "No elements exist in the fw_list." ).c_str() );
  return head->data;
}


template <typename T>
const typename fw_list<T>::iterator fw_list<T>::find( const T& data ) const {
  iterator it( 0 );
  for( it = begin();
       it != end();
       ++ it ) {
    if( ( *it ) == data )
      return it;
  }
  return it;
}


template <typename T>
void fw_list<T>::push_front( const T& data ) {
  node* temp = new node( data, head );
  head->b_link = temp;
  head = temp;
  ++ used;
}

template <typename T>
void fw_list<T>::pop_front() {
  if( used == 0 ) return;
  typename fw_list<T>::node* toDel = head;
  head = head->f_link;
  head->b_link = 0;
  delete toDel;
  -- used;
}

template <typename T>
void fw_list<T>::push_back( const T& data ) {
  node* temp = new node( data, 0, tail );
  tail->f_link = temp;
  tail = temp;
  ++ used;
}

template <typename T>
void fw_list<T>::pop_back() {
  if( used == 0 ) return;
  typename fw_list<T>::node* toDel = tail;
  tail = tail->f_link;
  tail->f_link = 0;
  delete toDel;
  -- used;
}


template <typename T>
typename fw_list<T>::iterator fw_list<T>::find( const T& data ) {
  unsigned i = 0;
  node* n = head;
  while( i < used ) {
    if( n->data == data )
      break;
    n = n->f_link;
    ++ i;
  }
  return iterator( n );
}


template <typename T>
void fw_list<T>::insert( const T& data, unsigned insPos ) {

  // Special case: Insert at head
  if( insPos == 0 || used == 0 ) {
    head = new node( data, head );
  }

  // Insert in middle or end
  else {
    unsigned currPos = 1;
    node* currNode = head;
    while( currNode->f_link != 0
           && currPos < insPos ) {
      currNode = currNode->f_link;
      ++ currPos;
    }
    currNode->f_link = new node( data, currNode->f_link );
  }
  ++ used;
  return;

}

template <typename T>
void fw_list<T>::insert_after( iterator it, const T& data ) {
  // End insert
  if( it->f_link == 0 ) {
    it->f_link = new node( data, 0, it->b_link );
  } else {
    node* temp = new node( data, it->f_link, *it );
    it->f_link->b_link = temp;
    it->f_link = temp;
  }
  ++ used;
}

template <typename T>
bool fw_list<T>::erase_one( const T& toErase ) {
  unsigned pos = 0;
  node* curr = head;
  node* toDel = head;

  // Delete head, special case
  if( curr != 0 && curr->data == toErase ) {
    if( curr->f_link != 0 ) {
      curr = curr->f_link;
    }
    delete toDel;
    -- used;
    return true;
  }
  ++ pos;
  toDel = curr->f_link;
  while( pos < used ) {
    if( toDel->data == toErase ) {
      curr->f_link = toDel->f_link;
      -- used;
      return true;
    }
    ++ pos;
    curr = toDel;
    toDel = toDel->f_link;
  }
  return false;
}

template <typename T>
unsigned fw_list<T>::erase( const T& toErase ) {
  unsigned count = 0;
  node* curr = head;
  node* toDel = head;

  // Special case: head deletion
  while( curr != 0
         && curr->data == toErase ) {
    toDel = curr;
    curr = curr->f_link;
    delete toDel;
    ++ count;
    -- used;
  }

  while( curr != 0 ) {
    toDel = curr->f_link;
    if( toDel != 0 ) {
      if( toDel->data == toErase ) {
        curr->f_link = toDel->f_link;
        delete toDel;
        toDel = curr->f_link;
        ++ count;
        -- used;
      } else {
        curr = curr->f_link;
        toDel = curr->f_link;
      }
    } else {
      break;
    }
  }
  return count;
}

template <typename T>
void fw_list<T>::clear() {
  while( used > 0 ) {
    pop_front();
  }
}

template <typename T>
fw_list<T>& fw_list<T>::operator = ( const fw_list<T>& rList ) {
  this->clear();
  // avoid unnecessary traversal
  if( rList.size() > 0 ) {
    node* insNode = rList.head;
    head = new node( insNode->data );
    node* currNode = head;
    insNode = insNode->f_link;
    while( insNode != 0 ) {
      currNode->f_link = new node( insNode->data );
      currNode = currNode->f_link;
      insNode = insNode->f_link;
    }
  }
  used = rList.size();
  return *this;
}

// Warning... not cheap to use!
template <typename T>
void fw_list<T>::operator += ( const fw_list<T>& rList ) {
  // avoid unnecessary traversal
  if( rList.size() > 0 ) {
    if( head != 0 ) {
      node* currNode = head;
      node* insNode = rList.head;
      while( currNode->f_link != 0 ) {
        currNode = currNode->f_link;
      }
      while( insNode != 0 ) {
        currNode->f_link = new node( insNode->data );
        currNode = currNode->f_link;
        insNode = insNode->f_link;
        ++ used;
      }
    }
  }
}


template <typename T>
typename fw_list<T>::iterator fw_list<T>::begin() const {
  return iterator( head );
}

template <typename T>
typename fw_list<T>::iterator fw_list<T>::end() const {
  return iterator();
}

template <typename T>
typename fw_list<T>::node* fw_list<T>::copy( node* toCopy ) {
  return new node( toCopy->data, toCopy->f_link, toCopy->b_link );
}

#endif