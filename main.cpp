#include <iostream>
#include <cstring>
#include "Node.h"

using namespace std;

void add(Node* &treeRoot, Node* current, Node* newNode);
int correctInput();

int main() {
  
  Node* treeRoot = NULL;
  Node* current;
  Node* newNode;
  
  
  bool looping = true;
  while (looping == true) {
    int option = correctInput();
    // Add numbers to tree
    if (option == 1) {
      cout << "FILE or CONSOLE?" << endl;
      char input[15];
      cin.get(input, 15);
      cin.ignore(15, '\n');
      bool looping2 = true;
      while (looping2 == true) {
	if (strcmp(input, "FILE") == 0) {
	  looping2 = false;
	}
	else if (strcmp(input, "CONSOLE") == 0) {
	  int input[100];
	  cout << "How many numbers would you like to add?" << endl;
	  int totalNums;
	  cin >> totalNums;
	  cin.get();

	  cout << "Please enter your numbers." << endl;
	  for (int i = 0; i < totalNums; i++) {
	    cin >> input[i];
	    cin.get();
	    Node* newNode = new Node(input[i]);
	    add(treeRoot, treeRoot, newNode);
	  }
	  looping2 = false;
	}
	else {
	  cout << "Please input one of the two options" << endl;
	}
      }
    }
    // Print tree
    else if (option == 2) {
      
    }
    // Delete nodes from tree
    else if (option == 3) {
     
    }
    // Quit the program
    else if (option == 4) {
      looping = false;
    }
  }
}

// Add needs much more work...think about what cases could occur
void add(Node* &treeRoot, Node* current, Node* newNode) {
  bool parentGreater = false;
  if (current->getNum() > newNode->getNum()) {
    parentGreater = true;
  }
  if (treeRoot == NULL) {
    treeRoot = newNode;
  }
  else if ((parentGreater == true) && (current->getLeft() == NULL)) {
    current->setLeft(newNode);
  }
  else if ((parentGreater == true) && (current->getLeft() != NULL) && (current->getRight() == NULL)) {
    current->setRight(newNode);
  }
  else {
    add(treeRoot, current->getLeft(), newNode);
  }
}

int correctInput() {
  bool leaveLoop = false;
  cout << "Enter one of the following options: ADD, PRINT, REMOVE, or QUIT (uppercase)" << endl;
  while (leaveLoop == false) {
    char input[15];
    cin.get(input, 15);
    cin.ignore(15, '\n');
    if (strcmp(input, "ADD") == 0) {
      return 1;
    }
    else if (strcmp(input, "PRINT") == 0) {
      return 2;
    }
    else if (strcmp(input, "REMOVE") == 0) {
      return 3;
    }
    else if (strcmp(input, "QUIT") == 0) {
      return 4;
    }
    else {
      cout << "Please enter a valid option." << endl;
    }
  }
  return -1;
}
