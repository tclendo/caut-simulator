class Grid {
	
	public:
		//grid constructor takes width and length and 
		//uses that to calculate num_cells and to instantiate
		//the array of cells
		Grid(unsigned int length, unsigned int width, int ruleSet);

	private:
		unsigned int length;
		unsigned int width;
		unsigned int num_cells;

		//pointer to arrays of cells
		Cell** cellArray;

}

class Cell {
	
	public:
		SetState();
		GetState();
	
	private:
		bool state;
}
