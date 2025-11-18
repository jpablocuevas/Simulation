# include "sim.hpp"


int main (void) {
	
	Pend :: ld dt = 0.1, t_f = 5, pi = 3.141592653589;
	
	Pend :: ld theta_0 = pi / 3, theta_t_0 = 2.5, g = 9.81, l = 0.5;
	
	Pend pend (dt, t_f, theta_0, theta_t_0, g, l);

	return 0;
}



