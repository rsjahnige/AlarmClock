/*********************************************************************
>>  File:   List.h
>>  Author: Ryan Jahnige
>>
>>  Description:  This file contains functions defined for building and
>>                maintaining a Double Linked List as well as a templated
>>                Node class to store each element of the list.
>>
>>  Note: The developer who chooses to use the LinkedList namespace is
>>        required to maintain a pointer to at least one Node within the
>>        linked list, otherwise the list will be lost
**********************************************************************/
#ifndef List_H
#define List_H

namespace LinkedList
{
  template<class T>
  class Node
  {
  public:
    Node(const T& data, Node<T>* nextLink=nullptr, Node<T>* prevLink=nullptr) :
          _data(data), _next_link(nextLink), _prev_link(prevLink) {}

    const T getData(void) const { return _data; }
    Node<T>* getNextLink(void) const { return _next_link; }
    Node<T>* getPrevLink(void) const { return _prev_link; }

    void setData(const T& data) { _data = data; }
    void setNextLink(Node<T>* link) { _next_link = link; }
    void setPrevLink(Node<T>* link) { _prev_link = link; }

  private:
    T _data;
    Node<T> *_next_link;
    Node<T> *_prev_link;
  };

  template<class T>
  void insertAfter(Node<T>* afterMe, const T& data)
  {
    Node<T> *replace = afterMe -> getNextLink();
    Node<T> *newNode = new Node<T>(data, replace, afterMe);

    afterMe -> setNextLink(newNode);
    if (replace != nullptr) replace -> setPrevLink(newNode); 
  }

  template<class T>
  void insertBefore(Node<T>* beforeMe, const T& data)
  {
    Node<T> *replace = beforeMe -> getPrevLink();
    Node<T> *newNode = new Node<T>(data, beforeMe, replace);

    beforeMe -> setPrevLink(newNode);
    if (replace != nullptr) replace -> setNextLink(newNode);
  }

  template<class T>
  void deleteNode(Node<T>* node) 
  {
    Node<T> *prev = node -> getPrevLink();
    Node<T> *next = node -> getNextLink();

    if (prev != nullptr) prev -> setNextLink(next);
    if (next != nullptr) next -> setPrevLink(prev);

    delete node;
  }
};

#endif
