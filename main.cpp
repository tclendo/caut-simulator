#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>


#include "grid.h"


using namespace std;


void usage(int argc, char **argv);
void read_file(vector <Cell*> &init, char* in_file);


int main(int argc, char** argv) {

  usage(argc, argv);

  // initial 'live' cells, will be initialized in our file reader
  vector <Cell*> initial_state;
  
  read_file(initial_state, argv[1]);
  
  return 0;
}

void usage(int argc, char** argv) {

  if (argc != 2) {
    cerr << "Usage: ./caut <inputfile>.caut" << endl;
    exit(EXIT_FAILURE);
  }

  cout << "Setting up Cellular Automata Simulation on file " << argv[1] << endl;
}

void read_file(vector <Cell*> &init, char* in_file) {

  ifstream file;

  file.open(in_file);

  string word;
  while (file >> word) {

    cout << word << endl;
  }
}
