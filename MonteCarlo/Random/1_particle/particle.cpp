# include <iostream>
# include <iomanip>
# include <fstream>
# include <cstdlib>
# include "particle.h"

	
void Particle:: delete_particle (void) {
	
	delete [] x;
	
	delete [] l;
}

void Particle:: create_particle (size_t dim, double *step_size) {
	
	std:: cout << std:: fixed << std:: setprecision (6);
	
	d = dim;
	
	x = new double [d]; // Particle's position vector 
	
	l = new double [d]; // Stores the step size in each coordinate axis
	
	for (int i = 0; i < d; i++) {
		
		*(l + i) = *(step_size + i);
		
		*(x + i) = *(l + i) * (double) rand () / RAND_MAX;
	}
}
		
void Particle:: move_particle (unsigned int n_moves) {
	
	int i, j;
	
	double step;
	
	std:: ofstream file;
	
	file.open ("pos.txt");
	
	for (i = 0; i < n_moves; i++) {
		
		for (j = 0; j < d; j++) {
			
			if (rand () % 2 == 0) {
				
				step = - (double) rand () / RAND_MAX;
			}
			
			else {
				step = (double) rand () / RAND_MAX;
			}
			
			* (x + j) = * (x + j) + * (l + j) * step;
			
			file << * (x + j) << ' ';
		}
		
		file << '\n';
	}

	file.close ();
	
	delete_particle ();	
}



