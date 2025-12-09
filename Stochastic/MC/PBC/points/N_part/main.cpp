# include "sim.hpp"


int main (void) {
	
	srand ( (unsigned) time (NULL));
	
	std:: cout << std:: fixed << std:: setprecision (12);
	
 	unsigned int M = 2147483647, a = 742938285; // Rand array parameters
 	
	unsigned int C = 6000; // Number of cycles 
	
	size_t no_part = 50, no_coord = 3;
	
	Sim :: ld sizes[3] = {1, 1, 1}, dims[3] = {8, 8, 8};
	
	Sim :: ld *s, *b;
	
	// Gets the first value of the array and then assigns it the ADRESS of the first value of the array.
	
	s = &(*(sizes + 0)); 
	
	b = &(*(dims + 0));
	
	Sim sim (no_part, no_coord, s, b, C, M, a);
	
	return 0;
}
