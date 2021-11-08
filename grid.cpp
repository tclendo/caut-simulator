#include <iostream>
#include <stdlib.h>
#include "classes.h"

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
			cellArray[i][j] = new Cell;
		}
	}
}

void Grid:: Prev_Print(){
	
	for(int i=0; i<rows; ++i){
		for(int j=0; j<cols; ++j){
			cout<<" "<<cellArray[i][j]->Get_Prev_State()<<" ";
		}
		cout<<endl;
	}
}

void Grid:: Curr_Print(){
	
	for(int i=0; i<rows; ++i){
		for(int j=0; j<cols; ++j){
			cout<<" "<<cellArray[i][j]->Get_Curr_State()<<" ";
		}
		cout<<endl;
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

