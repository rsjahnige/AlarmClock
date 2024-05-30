#ifndef MENU_H
#define MENU_H

#include <Arduino.h>
#include "Context.h"

#define MENU    0x01

namespace UI
{
  template<class T>
  class Node
  {
  public:
    Node();
    ~Node();

  private:
    T _data;
    Node<T> *_next_link;      // Forward iteration
    Node<T> *_last_link;      // Reverse iteration
  };
  
  template<class T>
  class Menu : public Context 
  {
  public:
    Menu(const LiquidCrystal *lcd, uint8_t num_options=3, char **options=nullptr);
    ~Menu();
  
    virtual void display(void) override;
  
    virtual void shiftLeft(void) override { return; }
    virtual void shiftRight(void) override { return; }
    virtual void shiftDown(void) override;
    virtual void shiftUp(void) override;

  private:
    Node<T> *_head;
  };
};

#endif
