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
bool findNode(Node* nodeId, Node* current);
//same as find but retuns it, null in cant find
Node* returnNode(int nodeId, Node* current);
Node* returnEdge(Node* firstNode, Node* secondNode, Node* current);
//find length of LL
int findLength(Node* current, int num);

//this is dijkstra's, exept mostly just a redo of traveling saleman
void dijkstra(Node* traveled, Node* current, Node* destination,
	      Node* edgeRoot, Node* nodeRoot, Node* start);
//traveled is going to be a root of a LL of traveled nodes;
//I don't tink the node LL is needed but pass it in anyway

//prints
void printNode(Node* current);
void printEdge(Node* current);

//go look at delvertex to see why this is needed
//(it is a special vesion of find that finds all, since it is only
//needed for one case it also cals delete)
void nodeDelAlert(Node* toDel, Node* current, Node* &edgeRoot, Node* &nodeRoot);

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
      int UI = 0;
      cin >> UI;
      if (UI == 1) {
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
    if (strcmp(input, "Add Vertex") == 0 || strcmp(input, "AV") == 0) {
      cout << "A V" << endl;
      //find id
      cout << "what is numerical id of the vertex you want to add?" << endl;
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
    if (strcmp(input, "Add Edge") == 0 || strcmp(input, "AE") == 0) {
      cout << "A E" << endl;
      //figure out what edge (add two nodes it is connecting)
      //crate cpy of find node that returns node
      int a = 0;
      cout << "what is the id of the first node it connects to?" << endl;
      cin >> a;
      int b = 0;
      cout << "what is the id of the second node it connects to?" << endl;
      cin >> b;
      cout << "what is the length of the edge?" << endl;
      int c = 0;
      cin >> c;
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
      temp->setNumber(c);
      
      //call add edge
      addThing(temp, edgeRoot, edgeRoot);
    }
    if (strcmp(input, "Remove Vertex") == 0 || strcmp(input, "RV") == 0) {
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
    if (strcmp(input, "Remove Edge") == 0 || strcmp(input, "RE") == 0) {
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
      
      cout << thing1 << " to " << thing2 << endl;
      //call dijkstra's now we have all info
      //for coding this it will be a seperate recusrive thing
      //also will need its own root for a ll, (only use first to store)
      //also need a find length
    }
  } 
}


void dijkstra(Node* &traveled, Node* current, Node* destination,
	      Node* edgeRoot, Node* nodeRoot, int currentPathLength,
	      Node* start, Node* previousList, bool done) {
  //traveled is a root;
  //Anywasy psudocode here:
  //start by visting thing with shortest path
  //then visit others for info of how far away it is
  //then go the the one with shortest path from main

  //I don't quite think think what I am doing is Dijstra since it would go
  //to end of path first though so lets fix that
  //I really dont want to keep track of a table so LL agian which is proably
  //worse then just doing the other seach but thats the assignment
  if (current == destination) {
    //cout the path
    done = true;
  }
  else if(done == true) {
    //do nothing
  }
  else {
    //go though everything connected to current and find shortest path
    //update that
    bool loop = true;
    int length = -1;

    //we need to knwo number of edges
    int c = 0;
    int d = 0;
    int b = findLength(edgeRoot, 0);
    Node* temp = edgeRoot;
    //so we 1 find number of conenciotns 
    for(int a = 0; a < b; b++) {
      if(temp != NULL) {
	//is it connected?
	if(temp->first == current || temp->last == current) {
	  c++;
	}
      }
      temp = temp->getNext();
    }

    Node* counter = NULL;
    while(loop == true) {
      //find an edge
      //see if it is shortest
      //one all edges are on edges we are done;

      temp = edgeRoot;
      Node* edge = NULL;

      //go though the edges
      for(int a = 0; a < b; b++) {
	if(temp != NULL) {
	  //is it connected?
	  if(temp->first == current || temp->last == current) {
	    //is it shorter
	    if((temp->getNumber() < length || length == -1) &&
	       findNode(temp, counter) != true) {
	      //save its length and it
	      length = temp->getNumber();
	      edge = temp;
	      //remove it form this search
	      addThing(temp, counter, counter);
	      
	    }
	  }
	  temp = temp->getNext();
	}
      }
      //end of for loop
      //we have found shortest edge
      //go update that
      
      //also yes this is most definetly an abomination
      //but in my defence I was planning on doing a find the shortest path
      //so have nothign planned for a table
      if(findNode(current->getNumber(), traveled) == false) {
	//lets make first the current vertex
	//last the previous
	//and num the distance
	
	//ad it to LL
	Node* chaos = new Node();
	addThing(traveled, chaos, chaos);
	//set vertex
	if (current == edge->first) {
	  chaos->first = edge->last;
	}
	else {
	  chaos->first = edge->first;
	}
	//set previous
	//this is current since we did not actually move
	chaos->last = current;
	//set pathlength
	//this is just edge->getNumber + previous->getNumber
	chaos->setNumber(edge->getNumber() + chaos->last->getNumber());
      }
      else {
	cout << "update" << endl;
	//update its value (wierd case) for if its better
      }
      
      //now we need to check if we have gone thought all connections
      //if so we exit the loop
      if (c == d) {
	loop = false;
      }
    }
    //end of while loop
    
    //now go to the next node
    //find conneciton with least distance and go down that
    //as long as other connecitosn have been done
    //go look at previousList, if previous could go to any that is in list do
    //that
    
    //if (current == start) {
    //go no matter what
    //}

    //you know what just go to edge and it should magicaly sort iself out
    //that or I have a massive headache trying to code a other way that is
    //not another monstraosity
    //also it snot edge ut pob a new variale bieng set up, drat
    //cp paste
    //we need to knwo number of edges
    int c = 0;
    int d = 0;
    int b = findLength(edgeRoot, 0);
    Node* temp = edgeRoot;
    //so we 1 find number of conenciotns 
    for(int a = 0; a < b; b++) {
      if(temp != NULL) {
	//is it connected?
	if(temp->first == current || temp->last == current) {
	  c++;
	}
      }
      temp = temp->getNext();
    }

    Node* counter = NULL;
    while(loop == true) {
      //find an edge
      //see if it is shortest
      //one all edges are on edges we are done;

      temp = edgeRoot;
      Node* edge = NULL;

      //go though the edges
      for(int a = 0; a < b; b++) {
	if(temp != NULL) {
	  //is it connected?
	  if(temp->first == current || temp->last == current) {
	    //is it shorter
	    if((temp->getNumber() < length || length == -1) &&
	       findNode(temp, counter) != true) {
	      //save its length and it
	      length = temp->getNumber();
	      edge = temp;
	      //remove it form this search
	      addThing(temp, counter, counter);
	      
	    }
	  }
	  temp = temp->getNext();
	}
      }
      //no go to that one
      
    }
    //keep updating for all connectos
    //then go to the path
  }
  
}

  

int findLength(Node* current, int num) {
  if (current != NULL) {
    num++;
    num = findLength(current->getNext(), num);
  }
  return num;
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
  cout << "rm" << endl;
  if(root == node) {
    cout << "del root" << endl;
    cout << root->getNumber()  << ": " << root->getNext() << endl;
    root = root->getNext();
    cout << root << endl;
    delete node;
    return;
  }
  else if (current == node) {
    cout << "del current" << endl;
    previous->setNext(current->getNext());
    delete current;
  }
  else if (current->getNext() != NULL && root != node) {
    cout << "recirse" << endl;
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

bool findNode(Node* nodeId, Node* current) {
  //return if a node with that id exits (id should be uniqe);
  if (current != NULL) {
    if (current == nodeId) {
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

void nodeDelAlert(Node* toDel, Node* current, Node* &edgeRoot, Node* &nodeRoot) {
  //go though list, if a edge exiss that connects nodes return true
  if (current != NULL) {
    if (current->first == toDel ||
	current->last == toDel) {
      
      cout << toDel->getNumber() << ": " << current << endl;

      Node* next = current->getNext();
      removeThing(current, edgeRoot, edgeRoot, NULL);
      
      //keep looking
      nodeDelAlert(toDel, next, edgeRoot, nodeRoot);
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
  if (current != NULL) {
    cout << "Current: " << current->getNumber() << endl;
    
  printNode(current->getNext());
  }
}

void printEdge(Node* current) {
  if (current != NULL) {
    cout << "Current: " << current << endl;
    cout << "Length " << current->getNumber() << endl;
    if (current->first != NULL) {
      cout << "A   " << current->first->getNumber() << endl;
    }
    if (current->last != NULL) {
      cout << "B   " << current->last->getNumber() << endl;
    }
    
  printEdge(current->getNext());
  }
}
