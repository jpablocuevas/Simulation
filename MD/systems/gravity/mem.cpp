# include "mem.hpp"

// ---------------------------- Memory allocation methods ----------------------

// Allocates a 2D pointer to store in each index an array which in turns contains the Cartesian coordinates of each particle 

Memory:: ld **Memory:: alloc_grid (void) {
	
	ld **grid;
	
	grid = new ld *[N];
	
	if (grid == NULL) {
		
		std:: cout << "Memory allocation failed!" << '\n';
		
		exit (0);
	}
	
	for (i = 0; i < N; i++) {
		
		*(grid + i) = new ld [3]; // For the three Cartesian coordinates
		
		if (*(grid + i) == NULL) {
		
			std:: cout << "Memory allocation failed!" << '\n';
			
			exit (0);
		}
	}
	
	return grid;
}

// This function does not directly deallocate the created grid, since the grid is to be used in the solvers code it is returned as a parameter, and is therefore "lost". This function deallocates an arbitrary 2D dynamic pointer

void Memory:: dealloc_grid (ld **grid) {
	
	for (i = 0; i < N; i++) {
	
		delete [] *(grid + i);
	}
	
	delete [] grid;
}

void Memory:: init_grid_rand (ld **grid) {

	for (i = 0; i < N; i ++) {
		
		for (j = 0; j < 3; j ++) { // This for loop stops at three because each particle only has three cartesian coorindates
		
			*(*(grid + i) + j) = (ld) rand () / RAND_MAX;
		}
	}
}

// Prints matrix to the screen

void Memory:: print_matrix (ld **M) {
	
	for (i = 0; i < N; i ++) {
		
		for (j = 0; j < 3; j ++) {

			std:: cout << *(*(M + i) + j) << ' ';
		}
		
		std:: cout << '\n';
	}
}

void Memory:: print_vector (ld *vec) {
	
	for (i = 0; i < N; i ++) {
		
			std:: cout << *(vec + i) << '\n';
	}
}
// Printing tensor components to a text file

void Memory:: create_file (ld **grid, unsigned int name) {
	
	file.open ("positions" + std:: to_string (name) + ".txt");
	
	for (i = 0; i < N; i ++) {
	
		for (j = 0; j < 3; j ++) {
	
			file << *(*(grid + i) + j) << ' ';
		}
		
		file << '\n';
	}
	
	file.close ();
}

