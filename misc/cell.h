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

private:

  unsigned int x;
  unsigned int y;

  int curr_state;
  int next_state;
};
