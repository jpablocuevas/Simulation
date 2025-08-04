# include <iostream>
# include <cstdlib>
# include <ctime>
# include "particle.h"


int main (void) {
	
	srand (time (NULL));
	
	size_t d = 2;
	
	double l[2] = {0.9, 0.46};
	
	Particle particle;

	particle.create_particle (d, l);
	
	unsigned int n = 20;
	
	particle.move_particle (n);
	
	return 0;
}




