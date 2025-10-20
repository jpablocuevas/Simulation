# include "mem.hpp"

// ---------------------------- Mem allocation methods ----------------------

// Class constructor

Mem :: Mem (std :: size_t grid_size) {
	
	N = grid_size;
}

// Allocates a 2D pointer to store in each index an array which in turns contains the Cartesian coordinates of each particle 

Mem :: ld **Mem:: alloc_grid (void) {

	X = new ld *[N];
	
	if (X == NULL) {
		
		std:: cout << "Mem allocation failed!" << '\n';
		
		exit (0);
	}
	
	for (i = 0; i < N; i++) {
		
		*(X + i) = new ld [3]; 
		
		if (*(X + i) == NULL) {
		
			std:: cout << "Mem allocation failed!" << '\n';
			
			exit (0);
		}
	}
	
	return X;
}

// This function does not directly deallocate the created grid, since the grid is to be used in the solvers code it is returned as a parameter, and is therefore "lost". This function deallocates an arbitrary 2D dynamic pointer

Mem :: ld *Mem :: alloc_array (void) {

	x = new ld [N];
	
	return x;
}

void Mem :: dealloc_grid (ld **grid) {
	
	for (i = 0; i < N; i++) {
	
		delete [] *(grid + i);
	}
	
	delete [] grid;
}

void Mem :: dealloc_array (ld *arr) {
	
	delete [] arr;
}

void Mem :: set_grid_rand (ld **grid) {
	
	signed int l = 1;
	
	for (i = 0; i < N; i ++) {
		
		for (j = 0; j < 3; j ++) { 
			
			if (rand () % 2 == 0) {
			
				l = - 1;
			}
		
			*(*(grid + i) + j) = l * (ld) rand () / RAND_MAX;
		}
	}
}

void Mem :: set_array_rand (ld *arr) {
	
	signed int l = 1;
	
	for (i = 0; i < N; i ++) {
		
		if (rand () % 2 == 0) {
			
			l = - 1;
		}
		
		*(arr + i) = l * (ld) rand () / RAND_MAX;
	}
}

// Prints matrix to the screen

void Mem :: print_grid (ld **grid) {
	
	for (i = 0; i < N; i ++) {
		
		for (j = 0; j < 3; j ++) {

			std:: cout << *(*(grid + i) + j) << ' ';
		}
		
		std:: cout << '\n';
	}
}


void Mem:: print_array (ld *arr) {
	
	for (i = 0; i < N; i ++) {
		
			std:: cout << *(arr + i) << '\n';
	}
}
// Printing tensor components to a text file

void Mem:: create_file (ld **grid, unsigned int name) {
	
	file.open ("positions" + std:: to_string (name) + ".txt", std :: ios :: out);
	
	for (i = 0; i < N; i ++) {
	
		for (j = 0; j < 3; j ++) {
	
			file << *(*(grid + i) + j) << ' ';
		}
		
		file << '\n';
	}
	
	file.close ();
}

