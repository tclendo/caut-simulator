#include <cstdint>
#include <fstream>
#include <iostream>
#include <omp.h>
#include <time.h>

extern "C" {
  #include "common.h"
}

#include "grid.h"

//#define VISUALIZATION
#define HP 50
#define HP_LOSS 3

using namespace std;

Grid::Grid(unsigned int rows, unsigned int cols, unsigned int ruleSet){
	
  this->rows = rows;
  this->cols = cols;
  this->ruleSet = ruleSet;

  //allocate whole block for the grid
  cellArray = new Cell**[rows];
	
  srand(time(NULL));
  for(int i=0; i<rows; ++i){
    
    //allocate each row
    cellArray[i] = new Cell*[cols];
    for(int j=0; j<cols; ++j){
      //instantiate objects in the row
      cellArray[i][j] = new Cell(i, j);
      cellArray[i][j]->Set_HP( (rand() % HP)+1 );
      //random dry_brush between (0,1]
      cellArray[i][j]->Set_Dry_Brush( (double)rand() / (double)((unsigned)RAND_MAX) );
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

unsigned int Grid::Get_Rows() {
	return this->rows;
}

unsigned int Grid::Get_Cols() {
	return this->cols;
}

unsigned int Grid::Get_Ruleset() {
	return this->ruleSet;
}

void Grid::Curr_Print(fstream * grid_file) {
  
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
  /*
  for(int i=0; i < rows; ++i){
    for(int j=0; j < cols; ++j){
      if(cellArray[i][j]->Get_Curr_State() == 1)
	cout << " " <<"x"<< " ";
      else	
      	cout << " " <<" "<< " ";
    }
    cout << endl;
  }
  */
  // game of life printing
  if (ruleSet == 1) {
    #pragma omp parallel for schedule(static)
    for(int i=0; i < rows; ++i){
	  #pragma omp parallel for schedule(static)
      for(int j=0; j < cols; ++j){
		Cell* curr = cellArray[i][j];

		#ifdef VISUALIZATION
		// only have to track which cells change state to add to output file
		bool change = 
			curr->Get_Curr_State() != curr->Get_Prev_State();
		int x, y;
		x = curr->Get_X_Coord();
		y = curr->Get_Y_Coord();
		#endif

        if(curr->Get_Curr_State() == 1) {

		  #ifdef VISUALIZATION	
		  if (change) {
			// by tracking which cells are changing state,
			// we only have to change those cells in the vis
			*grid_file << x << " " 
				      << y << " " << "0" << endl;
		  }
		  #endif

	      cout << " " <<"0"<< " ";
	    }

        else {

		  #ifdef VISUALIZATION
		  if (change) {
			*grid_file << x << " " 
				      << y << " " << "-" << endl;
		  }
		  #endif

	      cout << " " <<"-"<< " ";
	    }
      }
	  cout << endl;
    }
    #ifdef VISUALIZATION
    *grid_file << "\n";
    #endif
  }
  // Fire spread simulation print
  if (ruleSet == 2) {
    #pragma omp parallel for schedule(static)
    for(int i=0; i < rows; ++i){
	  #pragma omp parallel for schedule(static)
      for(int j=0; j < cols; ++j){
        Cell* curr = cellArray[i][j];

		#ifdef VISUALIZATION
		bool change = 
			curr->Get_Curr_State() != curr->Get_Prev_State();
	    int x, y;
		x = curr->Get_X_Coord();
		y = curr->Get_Y_Coord();
		#endif

        if(curr->Get_Curr_State() == 1) {
		  
		  #ifdef VISUALIZATION
	      if (change) {
			*grid_file << x << " " 
				      << y << " " << "0" << endl;
		  }
		  #endif

	      cout << " " <<"0"<< " ";
	    }

        else if (curr->Get_HP() <= 0) {	
		  #ifdef VISUALIZATION
      	  if (change) {
			*grid_file << x << " " 
				      << y << " " << "X" << endl;
		  }
          #endif

	      cout << " " <<"X"<< " ";
	    }

		else {

		  #ifdef VISUALIZATION
		  if (change) {
			*grid_file << x << " " 
				      << y << " " << "-" << endl;
		  }
		  #endif

	      cout << " " <<"-"<< " ";
		}
      }
	  cout << endl;
    }
	#ifdef VISUALIZATION
    *grid_file << "\n";
	#endif
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


void Grid::ApplyRules(){
	
  switch(ruleSet){
	
  case 1 :
    ApplyGOL();
    break;
	
  case 2 :
    ApplyFire();
    break;

  default:
    cout<<"Undefined rule set defined rule sets are:"<<endl;
    cout<<"1: Game of Life"<<endl;
	cout<<"2: Forest Fire Spread Simulation"<<endl;
    exit(EXIT_FAILURE);
  }

  double update_timer = 0.0;
  uint64_t t0;
  t0 = ReadTSC();

  //all current states now need to be equal to next states
  #pragma omp parallel for schedule(static)
  for(int i=0; i<rows; ++i){
    for(int j=0; j<cols; ++j){
      cellArray[i][j]->Set_Prev_State(cellArray[i][j]->Get_Curr_State());
      
      cellArray[i][j]->Set_Curr_State(cellArray[i][j]->Get_Next_State());
    }
  }

  // cout << "Time to update grid: " << ElapsedTime(ReadTSC() - t0) << endl;
}

//TODO: find everywhere this is used and change its name to GOL specific name to avoid confusion
inline void Grid::GOL_Update_State(Cell* cell) {

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

void Grid::Find_Live_Neighbors(Cell* cell, int i, int j)
{
      //bottm left
  if(Is_Safe_Coord(j-1, i+1))
    cell->Add_Neighbor(cellArray[i+1][j-1]->Get_Curr_State());
  
  //left
  if(Is_Safe_Coord(j-1, i))
    cell->Add_Neighbor(cellArray[i][j-1]->Get_Curr_State());
  
  //top left
  if(Is_Safe_Coord(j-1, i-1))
    cell->Add_Neighbor(cellArray[i-1][j-1]->Get_Curr_State());
  
  //top
  if(Is_Safe_Coord(j, i-1))
    cell->Add_Neighbor(cellArray[i-1][j]->Get_Curr_State());
  
  //top right
  if(Is_Safe_Coord(j+1, i-1))
    cell->Add_Neighbor(cellArray[i-1][j+1]->Get_Curr_State());

  //right neighbor
  if(Is_Safe_Coord(j+1, i))
    cell->Add_Neighbor(cellArray[i][j+1]->Get_Curr_State());
  
  //bottom right
  if(Is_Safe_Coord(j+1, i+1))
    cell->Add_Neighbor(cellArray[i+1][j+1]->Get_Curr_State());
  
  //bottom	
  if(Is_Safe_Coord(j, i+1))
    cell->Add_Neighbor(cellArray[i+1][j]->Get_Curr_State());
}

inline bool Grid::Is_Safe_Coord(int x, int y) {
  return (((x < cols) && (y < rows)) && ((x >= 0) && (y >= 0)));
}

void Grid::ApplyGOL(){
	
  double update_timer = 0.0;
  uint64_t t1;
  t1 = ReadTSC();
	
  #pragma omp parallel for schedule(static)
  for(int i=0; i<rows; ++i){
		
    for(int j=0; j<cols; ++j){
      //count alive neighbors for each cell
      Cell* current = cellArray[i][j];
			
      Find_Live_Neighbors(current, i, j);

      //now that we have summed up the amount of alive neighbors we can perform ops
      GOL_Update_State(cellArray[i][j]);

      // we don't need neighbor information anymore for this cell
      current->Clear_Neighbors();
    }
  }

  cout << "Time to apply Game Of Life rules for 1 generation: "
       << ElapsedTime(ReadTSC() - t1) << endl;
}

inline void Grid::Fire_Update_State(Cell* cell)
{
	//if cell is on fire and still has hp then decrement hp
	if(cell->Get_HP() > 0 && cell->Get_Curr_State())
	{
		cell->Set_HP(cell->Get_HP() - HP_LOSS);

		//if cell is on fire but has < 0 hp then it is dead and cant come back to life
		if(cell->Get_HP() <= 0)
			cell->Set_Next_State(0);
	}

	//if cell still has hp is not on fire and has 2 or more neighbors on fire
	else if(cell->Get_HP() > 0 && !cell->Get_Curr_State() && cell->Get_Neighbors() >= 2){
		//generate a random number (0, 1) 
		double random = (double)rand()/(unsigned int)((unsigned int)RAND_MAX+1);
		cell->Set_Next_State(random < cell->Get_Dry_Brush());
	}
}

void Grid::ApplyFire()
{
		
  double update_timer = 0.0;
  uint64_t t2;
  t2 = ReadTSC();
	
  #pragma omp parallel for schedule(static)
  for(int i=0; i<rows; ++i){
		
    for(int j=0; j<cols; ++j){
      Cell* current = cellArray[i][j];
      Find_Live_Neighbors(current, i, j);
      Fire_Update_State(current);
      current->Clear_Neighbors();
    }
  }

  cout << "Time to apply Fire Simulation rules for 1 generation: "
       << ElapsedTime(ReadTSC() - t2) << endl;
}
