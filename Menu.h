#ifndef MENU_H
#define MENU_H

#include "List.h"
#include "Context.h"

#define MENU    0x01

using LinkedList::Node;

namespace UserInterface
{
  class Menu : public Context 
  {
  public:
    typedef struct Item
    {
      char *string;                   // String to be displayed on the LCD - must be null terminated
      void (*action)();               // Function called when user selects an MenuItem instance
    };

    Menu(const LiquidCrystal* lcd, Node<Item>* head=nullptr) : 
          Context(lcd, CNTX_INPUT), _curr_node(head) {}
  
    void setNode(Node<Item>* node) { _curr_node = node; }
    void display(void) override;
  
    void shiftLeft(void) override { return; }
    void shiftRight(void) override { return; }
  
    void shiftDown(void) override;
    void shiftUp(void) override;

  private:
    Node<Item> *_curr_node;
  };
}; 

#endif
