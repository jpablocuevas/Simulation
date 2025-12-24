# include "mem.hpp"

class NewtGrav: public Mem {

	private:
		
		ld pi = 3.141592653589793;

		// ------------------------- Units ------------------------

		// Distance: AU (Astronomical Units)
		// Time: days
		// Acceleration: AU^2/Days
		// Mass: SM (Solar Masses)

		// Gravitational constant
		
		ld G = 4. * pi * pi;
		
		// G=39.485279383758936; # G=4*pi^2 Y^-2*AU*MS^-1
		
		ld **X_old, **X_mid, **X_new; 
		
		ld **V_old, **V_mid, **V_new; 
		
		ld **A_old, **A_mid, **A_new;
		
		ld *M; // Stores the masses of all particles.
		
		ld *D; // Stores the distances between particles in each step
		
		ld t = 0., dt, t_f; // Time step and duration of the simulation.
		
		size_t grid_size;
		
		ld dis (ld *, ld *); 
		
		void acc (ld **, ld **); 
		
		void update (ld **, ld **); 
		
		void V_step (ld **, ld **, ld **);
		
		void verlet_vel (ld **, ld **, ld **, ld **);
		
		void X_step (ld **, ld **, ld **);

	public:
		
		// Class constructor. It initializes the simulation.
		
		NewtGrav (size_t, ld, ld);  

};


