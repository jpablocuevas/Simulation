# include "mem.hpp"

class LennJon: public Mem {

	private:
		
		ld sigma, epsilon, m, L;
		
		ld **X_old, **X_mid, **X_new; 
		
		ld dX;
		
		ld **V_old, **V_new; 
		
		ld **F_old, **F_mid;

		ld t = 0., dt, t_f; // Time step and duration of the simulation.
		
		size_t grid_size;
		
		void init_grid_cube ();
		
		void init_vel_rand ();
		
		ld dis (ld *, ld *); 
		
		void force (ld **, ld **); 
		
		void update (ld **, ld **); 
		
		void Verlet (ld **, ld **);
		
		void X_step (ld **, ld **, ld **);

	public:
		
		// Class constructor. It initializes the simulation.
		
		LennJon (size_t set_grid_size, ld time_step, ld total_time, ld set_sigma, ld set_epsilon, ld set_m, ld set_cube_size);  

};


