# include "methods.h"

int main (void) {
	
	size_t N = 3; // Number of particles;
	
	System:: ld dt = 0.1, t_f = 1000.;
	
	std:: string method = "verlet_pos";
	
	System sys (N, dt, t_f, method);

	return 0;
}
