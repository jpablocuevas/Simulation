# include <iostream>
# include <iomanip>
# include <cmath>
# include <fstream>


class Pend {
	
	public:
		
		typedef long double ld;
		
		Pend (ld, ld, ld, ld, ld, ld);
		
	private:
		
		ld t;
		
		ld theta_t_old ,theta_t_mid, theta_t_new;
		
		ld theta_tt_old, theta_tt_new;
		
		ld theta_old, theta_new;
		
		ld *x = NULL; 
		
		std:: fstream file;
		
		ld g_val, l_val;
		
		ld acc (ld);
		
		void Verlet_vel (ld, ld);
		
};




