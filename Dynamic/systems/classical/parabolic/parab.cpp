# include "parab.hpp"

Shoot :: Shoot (std :: size_t grid_size, ld time_step, ld total_time): Mem (grid_size) {
	
	// Simulation parameters
	
	dt = time_step;
	
	t_f  = total_time;
	
	// Memory allocation
	
	Mem mem (grid_size);
	
	X_old = mem.alloc_grid ();

	X_new = mem.alloc_grid ();
	
	V_old = mem.alloc_grid ();

	V_new = mem.alloc_grid ();
	
	std:: ifstream init_pos, init_vel;

	init_pos.open ("init_positions.txt", std:: ios:: in);

	init_vel.open ("init_velocities.txt", std:: ios:: in);

	if (init_pos.fail () == true ) {

		std:: cout << "Initial positions file could not be opened" << '\n';
		
		exit (0);
	}

	if (init_vel.fail () == true) {

		std:: cout << "Initial velocities file could not be opened" << '\n';
		
		exit (0);
	}

	// Reading the initial conditions from a file
	
	for (i = 0; i < grid_size; i ++) {
		
		init_pos >> *(*(X_old + i) + 0) >> *(*(X_old + i) + 1) >> *(*(X_old + i) + 2);
		
		init_vel >> *(*(V_old + i) + 0) >> *(*(V_old + i) + 1) >> *(*(V_old + i) + 2);
	}
	
	init_pos.close ();
	
	init_vel.close ();
	
	// Initial conditions
	
	std :: cout << "Initial positions: " << '\n';
	
	mem.print_grid (X_old);
	
	std :: cout << '\n';
	
	std :: cout << "Initial velocities: " << '\n';
	
	mem.print_grid (V_old);
	
	std :: cout << '\n';
	
	std :: cout << "Number of particles: " << N << '\n';
	
	std :: cout << '\n';
	
	// Calling the simuiation algorithm
	
	verlet_vel (X_old, V_old, X_new, V_new, grid_size);
	
	mem.dealloc_grid (X_old);
	
	mem.dealloc_grid (V_old);
	
	mem.dealloc_grid (X_new);
	
	mem.dealloc_grid (V_new);
}

void Shoot :: acc (ld **X, ld **A, std :: size_t N) {

	for (i = 0; i < N; i ++) {
		
		for (j = 0; j < 3; j ++) {
		
			switch (j) {
				
				case 2:
					
					*(*(A + i) + j) = - g;
					
				break;
				
				default:
				
				*(*(A + i) + j) = 0.;
				
				break;	
			}	
		}
	}
}

void Shoot :: V_step (ld **V_new, ld **V_mid, ld **A_new, std :: size_t N) {
	
	for (i = 0; i < N; i ++) {
		
		for (j = 0; j < 3; j ++) {
				
			*(*(V_new + i) + j) = *(*(V_mid + i) + j) + dt / 2. *  *(*(A_new + i) + j);
		}
	}
}

void Shoot :: update (ld **old_coord, ld **new_coord, std :: size_t N) {
	
	for (i = 0; i < N; i++) {
		
		for (j = 0; j < 3; j++) {
			
			*(*(old_coord + i) + j) = *(*(new_coord + i) + j);
		}
	}
}

void Shoot :: verlet_vel (ld **X_old, ld **V_old, ld **X_new, ld **V_new, std :: size_t grid_size) {
	 
	 // Memory allocation
	 
	Mem mem (grid_size);

	V_mid = mem.alloc_grid ();
	
	A_old = mem.alloc_grid ();
	
	A_new = mem.alloc_grid ();
	 
	// Velocity verlet algorithm
	
	while (t < t_f) {
		
		acc (X_old, A_old, grid_size);
		
		for (i = 0; i < grid_size; i ++) {
		
			for (j = 0; j < 3; j ++) {
		
				*(*(V_mid + i) + j) = *(*(V_old + i) + j) + dt / 2. * *(*(A_old + i) + j);
				
				*(*(X_new + i) + j) = *(*(X_old + i) + j) + dt * *(*(V_mid + i) + j);
			}
		}
		
		acc (X_new, A_new, grid_size);
		
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




