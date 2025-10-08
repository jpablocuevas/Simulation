# include "methods.h"


// ---------------------------- Memory allocation methods ----------------------

// Allocates a 2D pointer to store in each index an array which in turns contains the Cartesian coordinates of each particle 

Memory:: ld **Memory:: alloc_grid (void) {
	
	ld **grid;
	
	grid = new ld *[N];
	
	if (grid == NULL) {
		
		std:: cout << "Memory allocation failed!" << '\n';
		
		exit (1);
	}
	
	for (i = 0; i < N; i++) {
		
		*(grid + i) = new ld [3]; // For the three Cartesian coordinates
		
		if (*(grid + i) == NULL) {
		
			std:: cout << "Memory allocation failed!" << '\n';
			
			exit (1);
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


// ---------------------------- Solvers methods ----------------------

// Constructor definition

System:: System (size_t grid_size, ld time_step, ld total_time, std:: string method) {
	
			N = grid_size;
			
			dt = time_step;
			
			t_f = total_time;
		
			// Reading the initial conditions from a file
			
			std:: ifstream init_cond, masses;
			
			init_cond.open ("init_conditions.txt", std:: ios:: in);
			
			masses.open ("masses.txt", std:: ios:: in);
			
			if (init_cond.fail () == true || masses.fail () == true) {
			
				std:: cout << "File could not be opened" << '\n';
				
				exit (1);
			}
			
			masses.close ();
			
			init_cond.close ();
			
			if (method == "verlet_pos") {
			
				verlet_pos ();
			}
			
			else if (method == "verlet_vel") {
			
				verlet_vel ();
			}
			
			else if (method == "stoermer_verlet") {
			
				stoermer_verlet ();
			}
			
			else if (method == "beeman") {
			
				beeman ();
			}
} // The constructor definition does not get a semi-colon at the end 
	
// Module that updates old to new coordinates of all particles

void System:: update (ld **old_coord, ld **new_coord) {

	for (i = 0; i < N; i++) {
		
		for (j = 0; j < 3; j++) {
			
			*(*(old_coord + i) + j) = *(*(new_coord + i) + j);
		}
	}

}

// Module that computes the distance between two particles 

Memory:: ld System:: dis (ld *x, ld *y) {

	ld s, d;
	
	for (i = 0; i < 3; i ++) {
		
		d = *(x + i) - *(y + i);
		
		s = s + d * d; 
	}
	
	return sqrt (s);
}

Memory:: ld *System:: acc (unsigned int k, ld **X) {
	
	ld *a, *x;
	
	a = new ld [3]; // Pointer that stores the three acceleration components of a particle 
	
	x = *(X + k);
	
	ld d, G = 4. * pi * pi; 
	
	for (i = 0; i < 3; i ++) {
		
		for (j = 0; j < N; j ++) {
			
			switch (k - i) {
			
				case 0:
					
					* (a + i) = 0.;
					
				break;
				
				default:
					
					d = dis (x, *(X + j));
			
					*(a + i) = *(M + j) * (*(x + i) - *(*(X + j) + i)) / d;
			}
		} 
	}
	
	for (i = 0; i < 3; i ++) {
		
		*(a + i) = G * *(a + i);
	}
	
	return a;
}


// Verlet algorithm functions

void System:: verlet_pos (void) {
	
	std:: cout << "This is fine" << '\n';
	
	// Memory allocation
	
	X_old = alloc_grid ();
	
	X_mid = alloc_grid ();
	
	X_new = alloc_grid ();
	
	V_old = alloc_grid ();
	
	V_new = alloc_grid ();
	
	// Verlet loop
	
	while (t < t_f) {
	
		for (i = 0; i < N; i++) { 
			
			a_i_mid = acc (i, X_mid); // The acceleration vector is allocated in the acc () module
			
			std:: cout << "This is fine 1" << '\n';
			
			for (j = 0; j < 3; j++) { 
		
				
				*(*(X_mid + i) + j) = *(*(X_old + i) + j) + dt / 2. * *(*(V_old + i) + j);
				std:: cout << "This is fine 2" << '\n';
				
				*(*(V_new + i) + j) = *(*(V_old + i) + j) + dt * *(a_i_mid + j);
				
				*(*(X_new + i) + j) = *(*(X_mid + i) + j) + dt / 2. * *(*(V_new + i) + j);
			}
			
			
			
			delete [] a_i_mid;
			
			
		}
		
		update (X_old, X_mid);
		
		update (X_mid, X_new);
		
		update (V_old, V_new);
		
		std:: cout << "This is fine 3" << '\n';
		
		if ( (int) t % 20 == 0) {
		
			create_file (X_new, (int) t);
		}
		
		std:: cout << "This is fine 4" << '\n';
		
		t = t + dt; 
	}
	
	dealloc_grid (X_old);
	
	dealloc_grid (X_mid);
	
	dealloc_grid (X_new);
	
	dealloc_grid (V_old);
	
	dealloc_grid (V_new);
}



void System:: verlet_vel (void) {
	
	while (t < t_f) {
	
		for (i = 0; i < N; i++) { 
			
			a_i_old = acc (i, X_old);
			
			
			for (j = 0; j < 3; j++) { 
		
				*(*(V_mid + i) + j) = *(*(V_old + i) + j) + dt / 2. * *(a_i_old + j);
				
				*(*(X_new + i) + j) = *(*(X_old + i) + j) + dt * *(a_i_old + j);
				
				*(*(X_new + i) + j) = *(*(X_mid + i) + j) + dt / 2. * *(*(V_new + i) + j);
			}
			
			
			
			delete [] a_i_old;
		}
		
		update (X_old, X_mid);
		
		update (X_mid, X_new);
		
		update (V_old, V_new);
		
		t = t + dt; 
	}
}

void System:: stoermer_verlet (void) {
	
	while (dt < t_f) {
	
		for (i = 0; i < N; i++) { 
			
			for (j = 0; j < 3; j++) { 
		
				* (*(V_mid + i) + j) = *( *(V_old + i) + j) + dt / 2;
			}
		}
	}
}

// Beeman algorithm functions

void System:: beeman (void) {
	
	// Memory allocation
	
	X_old = alloc_grid ();
	
	X_mid = alloc_grid ();
	
	X_new = alloc_grid ();
	
	V_old = alloc_grid ();
	
	V_new = alloc_grid ();
	
	// Verlet loop
	
	while (t < t_f) {
	
		for (i = 0; i < N; i++) { 
			
			a_i_old = acc (i, X_mid); // The acceleration vector is allocated in the acc () module
			
			for (j = 0; j < 3; j++) { 
		
				*(*(X_mid + i) + j) = *(*(X_old + i) + j) + dt / 2. * *(*(V_old + i) + j);
				*(*(V_new + i) + j) = *(*(V_old + i) + j) + dt * *(a_i_mid + j);
				
				*(*(X_new + i) + j) = *(*(X_mid + i) + j) + dt / 2. * *(*(V_new + i) + j);
			}
		
			delete [] a_i_mid;
		}
		
		update (X_old, X_mid);
		
		update (X_mid, X_new);
		
		update (V_old, V_new);
		
		if ( (int) t % 20 == 0) {
		
			create_file (X_new, (int) t);
		}
		
		t = t + dt; 
	}
	
	dealloc_grid (X_old);
	
	dealloc_grid (X_mid);
	
	dealloc_grid (X_new);
	
	dealloc_grid (V_old);
	
	dealloc_grid (V_new);
}


