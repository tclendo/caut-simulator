#include "cell.h"

Cell::Cell(unsigned int x, unsigned int y){

  // set the coordinates of the current cell instance
  this->x = x;
  this->y = y;
  
  //default cell state
  prev_state = 0;
  curr_state = 0;
  next_state = 0;

  //default flocking cell state
  flock_prev_state[0] = 0;
  flock_curr_state[0] = 0;
  flock_next_state[0] = 0;
  flock_prev_state[1] = 0;
  flock_curr_state[1] = 0;
  flock_next_state[1] = 0;

  // initialize the amount of live neighbors to 0
  live_neighbors = 0;

}

void Cell::GOL_Update_State() {

  if ((Get_Curr_State() == 0)) { 
    if (Get_Neighbors() == 3)
      Set_Next_State(1);
    else
      Set_Next_State(0);
  }
  
  else {
    if ((Get_Neighbors() < 2) || (Get_Neighbors() > 3)) {
      Set_Next_State(0);

    } else
      Set_Next_State(1);
      
  }
}
