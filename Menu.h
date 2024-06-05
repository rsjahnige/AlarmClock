#ifndef MENU_H
#define MENU_H

#include "Context.h"

#define MENU    0x01

namespace List
{
  // Will act as a circular buffer (?)
  template<class T>
  class Node
  {
  public:
    Node(const T& data, Node<T>* nextLink=nullptr, Node<T>* prevLink=nullptr) :
          _data(data), _next_link(nextLink), _prev_link(prevLink) {}

    const T getData(void) const { return data; }
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
  void insertNode(Node<T>* afterMe, const T& data);

  template<class T>
  void deleteNode(Node<T>* node);
      
  // This class assumes that there is always at least one node that contains data and the 
  // node data is accessible via indexing (required to support char* and Alarm 'class' types)
  template<class T>
  class Menu : public Context 
  {
  public:
    Menu(const LiquidCrystal* lcd, Node<T>* head) : Context(lcd), _curr_node(head) {}
  
    void display(void) override;
  
    void shiftLeft(void) override { return; }
    void shiftRight(void) override { return; }

    void shiftDown(void) override;
    void shiftUp(void) override;

  private
    Node<T> *_curr_node;    // Node at the current cursor location
  };
};

#endif
