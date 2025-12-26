# include "lj.hpp"

// Class constructor 

LennJon:: LennJon (size_t set_grid_size, ld time_step, ld total_time, ld set_sigma, ld set_epsilon): Mem () {
	
	// Simulation parameters
	
	dt = time_step;

	t_f = total_time;
	
	sigma = set_sigma;
	
	epsilon = set_epsilon;
	
	grid_size = set_grid_size;
	
	// Memory allocation 
	
	Mem mem (grid_size);
	
	X_old = mem.alloc_grid ();
	
	V_old = mem.alloc_grid ();

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
	
	Verlet (X_old, V_old);
	
	// Memory deallocation
	
	mem.dealloc_grid (X_old);
	
	mem.dealloc_grid (V_old);
	
	mem.dealloc_arr (M);
	
} // The constructor definition does not get a semi-colon at the end 
	
// Middle step for the positions, used in the Verlet integration algorithm

void LennJon:: X_step (ld **X_mid, ld ** X_old, ld **V_old) {
	
	for (i = 0; i < grid_size; i ++) {
		
		for (j = 0; j < 3; j ++) {
		
			*(*(X_mid + i) + j) = *(*(X_old + i) + j) + dt * *(*(V_old + i) + j);
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

void LennJon:: force (ld **F, ld **X) {
	
	ld d;
	
	ld s [3] = {0., 0., 0.};

	for (i = 0; i < grid_size; i ++) {
		
		for (j = 0; j < 3; j ++) {
			
			for (k = 0; k < grid_size; k ++) {
				
				if (i == k) {
				
				continue;
				
				}
				
				d = dis (*(X + i), *(X + k));
				
				*(s + j) = *(s + j) + (pow (sigma, 12.) / pow (d, 14.) + pow (sigma, 6) / (2 * pow (d, 8.))) * (*(*(X + i) + j) - *(*(X + k) + j));
			
			}
			
			*(*(F + i) + j) = 48 * epsilon * *(s + j);
			
			*(s + j) = 0.;
		}
	}
}


// Verlet algorithm module  

void LennJon :: Verlet (ld **X_old, ld **V_old) {
	 
	 // Memory allocation
	 
	Mem mem (grid_size);
	
	X_mid = mem.alloc_grid ();
	
	X_new = mem.alloc_grid ();
	
	dX = mem.alloc_grid ();
	
	V_new = mem.alloc_grid ();
	
	F_old = mem.alloc_grid ();
	
	F_mid = mem.alloc_grid ();
	 
	// Verlet loop
	
	while (t < t_f) {
		
		force (F_old, X_old);
		
		X_step (X_mid, X_old, V_old);
		
		force (F_mid, X_mid);
		
		for (i = 0; i < grid_size; i ++) {
			
			for (j = 0; j < 3; j ++) {
				
				// Position update
				
				*(*(dX + i) + j) = *(*(X_mid + i) + j) - *(*(X_old + i) + j) + *(*(F_mid + i) + j) / *(M + i) * dt * dt;
				
				*(*(X_new + i) + j) = *(*(X_mid + i) + j) + *(*(dX + i) + j);
				
				// Velocity update for the calculation of the kinetic energy
				
				*(*(V_new + i) + j) = *(*(dX + i) + j) / dt + (5 * *(*(F_mid + i) + j) - 2 * *(*(F_old + i) + j)) / (6 * *(M + i)) * dt;
				
			}
		}
		
		if ((unsigned int) t % 20  == 0) {
			
			mem.create_file (X_new, (unsigned int) t);
		}

		
		t = t + dt;
	}
	
	// Memory deallocation
	
	mem.dealloc_grid (X_mid);
	
	mem.dealloc_grid (dX);
	
	mem.dealloc_grid (X_new);
	
	mem.dealloc_grid (V_new);

	mem.dealloc_grid (F_old);
	
	mem.dealloc_grid (F_mid);

}


