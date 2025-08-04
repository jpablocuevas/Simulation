# include "mem.h"

// Allocates a 2D pointer to store in each index an array which in turns contains the Cartesian coordinates of each particle 

ld **Mem:: alloc_grid (void) {

	grid = new ld* [N];
	
	if (grid == NULL) {
		
		std:: cout << "Memory allocation failed!" << '\n';
		
		exit (1);
	}
	
	for (i = 0; i < N; i++) {
		
		* (grid + i) = new ld [3]; // For the three Cartesian coordinates
		
		if (* (grid + i) == NULL) {
		
			std:: cout << "Memory allocation failed!" << '\n';
			
			exit (1);
		}
	}
	
	return grid;
}

// This function does not directly deallocate the created grid, since the grid is to be used in the solvers code it is returned as a parameter, and is therefore "lost". This function deallocates an arbitrary 2D dynamic pointer

void Mem:: dealloc_grid (ld **tens, size_t tens_size) {
	
	for (i = 0; i < tens_size; i++) {
	
		delete [] * (tens + i);
	}
	
	delete [] tens;
}

void Mem:: fill_grid (void) {

	for (i = 0; i < n; i ++) {
		
		for (j = 0; j < m; j ++) {
		
			* (* (grid + i) + j) = (ld) rand () / RAND_MAX;
		}
	}
}

// Printing tensor components to a text file

void Mem:: print_grid (size_t rank) {
	
	file.open ("positions.txt");
	
	for (i = 0; i < n; i ++) {
	
		for (j = 0; j < m; j ++) {
	
			file << *( * (grid + i) + j) << ' ';
		}
		
		file << '\n';
	}
	
	file.close ();
}




