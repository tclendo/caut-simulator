#include "cell.h"

Cell::Cell(unsigned int x, unsigned int y){

  // set the coordinates of the current cell instance
  this->x = x;
  this->y = y;
  
  //default cell state
  curr_state = 0;
  next_state = 0;
}
