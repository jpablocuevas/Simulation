# include "sys.hpp"

// Class constructor 

Sys:: Sys (std :: size_t grid_size, ld time_step, ld total_time, std :: string method): Mem (grid_size) {
	
	// Simulation parameters
	
	dt = time_step;

	t_f = total_time;
	
	// Memory allocation 
	
	Mem mem (grid_size);
	
	X_old = mem.alloc_grid ();
	
	X_new = mem.alloc_grid ();
	
	V_old = mem.alloc_grid ();
	
	V_new = mem.alloc_grid ();
	
	M = mem.alloc_array ();

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
	
	std :: cout << "Number of particles: " << N << '\n';
	
	std :: cout << '\n';
	
	std :: cout << "Masses: " << '\n';
	
	mem.print_array (M);
	
	// Calling the simulation algorithm
	
	if (method == "verlet_pos") {

		verlet_pos (X_old, V_old, X_new, V_new, M, grid_size);
	
	}
	
	else if (method == "verlet_vel") {
	
		verlet_vel (X_old, V_old, X_new, V_new, M, grid_size);
	}
	
	// Memory deallocation
	
	mem.dealloc_grid (X_old);
	
	mem.dealloc_grid (X_new);
	
	mem.dealloc_grid (V_old);
	
	mem.dealloc_grid (V_new);

} // The constructor definition does not get a semi-colon at the end 
	
// Middle step for the positions, used in the Position-Verlet algorithm

void Sys:: X_step (ld **X_mid, ld ** X_old, ld **V_old, std :: size_t N) {

	for (i = 0; i < N; i ++) {
		
		for (j = 0; j < 3; j ++) {
		
			*(*(X_mid + i) + j) = *(*(X_old + i) + j) + dt / 2. * *(*(V_old + i) + j);
		}
	}
}

// Middle step for the velocity, used in the Velocity-Verlet algorithm 

void Sys :: V_step (ld **V_new, ld **V_mid, ld **A_new, std :: size_t N) {
		
	for (i = 0; i < N; i ++) {
		
		for (j = 0; j < 3; j ++) {
				
			*(*(V_new + i) + j) = *(*(V_mid + i) + j) + dt / 2. *  *(*(A_new + i) + j);
		}
	}
}

// Module that updates old to new coordinates of all particles

void Sys :: update (ld **old_coord, ld **new_coord, std :: size_t N) {

	for (i = 0; i < N; i++) {
		
		for (j = 0; j < 3; j++) {
			
			*(*(old_coord + i) + j) = *(*(new_coord + i) + j);
		}
	}

}

// Module that computes the distance between two particles 

Mem:: ld Sys:: dis (ld *x, ld *y) {

	ld s = 0., d;
	
	for (i = 0; i < 3; i ++) {
		
		d = *(x + i) - *(y + i);
		
		s = s + d * d; 
	}
	
	return sqrt (s);
}

void Sys:: acc (ld **A, ld **X, ld *M, std :: size_t N) {
	
	ld d, s = 0.;
	
	unsigned int l = 0;
	
	for (j = 0; j < 3; j ++) {
			
			s = 0.;
			
			for (k = 0; k < N; k ++) {
			 	
			 	if (k == l) {
			 		
			 		s = 0.;
			 		
			 		break;
			 	}
			 	
				d = dis (*(X + l), *(X + k));

			 	s = s + *(M + j) * (*(*(X + l) + j) - *(*(X + k) + j)) / pow (d, 3);
		}
		
		*(*(A + l) + j) = - G * s;
		
		l ++;
	}
}


// Verlet-velocity module 

void Sys :: verlet_vel (ld **X_old, ld **V_old, ld **X_new, ld **V_new, ld *M, std :: size_t grid_size) {
	 
	 // Memory allocation
	 
	Mem mem (grid_size);
	
	V_mid = mem.alloc_grid ();

	A_old = mem.alloc_grid ();
	
	A_new = mem.alloc_grid ();
	 
	 // Velocity-Verlet loop
	 
	while (t < t_f) {
	
		acc (A_old, X_old, M, grid_size);
		
		for (i = 0; i < grid_size; i ++) {
		
			for (j = 0; j < 3; j ++) {
		
				*(*(V_mid + i) + j) = *(*(V_old + i) + j) + dt / 2. * *(*(A_old + i) + j);
				
				*(*(X_new + i) + j) = *(*(X_old + i) + j) + dt * *(*(V_mid + i) + j);
			}
		}
		
		acc (A_new, X_new, M, grid_size);
		
		V_step (V_new, V_mid, A_new, grid_size);
		
		if ((unsigned int) t % 20  == 0) {
			
			mem.create_file (X_new, (unsigned int) t);
		}
		
		update (X_old, X_new, grid_size);
		
		update (V_old, V_mid, grid_size);
		
		update (V_mid, V_new, grid_size);
		
		update (A_old, A_new, grid_size);
		
		t = t + dt;
	}
	
	// Memory deallocation

	mem.dealloc_grid (V_mid);

	mem.dealloc_grid (A_old);
	
	mem.dealloc_grid (A_new);

}

// Verlet-position algorithm 

void Sys:: verlet_pos (ld **X_old, ld **X_new, ld **V_old, ld **V_new, ld *M, std :: size_t grid_size) {
	
	// Memory allocation 
	
	Mem mem (grid_size);

	X_mid = mem.alloc_grid ();
	
	A_mid = mem.alloc_grid ();

	// Verlet-position loop
	
	while (t < t_f) {
		
		X_step (X_mid, X_old, V_old, N);
		
		acc (A_mid, X_mid, M, N);
		
		for (i = 0; i < N; i ++) { 

			for (j = 0; j < 3; j ++) {
			
				*(*(V_new + i) + j) = *(*(V_old + i) + j) + dt * *(*(A_mid + i) + j);
				
				*(*(X_new + i) + j) = *(*(X_mid + i) + j) + dt / 2. * *(*(V_new + i) + j);
			}
		}
		
		update (X_old, X_mid, N);
		
		update (X_mid, X_new, N);
		
		update (V_old, V_new, N);
		
		if ((unsigned int) t % 20  == 0) {
			
			mem.create_file (X_new, (unsigned int) t);
		}
		
		t = t + dt;
	}
	
	mem.dealloc_grid (X_mid);
	
	mem.dealloc_grid (A_mid);
}


