#include <iostream>
#include "node.h"

using namespace std;

Node::Node() {
  cout << "blank node created" << endl;
  nextNode = NULL;
  number = -1;
  parent = NULL;
  color = -1;
  
}
Node::Node(int newNumber) {
  nextNode = NULL;
  number = newNumber;
  //default parent to NULL and color to 0
  parent = NULL;
  color = 0;
}

Node::~Node() {
  //cout << "node destroyed" << endl;
}
Node* Node::getNext() {
  return nextNode;
}
void Node::setNext(Node* newNext) {
  nextNode = newNext;
}
int Node::getNumber() {
  return number;
}
void Node::setNumber(int newNumber) {
  number = newNumber;
}
Node* Node::getParent() {
  return parent;
}
void Node::setParent(Node* newparent) {
  parent = newparent;
}
int Node::getColor() {
  return color;
}
void Node::setColor(int newcolor) {
  color = newcolor;
}


