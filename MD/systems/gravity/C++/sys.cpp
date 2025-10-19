# include "sys.hpp"

Sys:: Sys (std :: size_t N, ld time_step, ld total_time): Mem (N) {
	
	// Simulation parameters
	
	dt = time_step;

	t_f = total_time;
	
	// Memory allocation 
	
	Mem mem (N);
	
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
	
	for (i = 0; i < N; i ++) {

		masses >> *(M + i);
		
		init_pos >> *(*(X_old + i) + 0) >> *(*(X_old + i) + 1) >> *(*(X_old + i) + 2);
		
		init_vel >> *(*(V_old + i) + 0) >> *(*(V_old + i) + 1) >> *(*(V_old + i) + 2);
	}
	
	// Calling the simulation algorithm
		
	verlet_pos (X_old, X_new, V_old, V_new, M, N);
	
	// Memory deallocation
	
	mem.dealloc_grid (X_old);
	
	mem.dealloc_grid (X_new);
	
	mem.dealloc_grid (V_old);
	
	mem.dealloc_grid (V_new);

} // The constructor definition does not get a semi-colon at the end 
	
// Module that creates the "middle" step coordinates for the position Verlet algorithm


void Sys:: X_step (ld **X_mid, ld ** X_old, ld **V_old, std :: size_t N) {

	for (i = 0; i < N; i ++) {
		
		for (j = 0; j < 3; j ++) {
		
			*(*(X_mid + i) + j) = *(*(X_old + i) + j) + dt / 2. * *(*(V_old + i) + j);
		}
	}
}

// Module that updates old to new coordinates of all particles

void Sys:: update (ld **old_coord, ld **new_coord, std :: size_t N) {

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
	
	ld s = 0.;
	
	ld d, G = 4. * pi * pi; 
	
	for (i = 0; i < N; i ++) { // Acceleration on i-th particle
		
		std :: cout << "Here 1" << '\n';
		
		for (j = 0; j < 3; j ++) { // For the three Cartesian compontens
			
			std :: cout << "Here 2" << '\n';
			
			s = 0.;
			
			for (k = 0; k < N; k ++) { // Acceleration due to other particles
				
				std :: cout << "Here 3" << '\n';
				
				std :: cout << "k = " << k << '\n';
				
				if (k == i) {
					
					s = 0.;
					
					break;
				}
				
				
				d = dis (*(X + i), *(X + k));
				
				std :: cout << d << '\n';
			
				s = s + *(M + k) * (*(*(X + i) + j) - *(*(X + k) + j)) / pow (d, 3); 
				
				//std :: cout << s << '\n';
			}
			
			*(*(A + i) + j) = - G * s;
		}
	}
}


// Verlet algorithm functions

void Sys:: verlet_pos (ld **X_old, ld **X_new, ld **V_old, ld **V_new, ld *M, std :: size_t N) {
	
	// Memory allocation 
	
	Mem mem (N);

	X_mid = mem.alloc_grid ();
	
	A_mid = mem.alloc_grid ();
	
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
	
	std :: cout << '\n';

	// "Kicking of", the simulation, i.e., generating the middle step"
	
	X_step (X_mid, X_old, V_old, N);
	
	//acc (A_mid, X_mid, M, N);

	// Verlet algorithm
	
	t = t + dt;
	
	while (t < t_f) {

		for (i = 0; i < N; i ++) { 

			for (j = 0; j < 3; j ++) {
			
				*(*(X_mid + i) + j) = *(*(X_old + i) + j) + dt / 2. * *(*(V_old + i) + j);
				*(*(V_new + i) + j) = *(*(V_old + i) + j) + dt * *(*(A_mid + i) + j);
				
				*(*(X_new + i) + j) = *(*(X_mid + i) + j) + dt / 2. * *(*(V_new + i) + j);
			}
			
			//acc (A_mid, X_mid, M, N);
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


