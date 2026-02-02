# include "lj.hpp"

// Class constructor 

LennJon:: LennJon (size_t set_grid_size, ld time_step, ld total_time, ld set_sigma, ld set_epsilon, ld set_m, ld set_cube_side): Mem () {
	
	// Simulation parameters
	
	dt = time_step;

	t_f = total_time;
	
	sigma = set_sigma;
	
	epsilon = set_epsilon;
	
	m = set_m;
	
	grid_size = set_grid_size;
	
	L = set_cube_side;
	
	// Memory allocation 
	
	Mem mem (grid_size);
	
	X_old = mem.alloc_grid ();
	
	V_old = mem.alloc_grid ();

	// Initial conditions
	
	init_grid_cube ();
	
	init_vel_rand ();
	
	std :: cout << "Number of particles: " << grid_size << '\n';
	
	std :: cout << '\n';
	
	std :: cout << "Simulation parameters: " << '\n';
	
	std :: cout << "σ: " << sigma << '\n';
	
	std :: cout << "m: " << m << '\n'; 
	
	std :: cout << "ε: " << epsilon << '\n';
	

	// Calling the simulation algorithm
	
	Verlet (X_old, V_old);
	
	// Memory deallocation
	
	mem.dealloc_grid (X_old);
	
	mem.dealloc_grid (V_old);
	
} // The constructor definition does not get a semi-colon at the end 


//------------------------ General simulation modules  ------------------------

// Starts the simulation with the particles placed in a cube

void LennJon :: init_grid_cube (void) {

	for (i = 0; i < grid_size; i++) {
		
		for (j = 0; j < 3; j++) {
			
			*(*(X_old + i) + j) = 
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

LennJon :: ld LennJon:: dis (ld *x, ld *y) {

	ld s = 0., d;
	
	for (unsigned int i_loc = 0; i_loc < 3; i_loc ++) {
		
		d = *(x + i_loc) - *(y + i_loc);
		
		s = s + d * d; 
	}
	
	return sqrt (s);
}

// Force module 

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

void LennJon :: init_grid_cube (ld **X, ld L) {

}

void  LennJon :: init_vel_rand (ld **V) {

}


//------------------------ Verlet integration modules ------------------------

// Middle step for the positions, used in the Verlet integration algorithm

void LennJon :: X_step (ld **X_mid, ld ** X_old, ld **V_old) {
	
	for (i = 0; i < grid_size; i ++) {
		
		for (j = 0; j < 3; j ++) {
		
			*(*(X_mid + i) + j) = *(*(X_old + i) + j) + dt * *(*(V_old + i) + j);
		}
	}
}



// Verlet algorithm module  

void LennJon :: Verlet (ld **X_old, ld **V_old) {
	 
	 // Memory allocation
	 
	Mem mem (grid_size);
	
	X_mid = mem.alloc_grid ();
	
	X_new = mem.alloc_grid ();
	
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
				
				dX =  *(*(X_mid + i) + j) - *(*(X_old + i) + j) + *(*(F_mid + i) + j) / m * dt * dt;
				
				*(*(X_new + i) + j) = *(*(X_mid + i) + j) + dX;
				
				// Velocity update for the calculation of the kinetic energy
				
				*(*(V_new + i) + j) = dX / dt + (5 * *(*(F_mid + i) + j) - 2 * *(*(F_old + i) + j)) / (6 * m) * dt;
				
			}
		}
		
		if ((unsigned int) t % 20  == 0) {
			
			mem.create_file (X_new, (unsigned int) t);
		}

		
		t = t + dt;
	}
	
	// Memory deallocation
	
	mem.dealloc_grid (X_mid);
	
	mem.dealloc_grid (X_new);
	
	mem.dealloc_grid (V_new);

	mem.dealloc_grid (F_old);
	
	mem.dealloc_grid (F_mid);

}


