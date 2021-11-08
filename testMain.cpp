#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "classes.h"

using namespace std;
void usage();

int main(int argc, char* argv[]){

	if(argc < 4){
		usage();
		exit(EXIT_FAILURE);
	}
	
	unsigned int rows = atoi(argv[1]);
	unsigned int cols = atoi(argv[2]);

	//we need two grids so that when we update a new iteration
	//we have something to refernce back to
	//at the end of every computation the prev_Grid
	Grid grid(rows, cols);
	srand(time(NULL));
	
	
	unsigned int rand_amt = atoi(argv[3]);

	//randomly initialize data 
	for(int i=0; i<rand_amt; ++i){
		//get a random row index
		unsigned int rand_rows = rand() % rows;
		//get a random col index
		unsigned int rand_cols = rand() % cols;

		grid.cellArray[rand_rows][rand_cols]->Set_Prev_State(1);
	}
		
	cout<<"Enter 1 to continue and 0 to stop\n";
	int entry = 1;
	while(entry != 0){
		cin>>entry;
		//if entry != 0 we compute the next iteration of the grid
		if(entry != 0){
			for(int i=0; i<rows; ++i){
				for(int j=0; j<cols; ++j){
					//this is where neighbors are checked and
					//curr_Grid.cellArray[i][j]->SetState(x) is
					//used to update current cells state
				}
			}
			grid.Prev_Print();

/*			//this is where we would update prev grid once we are done using it to form curr grid 
 			//this method may be inefficient but for now it does the trick
 
			for(int i=0; i<row; ++i){
				for(int j=0; j<cols; ++j){
					prev_Grid.cellArray[i][j]->SetState(curr_grid.cellArray[i][j]->GetState());
				}
*/
		}
	}
}



void usage(){

	cout<<"Usage: ./testMain <rows> <cols> <amt of initial random cells>\n"<<endl;
}
