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
