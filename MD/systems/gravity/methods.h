# include <iostream>
# include <iomanip>
# include <new>
# include <fstream>
# include <cstdlib>
# include <ctime>
# include <string>

// ---------------------------- Memory allocation class ----------------------

class Memory {

	public:
	
		typedef long double ld;

		unsigned int i, j, k; // Used for cycles 
		
		size_t N; // Number of particles (grid size)
		
		std:: ofstream file; // File object to print particles coordinates 
		
		ld **alloc_grid (void);

		void dealloc_grid (ld **);
		
		void init_grid_rand (ld **);
		
		void create_file (ld **, unsigned int);

};

// ---------------------------- Differential equations numerical solvers ----------------------

class System: public Memory {

	private:
		
		ld pi = 3.141592653589793;

		// ------------------------- Units ------------------------

		// Distance: AU (Astronomical Units)
		// Time: days
		// Acceleration: AU^2/Days
		// Mass: SM (Solar Masses)

		// Gravitational constant

		// G=39.485279383758936; # G=4*pi^2 Y^-2*AU*MS^-1
		
		ld **X_old, **X_mid, **X_new;
		
		ld **V_old, **V_mid, **V_new;
		
		ld *a_i_old, *a_i_mid, *a_i_new;
		
		ld *M; // Array that stores the masses of all particles
		
		ld t = 0., dt, t_f; // Time step and duration of the simulation
		
		ld dis (ld *, ld *); // Distance function between two particles
		
		ld *acc (unsigned int, ld **); // Module that returns the acceleration on a particle due to the other particles
		
		void verlet_pos (void);
		
		void verlet_vel (void);
		
		void stoermer_verlet (void);
		
		void beeman (void);
		
		void free_system ();
		
		void update (ld **, ld **);
	
	public:
		
		// Class constructor. It initializes the simulation
		
		System (size_t, ld, ld, std:: string);  
};



