# include <iostream>
# include <iomanip>
# include <cmath>
# include <fstream>

class Double_pend {


	public: 
		
		typedef long double ld;
		
		Double_pend (ld, ld, ld, ld *, ld *, ld *, ld *);
		
	
	private:
		
		unsigned int i;
		
		ld t, g_val, l1, l2, m1, m2;
		
		ld *theta_old, *theta_new;
		
		ld *theta_t_old, *theta_t_mid, *theta_t_new;
		
		ld *theta_tt_old, *theta_tt_new;
		
		void acc (ld *, ld *, ld *);
		
		void update (ld *, ld *);
		
		void Verlet_vel (ld, ld);


};


