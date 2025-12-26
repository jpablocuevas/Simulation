# include "mem.hpp"

class LennJon: public Mem {

	private:
		
		ld sigma, epsilon;
		
		ld **X_old, **X_mid, **dX, **X_new; 
		
		ld **V_old, **V_new; 
		
		ld **F_old, **F_mid;
		
		ld *M; // Stores the masses of all particles.
		
		ld t = 0., dt, t_f; // Time step and duration of the simulation.
		
		size_t grid_size;
		
		ld dis (ld *, ld *); 
		
		void force (ld **, ld **); 
		
		void update (ld **, ld **); 
		
		void Verlet (ld **, ld **);
		
		void X_step (ld **, ld **, ld **);

	public:
		
		// Class constructor. It initializes the simulation.
		
		LennJon (size_t set_grid_size, ld time_step, ld total_time, ld set_sigma, ld set_epsilon);  

};


