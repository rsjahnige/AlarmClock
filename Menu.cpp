#include "Menu.h"

namespace UserInterface 
{
  void Menu::display(void) 
  {
    // Ensure Menu object is populated with at least one item
    if (_curr_node == nullptr) {
      Context::print("ERROR :: Menu Empty\0", LCD_LINE1);
      return;
    }

    Item item = _curr_node -> getData();
    Context::print(item.string, LCD_LINE1); 

    Node<Item> *nextNode = _curr_node -> getNextLink();
    if (nextNode != nullptr) {
      item = nextNode -> getData();
      Context::print(item.string, LCD_LINE2);
      Serial.println(item.string);
    } 

    Context::setCursor(LCD_LINE1);
  } 

  // Note that when there are an odd number of Nodes in the linked list
  // an empty line will be displayed at the end of the list
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

  int8_t Menu::buttonPress(void) 
  {
    Item userData = _curr_node -> getData();
    userData.action(userData.cntx);
    return -1;
  }
}
