# include "1part.hpp"

int main (void) {
	
	srand ( (unsigned) time (NULL));
	
	std:: cout << std:: fixed << std:: setprecision (12);
	
 	unsigned int M = 2147483647, a = 742938285;
	
	size_t n_elements;
	
	unsigned int C = 6000;
	
	size_t n = 3; // Number of coordinates of the particle
	
	Simulate :: ld sizes[3] = {1, 1, 1}, dims[3] = {8, 8, 8};
	
	Simulate :: ld *s, *b;
	
	// Gets the first value of the array and then assigns it the ADRESS of the first value of the array.
	
	s = &(*(sizes + 0)); 
	
	b = &(*(dims + 0));
	
	Simulate sim (s, b, C, M, a, n);
	
	return 0;
}




