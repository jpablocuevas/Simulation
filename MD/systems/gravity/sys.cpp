# include "sys.hpp"

System:: System (size_t grid_size, ld time_step, ld total_time, std:: string method) {
	
	N = grid_size;

	dt = time_step;

	t_f = total_time;

	// Memory allocation

	X_old = alloc_grid ();

	X_new = alloc_grid ();

	V_old = alloc_grid ();

	V_new = alloc_grid ();

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

	if (method == "verlet_pos") {
		
		a_i_mid = new ld [3];
		
		// Memory allocation for the "middle" step 
	
		X_mid = alloc_grid ();
	
		X_step (); // Creates the first step for the algorithm, i.e., creates X_mid
		
		verlet_pos ();
		
		delete [] a_i_mid;
		
		dealloc_grid (X_mid);
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

	dealloc_grid (X_old);

	dealloc_grid (X_new);

	dealloc_grid (V_old);

	dealloc_grid (V_new);
} // The constructor definition does not get a semi-colon at the end 
	
// Module that creates the "middle" step coordinates for the position Verlet algorithm


void System:: X_step (void) {

	for (i = 0; i < N; i ++) {
		
		for (j = 0; j < 3; j ++) {
		
			*(*(X_mid + i) + j) = *(*(X_old + i) + j) + dt / 2. * *(*(V_old + i) + j);
		}
	}
}

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

	ld s = 0., d;
	
	for (i = 0; i < 3; i ++) {
		
		d = *(x + i) - *(y + i);
		
		s = s + d * d; 
	}
	
	return sqrt (s);
}

void System:: acc (ld *a, unsigned int k, ld **X) {
	
	std:: cout << "A" << '\n';
	ld *x;
	
	x = *(X + k); // Vector that keeps track of the position of the k-th particle
	
	ld s = 0.;
	
	ld d, G = 4. * pi * pi; 
	
	for (i = 0; i < 3; i ++) {
		
		 std:: cout << *(a + i) << '\n';
	}
	/*for (i = 0; i < 3; i ++) {
		
		s = 0.;

		for (j = 0; j < N; j ++) {
		
			if (k - i == 0) {
				
				s = 0.;
			}
			
			else {
				
				d = dis (x, *(X + j));
				
				s = s + *(M + j) * (*(x + i) - *(*(X + j) + i)) / pow (d, 3);
			}
		} 
		
		*(a + i) = s;
	}
	
	for (i = 0; i < 3; i ++) {
		
		*(a + i) = - G* *(a + i);
	}*/
}


// Verlet algorithm functions

void System:: verlet_pos (void) {
	
	// Verlet loop
	
	std:: cout << "N = " << N << '\n';
	
	while (t < t_f) {
	
		for (i = 0; i < N; i++) { 
			
			std:: cout << i << '\n';
			
			acc (a_i_mid, i, X_mid); 
			
			for (j = 0; j < 3; j++) { 
			
				*(*(X_mid + i) + j) = *(*(X_old + i) + j) + dt / 2. * *(*(V_old + i) + j);					
				*(*(V_new + i) + j) = *(*(V_old + i) + j) + dt * *(a_i_mid + j);
				//*(*(V_new + i) + j) = *(*(V_old + i) + j) + dt;
				
				*(*(X_new + i) + j) = *(*(X_mid + i) + j) + dt / 2. * *(*(V_new + i) + j);			
			}
		}
		
		std:: cout << "Fine" << '\n';
				
		if ( (int) t % 20 == 0) {
		
			create_file (X_new, (int) t);
		}		
		
		update (X_old, X_mid);
		
		update (X_mid, X_new);
		
		update (V_old, V_new);
		
		t = t + dt; 
	}
}



void System:: verlet_vel (void) {
	
	// Memoy allocation 
	
	V_mid = alloc_grid ();
	
	a_i_old = new ld [3];
	
	a_i_new = new ld [3];
	
	while (t < t_f) {
	
		for (i = 0; i < N; i++) { 
		
			std:: cout << i << '\n';
			
			std:: cout << "Error3" << '\n';
			
			acc (a_i_old, i, X_old);
		
			for (j = 0; j < 3; j++) { 
		
				//*(*(V_mid + i) + j) = *(*(V_old + i) + j) + dt / 2. * *(a_i_old + j);
				
				//*(*(X_new + i) + j) = *(*(X_old + i) + j) + dt * *(*(V_mid + i) + j);
			}
			
			std:: cout << "Error 5" << '\n';
			
			//acc (a_i_new, i, X_new);
			
			std:: cout << "Error 6" << '\n';
			
			for (j = 0; j < 3; j ++) {
			
				//*(*(V_new + i) + j) = *(*(V_mid + i) + j) + dt / 2. * *(a_i_new + j);
			}
		}
		
		update (X_old, X_new);
		
		update (V_old, V_mid);
		
		update (V_mid, V_new);
		
		t = t + dt; 
	}
	
	if ( (int) t % 20 == 0) {
		
		create_file (X_new, (int) t);
	}
	
	dealloc_grid (V_mid);
	
	delete [] a_i_old;
	
	delete [] a_i_new;
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
	
	// Verlet loop
	
	a_i_mid = new ld [3];
	
	while (t < t_f) {
	
		for (i = 0; i < N; i++) { 
			
			acc (a_i_mid, i, X_mid); 
			
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
}


