#include "Menu.h"

namespace List 
{
  template<class T>
  void insertNode(Node<T>* afterMe, const T& data) 
  {
    afterMe -> setNextLink(new Node<T>(data, afterMe->getNextLink(), afterMe));
  }

  template<class T>
  void deleteNode(Node<T>* node) 
  {
    (node -> getPrevLink()) -> setNextLink(node -> getNextLink());
    (node -> getNextLink()) -> setPrevLink(node -> getPrevLink());
    delete node;
  }

  template<class T>
  void Menu::display(void) 
  {
    char *str = _curr_node -> getData();
    Context::print(&str[0], LCD_LINE1); 

    Node<char*> nextNode = _curr_node -> getNextLink();
    if (nextNode != nullptr) {
      str = _nextNode -> getData();
      Context::print(&str[0], LCD_LINE2);
    }

    Context::setCursor(LCD_LINE1);
  } 

  // Note that when there are an odd number of Nodes in the linked list
  // an empty line will be displayed at the end of the list
  template<class T>
  void Menu::shiftDown(void)
  {
    if ((_curr_node -> getNextLink()) != nullptr) {
      _curr_node = _curr_node -> getNextLink();

      if (Context::getCursor() >= LCD_LINE2) {
        Context::changeContext();
      } else {
        Context::shiftDown();
      }
    } 
  }

  template<class T>
  void Menu::shiftUp(void)
  {
    if ((_curr_node -> getPrevLink()) != nullptr) {
      _curr_node = _curr_node -> getPrevLink();

      if (Context::getCursor() < LCD_LINE2) {
        Context::changeContext();
      } else {
        Context::shiftUp();
      }
    }
  }
}
