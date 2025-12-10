# include "sim.hpp"
 	
Sim :: ld * Sim :: rand_arr (unsigned int M, unsigned int a) {
	
	// It is custromary to take b = 0, so it is automatically done here. Also
	// M is usually taken to be prime
	
	unsigned int x, x0, b = 0;
	
	std:: cout << "Enter a seed" << std:: endl;
	
	std:: cin >> x0;
	
	ld *arr = new ld [M];
	
	*(arr + 0)  = (ld) x0 / M;
	
	for (i = 1; i < M; i++) {
	
		x = (a * x0 + b) - (unsigned int) ((a * x0 + b) / M) * M; // mod function
		
		if (rand () % 2 == 0) {
			
			*(arr + i) =  (ld) x / M;
		}
		
		else {
			
			*(arr + i) =   - (ld) x / M;
		}
		
		x0 = x;
	} 
	
	std :: cout << "Random array sequence finished" << '\n';

	return arr;
}

// Class constructor 

Sim :: Sim (size_t no_part, size_t no_coord, ld *steps, ld *dims, unsigned int C, unsigned int M, unsigned int a) : Mem () { 

// Initializes the Mem constructor that takes no parameters, so basically does 
// nothing. For some reason the code does not compile if one uses void in the 
// constructor argument, so it is left empty
	
	// Random array
	
	nums = rand_arr (M, a);
	
	// Memory management
	
	Mem mem (no_part, no_coord);
	
	ld **X;
	
	X = mem.alloc_grid ();
	
	// Simulation
	
	std :: cout << "Simulation start. No. of cycles: " << C << '\n';
	
	std :: cout << "Step size in each direction (x, y, z): \n";
	
	print_arr (steps, no_coord);
	
	std :: cout << "Simulation box size (x, y, z):" << '\n';
	
	print_arr (dims, no_coord);
	
	rand_count = 0;
	
	// The variable rand_count traverses the random array elements, which has a size of M - 1. Since the number of coordinates is defined at execution time, a possible bug can occur if the number of cycles is too large, since the random array elements is distributed among each coordinate, i.e., if the particle moves in a 2D plane then one must make sure that M >= 2 * C.
	
	// Main loop 
	
	for (i = 0; i < C; i ++) {
		
		for (j = 0; j < no_part; j ++) {
			
			for (k = 0; k < no_coord; k ++) {
				
				// Moves the particle along the j-th coordinate
				
				*(*(X + j) + k) = *(*(X + j) + k) + *(steps + k) * (ld) *(nums + rand_count);
				
				rand_count ++;
				
				// Checs PBC
				
				if (*(*(X + j) + k) >= *(dims + k)) {

					*(*(X + j) + k) = - *(dims + k) + (ld) abs (*(*(X + j) + k)  - *(dims + k));
				}
			
				else if (*(*(X + j) + k)  < - *(dims + k)) {
				
					*(*(X + j) + k)  = *(dims + k) -  (ld) abs (*(*(X + j) + k)  + *(dims + k));
				}
			}
		
		}

		if (i % 40 == 0) {
			
			mem.create_file (X, std :: to_string(i));
		}
	}
	
	delete [] nums;
	
	mem.dealloc_grid (X);
}


