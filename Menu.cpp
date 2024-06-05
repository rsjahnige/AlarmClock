#include "Menu.h"

namespace UserInterface 
{
  void Menu::display(void) 
  {
    Item item = _curr_node -> getData();
    Context::print(item.string, LCD_LINE1); 
    Serial.println(item.string);

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
}
