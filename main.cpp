#include <iostream>
#include <cstring>
#include <fstream>
#include "Node.h"

using namespace std;

void add(Node* &treeRoot, Node* current, Node* newNode);
void print(Node* treeRoot, int level);
void search(Node* treeRoot, int value, bool &contained);
void remove(Node* &treeRoot, Node* current, Node* parent, int direction, int value);
int correctInput();

int main() {
  
  Node* treeRoot = NULL;
  Node* current;
  Node* newNode;
  int level = 0;
  
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
	  int input[100];
	  int totalNums;
	  cout << "How many numbers are you adding?" << endl;
	  cin >> totalNums;
	  cin.get();
	  ifstream numbers("testNumbers.txt");
	  for (int i = 0; i < totalNums; i++) {
	    numbers >> input[i];
	    Node* newNode = new Node(input[i]);
	    add(treeRoot, treeRoot, newNode);
	  }
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
      print(treeRoot, level);
    }
    // Search for values
    else if (option == 3) {
      cout << "What number would you like to search for?" << endl;
      int value;
      cin >> value;
      cin.get();
      bool contained = false;
      search(treeRoot, value, contained);
      if (contained == true) {
	cout << endl << "The inputted value is contained within the tree." << endl << endl;
      }
      else if (contained == false) {
	cout << endl << "The inputted value is NOT contained within the tree." << endl << endl;
      }
    }
    // Delete nodes from tree
    else if (option == 4) {
      cout << "What number would you like to delete?" << endl;
      int value;
      cin >> value;
      cin.get();
      int direction;
      remove(treeRoot, treeRoot, treeRoot, direction, value);
    }
    // Quit the program
    else if (option == 5) {
      looping = false;
    }
  }
}

void add(Node* &treeRoot, Node* current, Node* newNode) {
  if (treeRoot == NULL) {
    treeRoot = newNode;
  }
  else if (current->getNum() > newNode->getNum()) {
    if (current->getLeft() == NULL) {
      current->setLeft(newNode);
    }
    else if (current->getLeft() != NULL) {
      add(treeRoot, current->getLeft(), newNode);
    }
  }
  else if ((current->getNum() < newNode->getNum()) || (current->getNum() == newNode->getNum())) {
    if (current->getRight() == NULL) {
      current->setRight(newNode);
    }
    else if (current->getRight() != NULL) {
      add(treeRoot, current->getRight(), newNode);
    }
  }
}

void print(Node* treeRoot, int level) {
  if (treeRoot == NULL) {
    cout << "The tree is empty!" << endl << endl;
  }
  // Go through the right side of tree, finding where the tree stops, and indenting appropriately
  else {
    if (treeRoot->getRight() != NULL) {
      print(treeRoot->getRight(), level + 1);
    }
    // Indent values
    for (int i = 0; i < level; i++) {
      cout << '\t';
    }
    // Left side
    cout << treeRoot->getNum() << endl;
    if (treeRoot->getLeft() != NULL) {
      print(treeRoot->getLeft(), level + 1);
    }
  }
}

void search(Node* treeRoot, int value, bool &contained) {
  if (treeRoot == NULL) {
    cout << "The tree is empty!" << endl << endl;
  }
  else {
    if (treeRoot->getNum() == value) {
      contained = true;
    }
    if (treeRoot->getRight() != NULL) {
      search(treeRoot->getRight(), value, contained);
    }
    if (treeRoot->getLeft() != NULL) {
      search(treeRoot->getLeft(), value, contained);
    }
  }
}

void remove(Node* &treeRoot, Node* current, Node* parent, int direction, int value) {
  if (treeRoot == NULL) {
    cout << "The tree is empty!" << endl << endl;
    return;
  }
  else {
    if (current->getNum() == value) {
      // Case where node has no children
      if (current->getRight() == NULL && current->getLeft() == NULL) {	
	if (current == treeRoot) {
	  treeRoot = NULL;
	}
	else {
	  if (direction == 1) {
	    parent->setRight(NULL);
	  }
	  else if (direction == 0) {
	    parent->setLeft(NULL);
	  }
	  current = NULL;
	}
      }
      // Case where node has two children
      else if (current->getRight() != NULL && current->getLeft() != NULL) {
	Node* replacement = current->getRight();
	Node* replacementParent = current;
	while (replacement->getLeft() != NULL) {
	  replacementParent = replacement;
	  replacement = replacement->getLeft();
	}
	if (current != replacementParent) {
	  current->setNum(replacement->getNum());
	  replacementParent->setLeft(NULL);
	}
	else {
	  current->setNum(replacement->getNum());
	  current->setRight(current->getRight()->getRight());
	}
      }
      // Case where node has one child
      else if (current->getRight() != NULL || current->getLeft() != NULL) {
	if (current->getRight() != NULL) {
	  if (current == treeRoot) {
	    treeRoot = current->getRight();
	  }
	  else {
	    if (direction == 1) {
	      parent->setRight(current->getRight());
	    }
	    else if (direction == 0) {
	      parent->setLeft(current->getRight());
	    }
	  }
	}
	else if (current->getLeft() != NULL) {
	  if (current == treeRoot) {
	    treeRoot = current->getLeft();
	  }
	  else {
	    if (direction == 1) {
	      parent->setRight(current->getLeft());
	    }
	    else if (direction == 0) {
	      parent->setLeft(current->getLeft());
	    }
	  }
	}
      }
    }
    else {
      if (current->getNum() < value) {
	if (current->getRight() != NULL) {
	  direction = 1;
	  remove(treeRoot, current->getRight(), current, direction, value);
	}
	else {
	  cout << endl << "This number is not contained within the tree!" << endl << endl;
	}
      }
      else if (current->getNum() > value) {
	if (current->getLeft() != NULL) {
	  direction = 0;
	  remove(treeRoot, current->getLeft(), current, direction, value);
	}
	else {
	  cout << endl << "This number is not contained within the tree" << endl << endl;
	}
      }
    }
  }
}

int correctInput() {
  bool leaveLoop = false;
  cout << "Enter one of the following options: ADD, PRINT, SEARCH, REMOVE, or QUIT (uppercase)" << endl;
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
    else if (strcmp(input, "SEARCH") == 0) {
      return 3;
    }
    else if (strcmp(input, "REMOVE") == 0) {
      return 4;
    }
    else if (strcmp(input, "QUIT") == 0) {
      return 5;
    }
    else {
      cout << "Please enter a valid option." << endl;
    }
  }
  return -1;
}
