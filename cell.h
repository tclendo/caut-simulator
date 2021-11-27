class Cell {
public:

  Cell(unsigned int x, unsigned int y);
  ~Cell() = default;

  int Get_Curr_State() const { return curr_state; }
  void Set_Curr_State(int state) { curr_state = state; }
  int Get_Next_State() const { return next_state; }
  void Set_Next_State(int state) { next_state = state; }
  int Get_X_Coord() const { return x; }
  int Get_Y_Coord() const { return y; }

  void Add_Neighbor(int state) { live_neighbors += state; }
  void Remove_Neighbor(int state) { live_neighbors -= state; }
  void Clear_Neighbors() { live_neighbors = 0; }
  unsigned int Get_Neighbors() { return live_neighbors; }
	int Get_HP(){ return hp; }
	void Set_HP(int loss) { hp = loss; }
	double Get_Dry_Brush(){ return dry_brush; }
	void Set_Dry_Brush(double brush) { dry_brush = brush; }


private:

  unsigned int x;
  unsigned int y;

  int curr_state;
  int next_state;

  unsigned int live_neighbors;

	/*
	 fire sim specific:

	 	1. hp:			 
									Represents the amount of
								 	burnable material left in 
								 	the cell. Each cell will 
									initialize with a random 
									amount of hp>0 .

		2. dry_brush:
									Represents the amount
									of easily combustable
									material contained in 
									the cell. This is 
									different from hp 
									because in reality if
									a plot of land catches 
									on fire enough not only
									dry or dead plants
									will burn.
	*/
	double hp;
	double dry_brush;
};
