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
  void insertNode(Node<T>* afterMe, const T& data)
  {
    Node<T> *replace = afterMe -> getNextLink();
    Node<T> *newNode = new Node<T>(data, replace, afterMe);

    afterMe -> setNextLink(newNode);
    replace -> setPrevLink(newNode); 
  }

  // This function is currently untested !!!!
  template<class T>
  void deleteNode(Node<T>* node) 
  {
    (node -> getPrevLink()) -> setNextLink(node -> getNextLink());
    (node -> getNextLink()) -> setPrevLink(node -> getPrevLink());
    delete node;
  }
};

#endif
