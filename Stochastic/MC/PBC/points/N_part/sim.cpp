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
	
	//nums = rand_arr (M_rand, a_rand);
	
	// Grid initialization
	
	Mem X (no_part, no_coord);
	
	X.get_grid_size ();
	
	X.rand_grid();
	
	X.print_grid ();
	
	X.dealloc_grid ();

	/*ld dis, rand_num;
	
	file.open ("positions.txt", std :: ios :: out);
	
	// Starts the particle at the origin
	
	for (j = 0; j < n; j++) {
		
		*(x + j) = 0.;
	}
	
	// Simulation
	
	std :: cout << "Simulation start. No. of cycles: " << C << '\n';
	
	std :: cout << "Step size in each direction (x, y, z): \n";
	
	print_arr (steps, n);
	
	std :: cout << "Simulation box size (x, y, z):" << '\n';
	
	print_arr (dims, n);
	
	k = 0;
	
	// The variable k traverses the random array elements, which has a size of M - 1. Since the number of coordinates is defined at execution time, a possible bug can occur if the number of cycles is too large, since the random array elements is distributed among each coordinate, i.e., if the particle moves in a 2D plane then one must make sure that M >= 2 * C.
	
	// Main loop 
	
	for (i = 0; i < C; i ++) {
		
		for (j = 0; j < n; j ++) {
			
			// Moves the particle
			
			*(x + j) = *(x + j) + *(steps + j) * (ld) *(nums + k);
			
			k ++;
			
			// Checs PBC
			
			temp = *(x + j); // IMPORTANT
			
			if (*(x + j) >= *(dims + j)) {

				*(x + j) = - *(dims + j) + (ld) abs (temp - *(dims + j));
			}
		
			else if (*(x + j) < - *(dims + j)) {
			
				*(x + j) = *(dims + j) -  (ld) abs (temp + *(dims + j));
			}
		}

		if (i % 40 == 0) {
			
			X.create_file (to_string(i));
		}
	}
	
	file.close ();*/
}
