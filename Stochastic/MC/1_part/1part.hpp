# include <iostream>
# include <iomanip>
# include <new>
# include <fstream>
# include <ctime>
# include <cstdlib>

class Simulate {
		
		public:
	 		
	 		typedef long double ld;
	 		
	 		Simulate (ld *, ld *, unsigned int, unsigned int, unsigned int, size_t);
	 	
	 	private:
	 		
	 		unsigned int i, j; // Used for cycles
	 		
	 		ld *nums; // Array of random numbers in (0, 1)
	 		
	 		size_t n; // Number of Cartesian coordinates of the particle
	 		
	 		bool acc; // For PBC
	 		
	 		ld *x = NULL, *lengths = NULL, *sizes = NULL; // Particle's position, step sizes in each direction, and box sizes
	 	
			ld *rand_arr (unsigned int, unsigned int);
			
			void print_arr (ld *, size_t);
};



