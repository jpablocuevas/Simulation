# include "lj.hpp"

int main (void) {
	
	std:: cout << std:: fixed << std:: setprecision (25);
	
	srand ( (unsigned) time (NULL));
	
	size_t N = 4; // Number of particles;
	
	LennJon:: ld dt = 0.1, t_f = 1, epsilon, sigma, m, L;
	
	sigma = 3.405 * pow (10, -10);
	
	epsilon = 1.654 * pow (10, -21);
	
	m = 6.69 * pow (10, -26);
	
	L = 1 * pow (10, -8);

	LennJon sim (N, dt, t_f, sigma, epsilon, m, L);

	return 0;
}
