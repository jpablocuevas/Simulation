# include <iostream>
# include <iomanip>
# include <new>
# include <fstream>
# include <cstdlib>
# include <ctime>
# include <string>

// ---------------------------- Memory allocation class ----------------------

class Memory {

	public:
	
		typedef long double ld;

		unsigned int i, j, k; // Used for cycles. 
		
		size_t N; // Number of particles (grid size).
		
		std:: ofstream file; // File object to print particles coordinates. 
		
		ld **alloc_grid (void);

		void dealloc_grid (ld **);
		
		void init_grid_rand (ld **);
		
		void print_matrix (ld **);
		
		void print_vector (ld *);
		
		void create_file (ld **, unsigned int);

};



