# include "grav.hpp"

int main (void) {
	
	std:: cout << std:: fixed << std:: setprecision (12);
	
	srand ( (unsigned) time (NULL));
	
	size_t N = 2; // Number of particles;
	
	Mem :: ld dt = 0.1, t_f = 5000;

	NewtGrav NewtGrav (N, dt, t_f);

	return 0;
}
