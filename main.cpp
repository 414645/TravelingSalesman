#include <iostream>
#include <cstring>


using namespace std;

//by ryan veith
//traveling salesman problem kina
//Directed Weighted Graph thingie

//going to need some sort of linked list
//void

int main() {
  cout << "hello world" << endl;
  bool quit = false;
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
    }
    if (strcmp(input, "Add Edge") == 0) {
      cout << "A E" << endl;
    }
    if (strcmp(input, "Remove Vertex") == 0) {
      cout << "R V" << endl;
    }
    if (strcmp(input, "Remove Edge") == 0) {
      cout << "R E" << endl;
    }
    if (strcmp(input, "Find Shortest Path") == 0) {
      int thing1;
      int thing2;
      cout << "Enter the first Node" << endl;
      cin >> thing1;
      cout << "Enter the second Node" << endl;
      cin >> thing2;
      
      cout << thing1 << " " << thing2 << endl;
    }
  } 
}
