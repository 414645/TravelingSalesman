#ifndef Node_H
#define Node_H

#include <iostream>
#include <cstring>


//for this project we are bringing back a variant of the bst nodes
//they only need one child do do a linked list

class Node {
public:
  Node();
  Node(int);
  ~Node();
  
  Node* getNext();
  void setNext(Node*);

  int getNumber();
  //prob not needed
  void setNumber(int);

  Node* getParent();
  //prob not DLL but never hurts to have option
  void setParent(Node*);

  //might want red and back for traveling saleman
  int getColor();
  void setColor(int);
private:
  Node* nextNode;
  int number;
  Node* parent;
  int color;
};
#endif
