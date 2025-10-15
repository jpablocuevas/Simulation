# include "methods.hpp"

int main (void) {
	
	std:: cout << std:: fixed << std:: setprecision (12);
	
	size_t N = 3; // Number of particles;
	
	System:: ld dt = 0.1, t_f = 10;
	
	std:: string method = "verlet_pos";
	
	System sys (N, dt, t_f, method);

	return 0;
}
