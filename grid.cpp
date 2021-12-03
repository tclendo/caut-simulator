#include <cstdint>
#include <fstream>
#include <iostream>
#include <omp.h>
#include <time.h>
#include <utility>
#include <cmath>

#include "common.h"
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

void Grid::Curr_Print(fstream * grid_file) {
  /*Print the current state of all the cells. Define the VISUALIZATION macro
	in order to write to the output file so that the data can be used with OpenGL*/
  // game of life printing
  if (ruleSet == 1) {
    for(int i=0; i < rows; ++i){
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
    for(int i=0; i < rows; ++i){
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
  // Flocking simulation print
  if (ruleSet == 3) {
    for(int i=0; i < rows; ++i){
      for(int j=0; j < cols; ++j){
        Cell* curr = cellArray[i][j];
		#ifdef VISUALIZATION
		bool change = 
			curr->Get_Curr_State() != curr->Get_Prev_State();
	    int x, y;
		x = curr->Get_X_Coord();
		y = curr->Get_Y_Coord();
		#endif
		int vec_x = curr->Flock_Get_Curr_X_State();
		int vec_y = curr->Flock_Get_Curr_Y_State();

        if(vec_x == -1) {
		  if (vec_y == -1) {
		    #ifdef VISUALIZATION
	        if (change) {
			  *grid_file << x << " " 
				      << y << " " << "/" << endl;
		    }
		    #endif
	        cout << " " <<"/"<< " ";
		  }
          if (vec_y == 0) {
		    #ifdef VISUALIZATION
	        if (change) {
			  *grid_file << x << " " 
				      << y << " " << "<" << endl;
		    }
		    #endif
	        cout << " " <<"<"<< " ";
		  }
          if (vec_y == 1) {
		    #ifdef VISUALIZATION
	        if (change) {
			  *grid_file << x << " " 
				      << y << " " << "\\" << endl;
		    }
		    #endif
	        cout << " " <<"\\"<< " ";
		  }
	    }

        else if (vec_x == 0) {	
		  if (vec_y == -1) {
		    #ifdef VISUALIZATION
	        if (change) {
			  *grid_file << x << " " 
				      << y << " " << "v" << endl;
		    }
		    #endif
	        cout << " " <<"v"<< " ";
		  }
          if (vec_y == 0) {
		    #ifdef VISUALIZATION
	        if (change) {
			  *grid_file << x << " " 
				      << y << " " << "-" << endl;
		    }
		    #endif
	        cout << " " <<"-"<< " ";
		  }
          if (vec_y == 1) {
		    #ifdef VISUALIZATION
	        if (change) {
			  *grid_file << x << " " 
				      << y << " " << "^" << endl;
		    }
		    #endif
	        cout << " " <<"^"<< " ";
		  }
	    }

		else {
		  if (vec_y == -1) {
		    #ifdef VISUALIZATION
	        if (change) {
			  *grid_file << x << " " 
				      << y << " " << "\\" << endl;
		    }
		    #endif
	        cout << " " <<"\\"<< " ";
		  }
          if (vec_y == 0) {
		    #ifdef VISUALIZATION
	        if (change) {
			  *grid_file << x << " " 
				      << y << " " << ">" << endl;
		    }
		    #endif
	        cout << " " <<">"<< " ";
		  }
          if (vec_y == 1) {
		    #ifdef VISUALIZATION
	        if (change) {
			  *grid_file << x << " " 
				      << y << " " << "/" << endl;
		    }
		    #endif
	        cout << " " <<"/"<< " ";
		  }
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

  case 3 :
	ApplyFlocking();
	break;

  default:
    cout<<"Undefined rule set defined rule sets are:"<<endl;
    cout<<"1: Game of Life"<<endl;
	cout<<"2: Forest Fire Spread Simulation"<<endl;
	cout<<"3: Flocking Simulation"<<endl;
    exit(EXIT_FAILURE);
  }

  // we clear live cells and then remake it the next generation
  live_cells.clear();
	
  double update_timer = 0.0;
  uint64_t t0;
  t0 = ReadTSC();

  //all current states now need to be equal to next states
  #pragma omp parallel for schedule(static)
  for(int i=0; i<rows; ++i){
    for(int j=0; j<cols; ++j){
      cellArray[i][j]->Set_Prev_State(cellArray[i][j]->Get_Curr_State());
      
      cellArray[i][j]->Set_Curr_State(cellArray[i][j]->Get_Next_State());
      if (cellArray[i][j]->Get_Curr_State() == 1) {
	// adding to the live cell array is a critical operation
	#pragma omp critical
	live_cells.push_back(cellArray[i][j]);
      }

      cellArray[i][j]->Clear_Neighbors();
    }
  }

  // update vector states for Flocking
  if (ruleSet == 3) {
	#pragma omp parallel for
	for (int i=0; i<rows; ++i){
	  for(int j=0; j<cols; ++j){
		Cell * cell = Get_Cell(i, j);
		// set previous state
	    cell->Flock_Set_Prev_State(cell->Flock_Get_Curr_X_State(), 
								   cell->Flock_Get_Curr_Y_State());
		// set current state
		cell->Flock_Set_Curr_State(cell->Flock_Get_Next_X_State(), 
								   cell->Flock_Get_Next_Y_State());
		// reset next state
		cell->Flock_Set_Next_State(0,0);
		cell->Set_Next_State(0);
	  }
	}
  }

  update_timer = ElapsedTime(ReadTSC() - t0);
  cout << "Time to update grid: " << update_timer << endl;

}

inline void Grid::Find_Live_Neighbors(Cell* cell, int i, int j)
{
  //bottm left
  if(Is_Safe_Coord(j-1, i+1))
    cell->Add_Neighbor(cellArray[i+1][j-1]->Get_Curr_State());

  // left
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

  omp_lock_t writelock;
  omp_init_lock(&writelock);

  #pragma omp parallel for schedule(static)
  for (int a = 0; a < live_cells.size(); a++) {
    Cell* cell = live_cells[a];

    // Edit_Neighbors(cell->Get_X_Coord(), cell->Get_Y_Coord());
    int i = cell->Get_X_Coord();
    int j = cell->Get_Y_Coord();

    // bottom left
    if(Is_Safe_Coord(j-1, i+1)) {
  	Cell *bl = cellArray[i+1][j-1];

  	// we need to increase the live neighbor count by 1
  	// and then add it to the potential cells list
  	omp_set_lock(&writelock);
  	bl->Add_Neighbor(1);
  	bl->GOL_Update_State();
  	omp_unset_lock(&writelock);
    }

    //left
    if(Is_Safe_Coord(j-1, i)) {
  	Cell* l = cellArray[i][j-1];
  	omp_set_lock(&writelock);
  	l->Add_Neighbor(1);
  	l->GOL_Update_State();
  	omp_unset_lock(&writelock);
    }

    //top left
    if(Is_Safe_Coord(j-1, i-1)) {
  	Cell* tl = cellArray[i-1][j-1];
  	omp_set_lock(&writelock);
  	tl->Add_Neighbor(1);
  	tl->GOL_Update_State();
  	omp_unset_lock(&writelock);
    }

    //top
    if(Is_Safe_Coord(j, i-1)) {
  	Cell* t = cellArray[i-1][j];
  	omp_set_lock(&writelock);
  	t->Add_Neighbor(1);
  	t->GOL_Update_State();
  	omp_unset_lock(&writelock);
    }

    //top right
    if(Is_Safe_Coord(j+1, i-1)) {
  	Cell* tr = cellArray[i-1][j+1];
  	omp_set_lock(&writelock);
  	tr->Add_Neighbor(1);
  	tr->GOL_Update_State();
  	omp_unset_lock(&writelock);
    }

    //right 
    if(Is_Safe_Coord(j+1, i)) {
  	Cell* r = cellArray[i][j+1];
  	omp_set_lock(&writelock);
  	r->Add_Neighbor(1);
  	r->GOL_Update_State();
  	omp_unset_lock(&writelock);
    }

    //bottom right
    if(Is_Safe_Coord(j+1, i+1)) {
  	Cell* br = cellArray[i+1][j+1];
  	omp_set_lock(&writelock);
  	br->Add_Neighbor(1);
  	br->GOL_Update_State();
  	omp_unset_lock(&writelock);
    }

    //bottom	
    if(Is_Safe_Coord(j, i+1)) {
  	Cell* b = cellArray[i+1][j];
  	omp_set_lock(&writelock);
  	b->Add_Neighbor(1);
  	b->GOL_Update_State();
  	omp_unset_lock(&writelock);
    }
  }

  omp_destroy_lock(&writelock);

  // #pragma omp parallel for schedule(static)
  // for(int i=0; i<rows; ++i){
  //   for(int j=0; j<cols; ++j){
  //     //count alive neighbors for each cell
  //     Cell* current = cellArray[i][j];
			
  //     Find_Live_Neighbors(current, i, j);

  //     //now that we have summed up the amount of alive neighbors we can perform ops
  //     current->GOL_Update_State();

  //     // we don't need neighbor information anymore for this cell
  //     current->Clear_Neighbors();
  //   }
  // }

  update_timer = ElapsedTime(ReadTSC() - t1);
  cout << "Time to apply Game Of Life rules for 1 generation: "
       << update_timer << endl;

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
	
  #pragma omp parallel for
  for(int i=0; i<rows; ++i){
		
    for(int j=0; j<cols; ++j){
      Cell* current = cellArray[i][j];
      Find_Live_Neighbors(current, i, j);
      Fire_Update_State(current);
      current->Clear_Neighbors();
    }
  }

  update_timer = ElapsedTime(ReadTSC() - t2);
  cout << "Time to apply Fire Simulation rules for 1 generation: "
       << update_timer << endl;
}

inline void Grid::Flocking_Update_State(Cell* cell) {
  int x = cell->Get_X_Coord();
  int y = cell->Get_Y_Coord();
  // if the cell has too many neighbors (but not too many to leave)
  // have it change direction to branch off from flock
  if (cell->Get_Neighbors() == 5) {
	cell->Flock_Set_Curr_State((int) pow(-1.0, double(rand() % 3)),
							   (int) pow(-1.0, double(rand() % 3)));
  }
  int vec_x = cell->Flock_Get_Curr_X_State();
  int vec_y = cell->Flock_Get_Curr_Y_State();
  Cell * neighbor = Get_Cell(x + vec_x, y + vec_y);
  int nbr_cur = neighbor->Get_Curr_State();
  int nbr_nxt = neighbor->Get_Next_State();
  // there is currently a "boid" there and will be next iteration too
  // try to follow direction unless it results in a collision
  int ctr = 0;
  // after 8 you've checked all neighbors, 
  // if there are none available something went wrong
  while (nbr_nxt && (ctr < 8)) {
	if (nbr_cur) {
	  vec_x = neighbor->Flock_Get_Curr_X_State();
	  vec_y = neighbor->Flock_Get_Curr_Y_State();
	}
	else {
      vec_x = neighbor->Flock_Get_Next_X_State();
	  vec_y = neighbor->Flock_Get_Next_Y_State();
	}
	neighbor = Get_Cell(x + vec_x, y + vec_y);
  	int nbr_cur = neighbor->Get_Curr_State();
  	int nbr_nxt = neighbor->Get_Next_State();
	ctr++;
  }
  if (ctr == 8) {
	  cerr << "Failure: Cycle was created by Flocking algorithm, trapped boid" << endl;
	  exit(EXIT_FAILURE);
  }
  // if the next spot is empty go there
  neighbor->Set_Next_State(1);
  cell->Set_Next_State(0);
  neighbor->Flock_Set_Next_State(vec_x, vec_y);
  cell->Flock_Set_Next_State(0,0);
}

void Grid::ApplyFlocking() {
  /* 
	 Basic version of algorithm modeling the way groups of birds or fish
	 tend to move.
   */
  double update_timer = 0.0;
  uint64_t t3;
  t3 = ReadTSC();
	
  #pragma omp parallel for schedule(static,1) ordered
  /*for(int i=0; i<rows; ++i){
    for(int j=0; j<cols; ++j){
      Cell* current = Get_Cell(i,j);*/
  // only need live cells, dont need to check them all
  for (int a = 0; a < live_cells.size(); a++) {
    Cell* current = live_cells[a];
	  // if the cell doesnt have a direction it's "empty space"
	  //if (current->Flock_Get_Curr_X_State() || current->Flock_Get_Curr_Y_State()) {
      	Find_Live_Neighbors(current, current->Get_X_Coord(), current->Get_Y_Coord());
		#pragma omp ordered
      	Flocking_Update_State(current);
      	current->Clear_Neighbors();
  }

  cout << "Time to apply Flocking Simulation rules for 1 generation: "
       << ElapsedTime(ReadTSC() - t3) << endl;
}
