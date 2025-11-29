# include "1part.hpp"

int main (void) {
	
	srand ( (unsigned )time (NULL));
	
	std:: cout << std:: fixed << std:: setprecision (12);
	
 	unsigned int M = 2147483647, a = 742938285;
	
	size_t n_elements;
	
	unsigned int C = 3000;
	
	size_t n = 2; // Number of coordinates of the particle
	
	Simulate :: ld step[2] = {1, 1}, box[2] = {5, 5};
	
	Simulate :: ld *s, *b;
	
	// Gets the first value of the array and then assigns it the ADRESS of the first value of the array.
	
	s = &(*(step + 0)); 
	
	b = &(*(box + 0));
	
	Simulate sim (s, b, C, M, a, n);
	
	return 0;
}




