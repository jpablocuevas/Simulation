# include "mem.hpp"

class Sys: public Mem {

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
		
		ld **A_old, **A_mid, **A_new;
		
		ld *M; // Array that stores the masses of all particles.
		
		ld t = 0., dt, t_f; // Time step and duration of the simulation.
		
		ld dis (ld *, ld *); 
		
		void acc (ld **, ld **, ld *, std :: size_t); 
		
		void update (ld **, ld **, std :: size_t); 
		
		void X_step (ld **, ld **, ld **, std :: size_t);
		
		void verlet_pos (ld **, ld **, ld **, ld **, ld *, std :: size_t);
		
	public:
		
		// Class constructor. It initializes the simulation.
		
		Sys (std :: size_t, ld, ld);  

};


