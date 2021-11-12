#include "grid.h"

using namespace std;

Grid::Grid(unsigned int rows, unsigned int cols){
	
  this->rows = rows;
  this->cols = cols;
  //malloc whole block for the grid
  cellArray = (Cell***) malloc(sizeof(Cell**)*rows);
	
  //loop through cellArray instantiating cell objects
  //in theory we could simply use integer values instead of classes
  //but with classes we allow for more complexity with later implementations
  for(int i=0; i<rows; ++i){
    
    //malloc each row
    cellArray[i] = (Cell**) malloc(sizeof(Cell*)*cols);
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
  }
  for(int j=0; j<rows; ++j){
    free(cellArray[j]);
  }
  free(cellArray);
  
}

void Grid::Curr_Print() {
  
  // indexed the way it is so that the origin is in the bottom left
  // TODO: Remember how this is inefficient due to cache lines
  // potentially need to figure out the most efficient way to do this.
  // Maybe not here in print, but when performing simulation actions.
  for(int i=rows; i > 0; --i){
    for(int j=0; j < cols; ++j){
      cout << " " << cellArray[j][i - 1]->Get_Curr_State() << " ";
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

bool Grid::Is_Safe_Coord(unsigned int x, unsigned int y) {
  return ((x < cols) && (y < rows));

}
