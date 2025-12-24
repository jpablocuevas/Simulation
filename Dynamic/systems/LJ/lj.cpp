# include "LennJon.hpp"

// Class constructor 

LennJon:: LennJon (size_t set_grid_size, ld time_step, ld total_time): Mem () {
	
	// Simulation parameters
	
	dt = time_step;

	t_f = total_time;
	
	grid_size = set_grid_size;
	
	// Memory allocation 
	
	Mem mem (grid_size);
	
	X_old = mem.alloc_grid ();
	
	X_new = mem.alloc_grid ();
	
	V_old = mem.alloc_grid ();
	
	V_new = mem.alloc_grid ();
	
	M = mem.alloc_arr ();
	
	mem.get_size ();
	
	std :: cout << "mem in constructor: " << &mem << '\n';

	// Reading the initial conditions from a file

	std:: ifstream init_pos, init_vel, masses;

	init_pos.open ("init_positions.txt", std:: ios:: in);

	init_vel.open ("init_velocities.txt", std:: ios:: in);

	masses.open ("masses.txt", std:: ios:: in);

	if (init_pos.fail () == true ) {

		std:: cout << "Initial positions file could not be opened" << '\n';
		
		exit (0);
	}

	if (init_vel.fail () == true) {

		std:: cout << "Initival velocities file could not be opened" << '\n';
		
		exit (0);
	}

	if (masses.fail () == true) {

		std:: cout << "Masses file not be opened" << '\n';
		
		exit (0);
	}
	
	// Reading the initial conditions from a file
	
	for (i = 0; i < grid_size; i ++) {

		masses >> *(M + i);
		
		init_pos >> *(*(X_old + i) + 0) >> *(*(X_old + i) + 1) >> *(*(X_old + i) + 2);
		
		init_vel >> *(*(V_old + i) + 0) >> *(*(V_old + i) + 1) >> *(*(V_old + i) + 2);
	}
	
	init_pos.close ();
	
	init_vel.close ();
	
	masses.close ();
	
	// Initial conditions
	
	std :: cout << "Initial positions: " << '\n';
	
	mem.print_grid (X_old);
	
	std :: cout << '\n';
	
	std :: cout << "Initial velocities: " << '\n';
	
	mem.print_grid (V_old);
	
	std :: cout << '\n';
	
	std :: cout << "Number of particles: " << grid_size << '\n';
	
	std :: cout << '\n';
	
	std :: cout << "Masses: " << '\n';
	
	mem.print_arr (M);
	
	std :: cout << '\n';
	
	// Calling the simulation algorithm
	
	verlet_vel (X_old, V_old, X_new, V_new);
	
	// Memory deallocation
	
	mem.dealloc_grid (X_old);
	
	mem.dealloc_grid (X_new);
	
	mem.dealloc_grid (V_old);
	
	mem.dealloc_grid (V_new);
	
	mem.dealloc_arr (M);
	
} // The constructor definition does not get a semi-colon at the end 
	
// Middle step for the positions, used in the Position-Verlet algorithm

void LennJon:: X_step (ld **X_mid, ld ** X_old, ld **V_old) {
	
	for (i = 0; i < grid_size; i ++) {
		
		for (j = 0; j < 3; j ++) {
		
			*(*(X_mid + i) + j) = *(*(X_old + i) + j) + dt / 2. * *(*(V_old + i) + j);
		}
	}
}

// Middle step for the velocity, used in the Velocity-Verlet algorithm 

void LennJon :: V_step (ld **V_new, ld **V_mid, ld **A_new) {
	
	for (i = 0; i < grid_size; i ++) {
		
		for (j = 0; j < 3; j ++) {
				
			*(*(V_new + i) + j) = *(*(V_mid + i) + j) + dt / 2. *  *(*(A_new + i) + j);
		}
	}
}

// Module that updates old to new coordinates of all particles

void LennJon :: update (ld **old_coord, ld **new_coord) {
	
	for (i = 0; i < grid_size; i++) {
		
		for (j = 0; j < 3; j++) {
			
			*(*(old_coord + i) + j) = *(*(new_coord + i) + j);
		}
	}

}

// Module that computes the distance between two particles 

Mem:: ld LennJon:: dis (ld *x, ld *y) {

	ld s = 0., d;
	
	for (unsigned int i_loc = 0; i_loc < 3; i_loc ++) {
		
		d = *(x + i_loc) - *(y + i_loc);
		
		s = s + d * d; 
	}
	
	return sqrt (s);
}

void LennJon:: acc (ld **A, ld **X) {
	
	ld d;
	
	ld s[3] = {0., 0., 0.}; // Stores the sum of each coordinate contribution

	for (i = 0; i < grid_size; i ++) {

}


// Verlet-velocity module 

void LennJon :: verlet_vel (ld **X_old, ld **V_old, ld **X_new, ld **V_new) {
	 
	 // Memory allocation
	 
	Mem mem (grid_size);
	
	V_mid = mem.alloc_grid ();

	A_old = mem.alloc_grid ();
	
	A_new = mem.alloc_grid ();
	
	D = mem.alloc_arr ();
	 
	// Velocity-Verlet loop
	
	while (t < t_f) {
	
		acc (A_old, X_old);
		
		mem.print_grid (A_old);
		
		std :: cout << '\n';
		
		for (i = 0; i < grid_size; i ++) {
		
			for (j = 0; j < 3; j ++) {
		
				*(*(V_mid + i) + j) = *(*(V_old + i) + j) + dt / 2. * *(*(A_old + i) + j);
				
				*(*(X_new + i) + j) = *(*(X_old + i) + j) + dt * *(*(V_mid + i) + j);
			}
		}
		
		acc (A_new, X_new);
		
		V_step (V_new, V_mid, A_new);
		
		if ((unsigned int) t % 20  == 0) {
			
			mem.create_file (X_new, (unsigned int) t);
		}
		
		update (X_old, X_new);
		
		update (V_old, V_mid);
		
		update (V_mid, V_new);
		
		update (A_old, A_new);
		
		t = t + dt;
	}
	
	// Memory deallocation

	mem.dealloc_grid (V_mid);

	mem.dealloc_grid (A_old);
	
	mem.dealloc_grid (A_new);
	
	mem.dealloc_arr (D);
}


