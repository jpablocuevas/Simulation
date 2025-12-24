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
		
		ld *theta_old = NULL, *theta_new = NULL;
		
		ld *theta_t_old = NULL, *theta_t_mid = NULL, *theta_t_new = NULL;
		
		ld *theta_tt_old = NULL, *theta_tt_new = NULL;
		
		std :: fstream pos_file, ang_file;
		
		void acc (ld *, ld *, ld *);
		
		void update (ld *, ld *);
		
		void Verlet_vel (ld, ld);


};


