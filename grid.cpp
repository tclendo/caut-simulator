#include <iostream>
#include <omp.h>

#include "grid.h"

using namespace std;

Grid::Grid(unsigned int rows, unsigned int cols, unsigned int ruleSet){
	
  this->rows = rows;
  this->cols = cols;
  this->ruleSet = ruleSet;

  //allocate whole block for the grid
  cellArray = new Cell**[rows];
	
  //loop through cellArray instantiating cell objects
  //in theory we could simply use integer values instead of classes
  //but with classes we allow for more complexity with later implementations
  for(int i=0; i<rows; ++i){
    
    //allocate each row
    cellArray[i] = new Cell*[cols];
    for(int j=0; j<cols; ++j){
      //instantiate objects in the row
      cellArray[i][j] = new Cell(i, j);
    }
  }
}

Grid::~Grid(){
  for(int i=0; i<rows; ++i){
    for(int j=0; j<cols; ++j){
      delete cellArray[i][j];
    }
    delete[] cellArray[i];
  }

  delete [] cellArray;
}

void Grid::Curr_Print() {
  
  // indexed the way it is so that the origin is in the bottom left
  // TODO: Remember how this is inefficient due to cache lines
  // potentially need to figure out the most efficient way to do this.
  // Maybe not here in print, but when performing simulation actions.
/*	for(int i=rows; i > 0; --i){
    for(int j=0; j < cols; ++j){
      cout << " " << cellArray[j][i - 1]->Get_Curr_State() << " ";
    }
    cout << endl;
  }*/

  for(int i=0; i < rows; ++i){
    for(int j=0; j < cols; ++j){
      if(cellArray[i][j]->Get_Curr_State() == 1)
	cout << " " <<"x"<< " ";
      else	
      	cout << " " <<" "<< " ";
    }
    cout << endl;
  }
}

void Grid::Next_Print(){
  
  // TODO: Figure out how to make it so that origin is bottom left?
  for(int i=0; i<rows; ++i){
    for(int j=0; j<cols; ++j){
      cout << " " << cellArray[i][j]->Get_Next_State() << " ";
    }
    cout << endl;
  }
}

void Grid::Print_Live_Cells() {

  cout << "Live cells:" << endl;
  for (Cell* cell : live_cells) {
    cout << cell->Get_X_Coord() << ","
	 << cell->Get_Y_Coord() << ": "
	 << cell->Get_Curr_State() << " -> "
	 << cell->Get_Next_State() << endl;
  }
}

//these needs to be ints not unsigned because signed values will be passed here
inline bool Grid::Is_Safe_Coord(int x, int y) {
	return (((x < cols) && (y < rows)) && ((x >= 0) && (y >= 0)));
}

void Grid::ApplyRules(){
	
  switch(ruleSet){
	
  case 1 :
    ApplyGOL();
    break;
		
  default:
    cout<<"Undefined rule set defined rule sets are:"<<endl;
    cout<<"1: Game of Life"<<endl;
    exit(EXIT_FAILURE);
  }

  //all current states now need to be equal to next states
  #pragma omp parallel for schedule(static)
  for(int i=0; i<rows; ++i){
    for(int j=0; j<cols; ++j){
      cellArray[i][j]->Set_Curr_State(cellArray[i][j]->Get_Next_State());
    }
  }
}

void Grid::Run_Simulation(unsigned int iterations) {

  /*
    This is our run simulation function. It is called
    once we set up the rules and iteration count.

    For every iteration
      For every live cell
        Look around that live cell and update its neighbors
   */


  for (int i = 0; i < iterations; i++) {

    Curr_Print();

    string enter;
    cin >> enter;
    cout << "Next iteration\n";

    vector<Cell*> potential_cells;

    #pragma omp parallel for
    for (Cell* cell : live_cells) {

	unsigned int x_coord = cell->Get_X_Coord();
	unsigned int y_coord = cell->Get_Y_Coord();

	/*
	     
	  x  
	0    

	*/ 
	if (Is_Safe_Coord(x_coord - 1, y_coord - 1)) {
	  // Increase the nearby cell's neighbor count by 1
	  // Because 
          #pragma omp atomic
	  cellArray[x_coord - 1][y_coord - 1]->Add_Neighbor(1);

	  potential_cells.push_back(cellArray[x_coord - 1][y_coord - 1]);
	}

	/*
	     
	  x  
	  0  

	*/ 
	if (Is_Safe_Coord(x_coord, y_coord - 1)) {
          #pragma omp atomic
	  cellArray[x_coord][y_coord - 1]->Add_Neighbor(1);

	  potential_cells.push_back(cellArray[x_coord][y_coord - 1]);
	}

	/*
	     
	  x  
	    0

	*/ 
	if (Is_Safe_Coord(x_coord + 1, y_coord - 1)) {
          #pragma omp atomic
	  cellArray[x_coord + 1][y_coord - 1]->Add_Neighbor(1);

	  potential_cells.push_back(cellArray[x_coord + 1][y_coord - 1]);
	}

	/*
	     
	0 x  
	     

	*/ 
	if (Is_Safe_Coord(x_coord - 1, y_coord)) {
          #pragma omp atomic
	  cellArray[x_coord - 1][y_coord]->Add_Neighbor(1);

	  potential_cells.push_back(cellArray[x_coord - 1][y_coord]);
	}

	/*
	     
	  x 0
	     

	*/ 
	if (Is_Safe_Coord(x_coord + 1, y_coord)) {
          #pragma omp atomic
	  cellArray[x_coord + 1][y_coord]->Add_Neighbor(1);

	  potential_cells.push_back(cellArray[x_coord + 1][y_coord]);
	}

	/*
	0    
	  x  
	     

	*/ 
	if (Is_Safe_Coord(x_coord - 1, y_coord + 1)) {
	  #pragma omp atomic
	  cellArray[x_coord - 1][y_coord + 1]->Add_Neighbor(1);
	  
	  potential_cells.push_back(cellArray[x_coord - 1][y_coord + 1]);
	}

	/*
	  0  
	  x  
	     

	*/ 
	if (Is_Safe_Coord(x_coord, y_coord + 1)) {
          #pragma omp atomic
	  cellArray[x_coord][y_coord + 1]->Add_Neighbor(1);

	  potential_cells.push_back(cellArray[x_coord][y_coord + 1]);
	}

	/*
	    0
	  x  
	     

	*/ 
	if (Is_Safe_Coord(x_coord + 1, y_coord + 1)) {
          #pragma omp atomic
	  cellArray[x_coord + 1][y_coord + 1]->Add_Neighbor(1);

	  potential_cells.push_back(cellArray[x_coord + 1][y_coord + 1]);
	}
    }

    // go through all the live cells and see which ones will have to die
    // during the next generation
    #pragma omp parallel for
    for (int i = 0; i < live_cells.size(); i++) {
      Update_State(live_cells[i]);
      if (live_cells[i]->Get_Next_State() == 0) {
	live_cells.erase(live_cells.begin() + i);
	live_cells[i]->Set_Curr_State(0);
      }

      // reset neighbor count for next generation
      live_cells[i]->Clear_Neighbors();
    }

    if (live_cells.size() == 0) {
      cout << "All cells died. Game Over.\n";
      break;
    }

    // go through all of the dead cells and see which ones will live
    // during the next generation
    #pragma omp parallel for
    for (int i = 0; i < potential_cells.size(); i++) {
      Update_State(potential_cells[i]);
      if (potential_cells[i]->Get_Next_State() == 1) {
	live_cells.push_back(potential_cells[i]);
	potential_cells[i]->Set_Curr_State(1);
      }

      // reset neighbor count for next generation
      potential_cells[i]->Clear_Neighbors();
    }
  }
}

inline void Grid::Update_State(Cell* cell) {

  if ((cell->Get_Curr_State() == 0)) { 
    if (cell->Get_Neighbors() == 3)
      cell->Set_Next_State(1);
    else
      cell->Set_Next_State(0);
  }
  
  else {
    if ((cell->Get_Neighbors() < 2) || (cell->Get_Neighbors() > 3)) {
      cell->Set_Next_State(0);

    } else
      cell->Set_Next_State(1);
      
  }
}

void Grid::ApplyGOL(){
	
  //TODO: Modify this to work with the vector of live cells but for now just get it working 	
	
  #pragma omp parallel for schedule(static)
  for(int i=0; i<rows; ++i){
		
    for(int j=0; j<cols; ++j){
      //count alive neighbors for each cell
      Cell* current = cellArray[i][j];
      
      //bottm left
      if(Is_Safe_Coord(j-1, i+1))
	current->Add_Neighbor(cellArray[i+1][j-1]->Get_Curr_State());
      
      //left
      if(Is_Safe_Coord(j-1, i))
	current->Add_Neighbor(cellArray[i][j-1]->Get_Curr_State());
      
      //top left
      if(Is_Safe_Coord(j-1, i-1))
	current->Add_Neighbor(cellArray[i-1][j-1]->Get_Curr_State());
      
      //top
      if(Is_Safe_Coord(j, i-1))
	current->Add_Neighbor(cellArray[i-1][j]->Get_Curr_State());
      
      //top right
      if(Is_Safe_Coord(j+1, i-1))
	current->Add_Neighbor(cellArray[i-1][j+1]->Get_Curr_State());

      //right neighbor
      if(Is_Safe_Coord(j+1, i))
	current->Add_Neighbor(cellArray[i][j+1]->Get_Curr_State());
      
      //bottom right
      if(Is_Safe_Coord(j+1, i+1))
	current->Add_Neighbor(cellArray[i+1][j+1]->Get_Curr_State());
      
      //bottom	
      if(Is_Safe_Coord(j+1, i))
	current->Add_Neighbor(cellArray[i][j+1]->Get_Curr_State());
      
      //now that we have summed up the amount of alive neighbors we can perform ops
      Update_State(cellArray[i][j]);

      // we don't need neighbor information anymore for this cell
      current->Clear_Neighbors();
    }
  }
}
