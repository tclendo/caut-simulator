#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "grid.h"

using namespace std;
void usage();

int main(int argc, char* argv[]){

	if(argc != 4){
		usage();
		exit(EXIT_FAILURE);
	}
	
	unsigned int rows = atoi(argv[1]);
	unsigned int cols = atoi(argv[2]);
	unsigned int ruleSet = atoi(argv[3]);

	//we need two grids so that when we update a new iteration
	//we have something to refernce back to
	//at the end of every computation the prev_Grid
	Grid grid(rows, cols, ruleSet);
	srand(time(NULL));
	
	
	unsigned int rand_amt = atoi(argv[3]);
	
	// for(int i=0; i<rows; ++i){
	// 	for(int j=0; j<cols; ++j){
	// 		grid.cellArray[i][j]->Set_Curr_State(rand() % 2);
	// 	}
	// }
	grid.cellArray[2][2]->Set_Curr_State(1);
	grid.cellArray[2][2]->Set_Curr_State(1);
	//randomly initialize data 
	/*for(int i=0; i<rand_amt; ++i){
		//get a random row index
		unsigned int rand_rows = rand() % rows;
		//get a random col index
		unsigned int rand_cols = rand() % cols;
		
		//if we already set this cell to be alive then skip it so
		//we can be sure to initialize the proper amount of random cells
		while(grid.cellArray[rand_rows][rand_cols]->Get_Curr_State() == 1){
			rand_rows = rand() % rows;
			rand_cols = rand() % cols;
		}
		grid.cellArray[rand_rows][rand_cols]->Set_Curr_State(1);
	}*/

	char key;
	grid.Curr_Print();
	while(true){
		
	  std::system("clear");
	  grid.Curr_Print();
	  grid.ApplyRules();
	  //cin>>key;
	  sleep(1);
	}
	return 0;
}



void usage(){

	cout<<"Usage: ./testMain <rows> <cols> <rule set>\n"<<endl;
}
