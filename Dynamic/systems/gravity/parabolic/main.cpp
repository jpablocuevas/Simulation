# include "parab.hpp"


int main (void) {

	std:: cout << std:: fixed << std:: setprecision (12);
	
	srand ( (unsigned) time (NULL));
	
	std :: size_t N = 3; // Number of particles;
	
	Shoot:: ld dt = 0.1, t_f = 460.;
	
	Shoot shoot (N, dt, t_f);
	
	return 0;
}




