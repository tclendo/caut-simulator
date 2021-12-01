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
