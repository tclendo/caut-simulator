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
	for(int i=0; i<rows; ++i){
		for(int j=0; j<cols; ++j){
			cellArray[i][j]->Set_Curr_State(cellArray[i][j]->Get_Next_State());
		}
	}
	
}

void Grid::ApplyGOL(){
	
	//TODO: Modify this to work with the vector of live cells but for now just get it working 	
	
	for(int i=0; i<rows; ++i){
		
		for(int j=0; j<cols; ++j){
			//count alive neighbors for each cell
			unsigned int liveNeigh = 0;
			
			//bottm left
			if(Is_Safe_Coord(j-1, i+1))
				liveNeigh += cellArray[i+1][j-1]->Get_Curr_State();
	
			//left
			if(Is_Safe_Coord(j-1, i))
				liveNeigh += cellArray[i][j-1]->Get_Curr_State();

			//top left
			if(Is_Safe_Coord(j-1, i-1))
				liveNeigh += cellArray[i-1][j-1]->Get_Curr_State();

			//top
			if(Is_Safe_Coord(j, i-1))
				liveNeigh += cellArray[i-1][j]->Get_Curr_State();

			//top right
			if(Is_Safe_Coord(j+1, i-1))
				liveNeigh += cellArray[i-1][j+1]->Get_Curr_State();

			//right neighbor
			if(Is_Safe_Coord(j+1, i))
				liveNeigh += cellArray[i][j+1]->Get_Curr_State();

			//bottom right
			if(Is_Safe_Coord(j+1, i+1))
				liveNeigh += cellArray[i+1][j+1]->Get_Curr_State();

			//bottom	
			if(Is_Safe_Coord(j+1, i))
				liveNeigh += cellArray[i][j+1]->Get_Curr_State();

			//now that we have summed up the amount of alive neighbors we can perform ops
			
			//if cell is dead and it has 3 or more live neighbors it becomes live
			
			unsigned int state = cellArray[i][j]->Get_Curr_State();
			if(state == 0 && liveNeigh == 3){
				cellArray[i][j]->Set_Next_State(1);
			}
			else if(state == 1 && (liveNeigh < 2 || liveNeigh > 3)){
				cellArray[i][j]->Set_Next_State(0);
			}

		}
	}
}
