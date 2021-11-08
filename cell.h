class Cell {
	
	public:
		Cell();
		void Set_Curr_State(int state);
		void Set_Prev_State(int state);

		int Get_Curr_State();
		int Get_Prev_State();
	
	private:
		int curr_state;
		int prev_state;
};
