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
void addEdge(Node* edge, Node* root);
void removeEdge(Node* edge, Node* root);
bool findEdge(Node* firstNode, Node* secondNode, Node* root);
void addNode(Node* node, Node* root);
void removeNode(Node* node, Node* root);
bool findNode(int nodeId, Node* root);

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
      cout << "What?" << endl;
    }
    if (strcmp(input, "Add Vertex") == 0) {
      cout << "A V" << endl;
      //find id
      //check that is is unique ID
      //create new node
      //call add (add might be universal)
    }
    if (strcmp(input, "Add Edge") == 0) {
      cout << "A E" << endl;
      //figure out what edge (add two nodes it is connecting)
      //check that both nodes exist
      //create a new edge
      //call add edge
    }
    if (strcmp(input, "Remove Vertex") == 0) {
      cout << "R V" << endl;
      //find it
      //go call remove on all edges attached to it
      //call remove on it
    }
    if (strcmp(input, "Remove Edge") == 0) {
      cout << "R E" << endl;
      //fnd it
      //remove it
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

void addEdge(Node* edge, Node* root) {
  //go thought list and add it to end
}

void removeEdge(Node* edge, Node* root) {
  //go though list to find a ege and remove it
}

bool findEdge(Node* firstNode, Node* secondNode, Node* root) {
  //go though list, if a edge exiss that connects nodes return true
  return false;
}

void addNode(Node* node, Node* root) {
  //add a node to the ll, might be same as add edge like exact same
}
void removeNode(Node* node, Node* root) {
  //redundant
}

bool findNode(int nodeId, Node* root) {
  //return if a node with that id exits (id should be uniqe);
  return false;
}
