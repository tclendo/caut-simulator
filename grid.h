#include <iostream>
#include <cstdlib>
#include <sys/cdefs.h>
#include <utility>
#include <vector>

#include "cell.h"

class Grid {
	
public:
  //grid constructor takes width and length and 
  //uses that to calculate num_cells and to instantiate
  //the array of cells
  Grid(unsigned int rows, unsigned int col, unsigned int ruleSet);
  ~Grid();
  void Curr_Print();
  void Next_Print();
  void Get_Num_Cells();
  void Get_Live_Cells();
  void ApplyRules();

  // get the cell pointer from a given coordinate
  //Cell* Get_Cell(unsigned int x, unsigned int y) { return cellArray[x][y]; }
  Cell* Get_Cell(unsigned int x, unsigned int y) { return cellArray[x][y]; }

  // set the live cell vector. note this should only ever be called once by main
  // TODO: method to edit this vector? not sure how best to do this yet.
  void Set_Live_Cells (std::vector <Cell*> live) { live_cells = std::move(live); }
  void Print_Live_Cells();

  void Run_Simulation(unsigned int iterations);

  //pointer to the entire grid of cells
  Cell*** cellArray;

private:
  unsigned int rows;
  unsigned int cols;
  unsigned int num_cells;
  int ruleSet;

  std::vector<Cell*> live_cells;

  inline bool Is_Safe_Coord(int x, int y);
  inline void Update_State(Cell* cell);
  void Prepare_Next(std::vector<Cell*> potential);

  void ApplyGOL();

};
