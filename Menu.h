#ifndef MENU_H
#define MENU_H

#include <Arduino.h>
#include "Context.h"

#define MENU    0x01

namespace ListUI
{
  template<class T>
  class Node
  {
  public:
    Node();
    ~Node();

  private:
    T _data;
    Node<T> *_link;
  };
  
  template<class T>
  class Menu : public Context 
  {
  public:
    Menu(const LiquidCrystal *lcd);
    ~Menu();
  
    void display(void) override;
  
    void shiftLeft(void) override { return; }
    void shiftRight(void) override { return; }
    void shiftDown(void) override;
    void shiftUp(void) override;

  private:
    Node<T> *_head;
  };
};

#endif
