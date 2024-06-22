/*********************************************************************
>>  File:   Menu.h
>>  Author: Ryan Jahnige
>>
>>  Description:  Header file for the Menu class which is derived from
>>                the Context class. As such, it contains User Interface
>>                functions that allow a developer to display a 'list'
>>                on an LCD screen, scroll though the 'list', and select
>>                items within that 'list' to perform a developer defined
>>                action.
>>
>>  Note: The _curr_node private member variable will always point to the
>>        node that corresponds to the cursor location on the LCD.
**********************************************************************/
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
      char *string;                       // String to be displayed on the LCD - must be null terminated
      Context* cntx;
      void (*action)(Context*);           // Function called when user selects an Menu::Item instance
    };

    Menu(const LiquidCrystal* lcd, Node<Item>* head=nullptr) : 
          Context(lcd, CNTX_INPUT), _curr_node(head) {}
  
    void display(void) override;
    uint8_t type(void) override { return MENU; }

    Node<Item>* getNode(void)       { return _curr_node; }
    void setNode(Node<Item>* node)  { _curr_node = node; }
  
    void shiftLeft(void) override { return; }
    void shiftRight(void) override { return; }
  
    void shiftDown(void) override;
    void shiftUp(void) override;
    int8_t buttonPress(void) override;

  private:
    Node<Item> *_curr_node;
  };
}; 

#endif
