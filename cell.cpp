#include "classes.h"

Cell::Cell(){
	//default cell state
	prev_state = 0;
	curr_state = 0;
}

void Cell::Set_Curr_State(int state){
	curr_state = state;
}

void Cell::Set_Prev_State(int state){
	prev_state = state;
}

int Cell::Get_Prev_State(){
	return prev_state;
}

int Cell::Get_Curr_State(){
	return curr_state;
}
