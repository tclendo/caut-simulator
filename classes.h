
class Cell {
	
	public:
		Cell();
		void SetState(int state);
		int GetState();
	
	private:
		int state;
};

class Grid {
	
	public:
		//grid constructor takes width and length and 
		//uses that to calculate num_cells and to instantiate
		//the array of cells
		Grid(unsigned int rows, unsigned int col);
		~Grid();
		void Print();
		//pointer to arrays of cells dynamically allocated cells
		Cell*** cellArray;

	private:
		unsigned int rows;
		unsigned int cols;
		unsigned int num_cells;

};

