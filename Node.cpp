#include <iostream>
#include "Node.h"


using namespace std;

// Constructor
Node::Node() {
  left = NULL;
  right = NULL;
}

Node::Node(int newNum) {
  num = newNum;
  left = NULL;
  right = NULL;
}

// Destructor
Node::~Node() {
  left = NULL;
  right = NULL;
}

// Getters
Node* Node::getLeft() {
  return left;
}

Node* Node::getRight() {
  return right;
}

int Node::getNum() {
  return num;
}

// Setters
void Node::setLeft(Node* n) {
  left = n;
}

void Node::setRight(Node* n) {
  right = n;
}

void Node::setNum(int newNum) {
  num = newNum;
}
