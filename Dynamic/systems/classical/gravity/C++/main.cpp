# include "sys.hpp"

int main (void) {
	
	std:: cout << std:: fixed << std:: setprecision (12);
	
	srand ( (unsigned) time (NULL));
	
	std :: size_t N = 2; // Number of particles;
	
	Sys:: ld dt = 0.1, t_f = 120;
	
	std:: string method = "verlet_vel";

	Sys sys (N, dt, t_f, method);

	return 0;
}
