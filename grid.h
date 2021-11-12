#include <iostream>
#include <cstdlib>
#include <utility>
#include <vector>

#include "cell.h"

class Grid {
	
public:
  //grid constructor takes width and length and 
  //uses that to calculate num_cells and to instantiate
  //the array of cells
  Grid(unsigned int rows, unsigned int col);
  ~Grid();
  void Curr_Print();
  void Next_Print();
  void Get_Num_Cells();
  void Get_Live_Cells();

  // get the cell pointer from a given coordinate
  Cell* Get_Cell(unsigned int x, unsigned int y) { return cellArray[x][y]; }

  // set the live cell vector. note this should only ever be called once by main
  // TODO: method to edit this vector? not sure how best to do this yet.
  void Set_Live_Cells (std::vector <Cell*> live) { live_cells = std::move(live); }
  void Print_Live_Cells();

  //pointer to the entire grid of cells
  Cell*** cellArray;

private:
  unsigned int rows;
  unsigned int cols;
  unsigned int num_cells;

  std::vector<Cell*> live_cells;
  bool Is_Safe_Coord(unsigned int x, unsigned int y);

};
