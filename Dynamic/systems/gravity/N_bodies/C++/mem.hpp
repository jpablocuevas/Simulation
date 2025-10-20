# include <iostream>
# include <iomanip>
# include <new>
# include <fstream>
# include <cstdlib>
# include <ctime>
# include <string>

// ---------------------------- Memory allocation class ----------------------

class Mem {

	public:
		
		Mem (std :: size_t);
		
		typedef long double ld;

		unsigned int i, j, k; // Used for cycles. 
		
		std :: size_t N; // Number of particles in the simulation
		
		std:: fstream file; // File object to print particles coordinates. 
		
		ld **alloc_grid (void);
		
		ld *alloc_array (void);

		void dealloc_grid (ld **);
		
		void dealloc_array (ld *);
		
		void set_grid_rand (ld **);
		
		void set_array_rand (ld *);
		
		void print_grid (ld **);
		
		void print_array (ld *);
		
		void create_file (ld **, unsigned int);
		
		ld **X = NULL;
		
		ld *x = NULL;
		
};



