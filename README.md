Grid implementation:

	The grid class is implemented currently as a container for an array of
	dynamically allocated cell classes. Thus inorder to access the cell
	object's attributes you must use -> and not . You can print the grid with
	a call to Print(). The current method of cells being classes is not
	essential and should we see reason to we can just have a normal array of
	ints. My reasoning behind having them be classes is to allow for more
	complexity later down the line in our project. 

Cell implementation:

	The cell class is implemented very basically with an integer value
	representing its state and some set state and get state functions.

Using these classes:

	As mentioned in the grid implementation the cells are dynamically
	allocated so you must use -> in order to access their attributes. State is
	private so you must use the set and get functions in order to modify it.  

Using randomize:
	
	All randomized runs must be run on files of the format raN.caut where N is 
	the specific random file you want to run. This file should only contain the
	rows and columns values. This is slightly convoluted but it was the easiest
	way to keep the original file reading functionality unchanged. Random file 
	example: "ra1.caut". Because of the way file name checking is done at least
	for now all input files must be atleast 2 letters long.

Using Fire Simulation (2):

	Fire simulation is run with any file in the input directory with Fire at the start 
	of its name. The rule set number is 2. There are two parameters currently. A dry brush
	amount per cell. This is a value in the range (0, 1]. This value is used to determine 
	how likely a cell is to catch on fire if it has 2 or more neighbors. There is also
	hp this is a random number in the range [1, 100] upon initialization. This number 
	is used to determine how long a cell will burn for once it has caught on fire. Once 
	this number reaches <= 0 the cell should not catch on fire again.
