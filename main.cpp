#include <iostream>
#include <cstring>
#include "node.h"

using namespace std;

//by ryan veith
//traveling salesman problem kina
//Directed Weighted Graph thingie

/*
struct path{
  Node* firstNode;
  Node* secondNOde;
  int valure;
};
//*/


//going to need some sort of linked list
bool findEdge(Node* firstNode, Node* secondNode, Node* current);
void addThing(Node* node, Node* &root, Node* current);
void removeThing(Node* node, Node* &root, Node* current, Node* previous);
bool findNode(int nodeId, Node* current);
//same as find but retuns it, null in cant find
Node* returnNode(int nodeId, Node* current);
Node* returnEdge(Node* firstNode, Node* secondNode, Node* current);

//prints
void printNode(Node* current);
void printEdge(Node* current);

//go look at delvertex to see why this is needed
void nodeDelAlert(Node* toDel, Node* current, Node* edgeRoot, Node* nodeRoot);

//going to want a list of nodes
//and a list of edges, list of nodes
//Nodes need to know value, Edges need to know 2 noedes and value
//means we need three classese, Edge, Node and then the linked list one

int main() {
  cout << "hello world" << endl;
  bool quit = false;
  Node* edgeRoot = NULL;
  Node* nodeRoot = NULL;
  //loop
  while(quit == false) {
    //ask user input
    char input[80];
    cin.getline(input, 80);
    if (strcmp(input, "QUIT") == 0) {
      quit = true;
    }
    if (strcmp(input, "HELP") == 0 ||
	strcmp(input, "Help") == 0 ||
	strcmp(input, "help") == 0) {
      cout << "Commands are:" << endl;
      cout << "Add Vertex" << endl;
      cout << "Add Edge" << endl;
      cout << "Remove Vertex" << endl;
      cout << "Remove Edge" << endl;
      cout << "Find Shortest Path" << endl;
      cout << "QUIT" << endl;
    }
    if (strcmp(input, "PRINT") == 0) {
      cout << "Edgelist (1) or Nodelist (2)?" << endl;
      //print edge or nodes?
      cin.getline(input, 80);
      if (input == "1" || input == "E" || input == "e") {
	//edgelist
	cout << "Print Edgelist: " << endl;
	printEdge(edgeRoot);
      }
      else {
	//nodelist
	
	cout << "Print Nodelist: " << endl;
	printNode(nodeRoot);
      }
    }
    if (strcmp(input, "Add Vertex") == 0) {
      cout << "A V" << endl;
      //find id
      cout << "what is the id of the vertex?" << endl;
      int newid = 0;
      cin >> newid;
      //check that is is unique ID
      if (findNode(newid, nodeRoot) == true) {
	cout << "choose a diferent id" << endl;
      }
      else {
	//create new node
	Node* temp = new Node(newid);
	//call add (add might be universal)
	addThing(temp, nodeRoot, nodeRoot);
      }
    }
    if (strcmp(input, "Add Edge") == 0) {
      cout << "A E" << endl;
      //figure out what edge (add two nodes it is connecting)
      //crate cpy of find node that returns node
      int a = 0;
      cout << "what is the id of the first node it connects to?" << endl;
      cin >> a;
      int b = 0;
      cout << "what is the id of the second node it connects to?" << endl;
      cin >> b;
      //find it
      Node* aNode = returnNode(a, nodeRoot);
      Node* bNode = returnNode(b, nodeRoot);
      //check that both nodes exist
      if (aNode == NULL ||bNode == NULL || a == b) {
	cout << "that is not allowed" << endl;
	//im lazy for cout
      }
      //create a new edge
      Node* temp = new Node();
      temp->first = aNode;
      temp->last = bNode;
      
      //call add edge
      addThing(temp, edgeRoot, edgeRoot);
    }
    if (strcmp(input, "Remove Vertex") == 0) {
      cout << "R V" << endl;
      cout << "what is the id of the vertex?" << endl;
      int num = 0;
      cin >> num;
      
      //find it
      Node* toDel = returnNode(num, nodeRoot);
      //go call remove on all edges attached to it
      if (toDel != NULL) {
	//go cpy search to look for any one sided ones 
	//lets just call remove on it there
	nodeDelAlert(toDel, edgeRoot, edgeRoot, nodeRoot);

	//then delete it
	removeThing(toDel, nodeRoot, nodeRoot, NULL);
      }
    }
    if (strcmp(input, "Remove Edge") == 0) {
      cout << "R E" << endl;
      //fnd it
      //same as adding here
      int a = 0;
      cout << "what is the id of the first node it connects to?" << endl;
      cin >> a;
      int b = 0;
      cout << "what is the id of the second node it connects to?" << endl;
      cin >> b;
      //find it
      Node* aNode = returnNode(a, nodeRoot);
      Node* bNode = returnNode(b, nodeRoot);
      //check that both nodes exist
      if (aNode == NULL ||bNode == NULL || a == b) {
	cout << "that is not allowed" << endl;
	//im lazy for cout
      }
      //new code
      Node* edge = returnEdge(aNode, bNode, edgeRoot);
      
      //now remove it
      removeThing(edge, edgeRoot, edgeRoot, NULL);
    }
    if (strcmp(input, "Find Shortest Path") == 0) {
      int thing1;
      int thing2;
      cout << "Enter the first Node" << endl;
      cin >> thing1;
      cout << "Enter the second Node" << endl;
      cin >> thing2;
      
      cout << thing1 << " " << thing2 << endl;
      //call dijkstra's
    }
  } 
}

bool findEdge(Node* firstNode, Node* secondNode, Node* current) {
  //go though list, if a edge exiss that connects nodes return true
  if (current != NULL) {
    if (current->first == firstNode ||
	current->first == secondNode) {
      if (current->last == firstNode ||
	  current->last == secondNode) {
	return true;
      }
    }
    return findEdge(firstNode, secondNode, current->getNext());
  }
  else {
    return false;
  }
}

void addThing(Node* node, Node* &root, Node* current) {
  //add a node to the ll, might be same as add edge like exact same
  if (root == NULL) {
    root = node;
  }
  else if(current->getNext() == NULL) {
    current->setNext(node);
  }
  else {
    addThing(node, root, current->getNext());
  }
}
void removeThing(Node* node, Node* &root, Node* current, Node* previous) {
  //go though list, find and remove
  if(root == node) {
    root = root->getNext();
    delete node;
  }
  else if (current == node) {
    previous->setNext(current->getNext());
    delete current;
  }
  else if (current->getNext() != NULL) {
    removeThing(node, root, current->getNext(), current);
  }
}

bool findNode(int nodeId, Node* current) {
  //return if a node with that id exits (id should be uniqe);
  if (current != NULL) {
    if (current->getNumber() == nodeId) {
      return true;
    }
    return findNode(nodeId, current->getNext());
  }
  else {
    return false;
  }
}

Node* returnNode(int nodeId, Node* current) {
  //return if a node with that id exits (id should be uniqe);
  if (current != NULL) {
    if (current->getNumber() == nodeId) {
      return current;
    }
    return returnNode(nodeId, current->getNext());
  }
  else {
    return NULL;
  }
}

void nodeDelAlert(Node* toDel, Node* current, Node* edgeRoot, Node* nodeRoot) {
  //go though list, if a edge exiss that connects nodes return true
  if (current != NULL) {
    if (current->first == toDel ||
	current->last == toDel) {
      //keep looking
      nodeDelAlert(toDel, current->getNext(), edgeRoot, nodeRoot);
      //then start del
      removeThing(current, edgeRoot, edgeRoot, NULL);
    }
    nodeDelAlert(toDel, current->getNext(), edgeRoot, nodeRoot);
  }
}

Node* returnEdge(Node* firstNode, Node* secondNode, Node* current) {
  //go though list, if a edge exiss that connects nodes return true
  if (current != NULL) {
    if (current->first == firstNode ||
	current->first == secondNode) {
      if (current->last == firstNode ||
	  current->last == secondNode) {
	return current;
      }
    }
    return returnEdge(firstNode, secondNode, current->getNext());
  }
  else {
    return NULL;
  }
}



void printNode(Node* current) {
  
}

void printEdge(Node* current) {
  
}
