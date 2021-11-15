#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <sstream>
#include <ctime>
#include <unistd.h>


#include "grid.h"


using namespace std;


void usage(int argc, char **argv);
Grid* read_file(vector <Cell*> &init, char* in_file, int ruleset);


int main(int argc, char** argv) {

  usage(argc, argv);

  // initial 'live' cells, will be initialized in our file reader
  vector <Cell*> initial_state;
  
  Grid* grid = read_file(initial_state, argv[1], stoi(argv[2]));
  
  // set the live cell vector in the grid class
  grid->Set_Live_Cells(initial_state);
  
  /*
    TODO:

    This is the section where we will begin the simulation.
    Everything is initialized up to this point,
    now it's up to the simulation to begin based on the ruleset.

   */

  for (int i = 0; i < stoi(argv[3]); i++) {
    // clear the system for printing
    system("clear");
    // print the grid
    grid->Curr_Print();
    // apply the ruleset to the grid
    grid->ApplyRules();

    // only here so that we can see the prints going on
    sleep(1);
  }

  // Delete the new grid from memory
  delete grid;

  // Program run successfully.
  return 0;
}

void usage(int argc, char** argv) {

  if ((argc < 4) || (argc > 4)) {
    cerr << "Usage: ./caut <inputfile>.caut <ruleset> <number_of_generations>" << endl;
    exit(EXIT_FAILURE);
  }

  cout << "Setting up Cellular Automata Simulation on file " << argv[1] << endl;
}

Grid* read_file(vector <Cell*> &init, char* in_file, int ruleset) {

  ifstream file;
  file.open(in_file);

  string line;
  getline(file, line);

  istringstream init_line(line);
  unsigned int rows;
  unsigned int columns;
  
  // the first 2 words in the file will be the rows and columns of the grid
  // TODO: error checking for bad input
  init_line >> rows >> columns;
  cout << "Rows: " << rows << endl;
  cout << "Columns: " << columns << endl;

  // initialize our grid of all empty cells
  Grid* grid = new Grid(rows, columns, ruleset);

  // Create a new live cell based on the x y coordinates from each input line
  while (getline(file, line)) {

    istringstream iss(line);
    unsigned int x;
    unsigned int y;

    if (!(iss >> x >> y)) {break;}

    cout << "x: " << x << " y: " << y << endl;

    // given the x and y coordinate of our input line, we want to make this
    // cell live for our simulation. We call Get_Cell and then Set_Curr_State
    Cell* input_cell = grid->Get_Cell(x, y);
    input_cell->Set_Curr_State(1);

    // we also want to add this to our vector of live cells
    init.push_back(input_cell);
  }

  // cout << "Grid initialized with " << init.size() << " live cells." << endl;

  return grid;
}
