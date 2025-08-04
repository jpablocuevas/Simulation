# include "solvers.h"
# include "mem.h"

// General module that sets the parameters for the simulation

void set_system (size_t num_part, ld time_step) {
	
	N = num_part;
	
	dt = time_step;
	
	// The initial positions conditions are read from a file
	
	for (i = 0; i < N; i ++) {
		
		for (j = 0; j < 3; j ++) {
	
			* (* (init_pos + i) + j)
		}
	}
}

// Verlet algorithm functions

void Verlet:: pos_verlet (void) {

	
}

void Verlet:: vel_verlet () {


}

// Beeman algorithm functions
