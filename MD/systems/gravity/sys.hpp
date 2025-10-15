# include "mem.hpp"

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
		
		ld *a_i_old, *a_i_mid, *a_i_new; // Acceleration vector on a specific particle.
		
		ld *M; // Array that stores the masses of all particles.
		
		ld t = 0., dt, t_f; // Time step and duration of the simulation.
		
		ld dis (ld *, ld *); 
		
		void acc (ld *, unsigned int, ld **); // Module that computes the acceleration on a particle due to all other particles
		
		void update (ld **, ld **); // Updates old coordinates to new coordiantes.
		
		void X_step (void);
		
		void verlet_pos (void);
		
		void verlet_vel (void);
		
		void stoermer_verlet (void);
		
		void beeman (void);
		
	public:
		
		// Class constructor. It initializes the simulation.
		
		System (size_t, ld, ld, std:: string);  
};


