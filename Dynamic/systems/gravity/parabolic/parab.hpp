# include "mem.hpp"

class Shoot: public Mem {
	
	private:
		
		ld t = 0., dt, t_f;
		
		ld **X_old, **X_new;
		
		ld **V_old, **V_mid, **V_new;
		
		ld **A_old, **A_new;
		
		ld g = 9.81;
		
		void update (ld **, ld **, std :: size_t); 
		
		void acc (ld **, ld **, std :: size_t);
		
		void V_step (ld **, ld **, ld **, std :: size_t);
		
		void verlet_vel (ld **, ld **, ld **, ld **, std :: size_t);
	
		public:
		
			Shoot (std :: size_t, ld, ld);

};
