# include "lj.hpp"

int main (void) {
	
	std:: cout << std:: fixed << std:: setprecision (12);
	
	srand ( (unsigned) time (NULL));
	
	size_t N = 4; // Number of particles;
	
	LennJon:: ld dt = 0.1, t_f = 500, epsilon, sigma;
	
	sigma = 3.405 * pow (10, -10);
	
	epsilon = 1.654 * pow (10, -21);

	LennJon sim (N, dt, t_f, sigma, epsilon);

	return 0;
}
