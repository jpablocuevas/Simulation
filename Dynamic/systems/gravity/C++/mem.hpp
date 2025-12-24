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
		
		Mem (size_t);
		
		Mem ();
		
		typedef long double ld;

		unsigned int i, j, k, l; // Used for cycles. 
		
		size_t N; // Number of particles in the simulation
		
		std:: fstream file; // File object to print particles coordinates. 
		
		ld **alloc_grid (void);
		
		ld *alloc_arr (void);
		
		void get_size (void);

		void dealloc_grid (ld **grid);
		
		void dealloc_arr (ld *arr);
		
		void set_grid_rand (ld **grid);
		
		void set_arr_rand (ld *arr);
		
		void print_grid (ld **grid);
		
		void print_arr (ld *arr);
		
		void create_file (ld **grid, unsigned int);
		
		ld **X = NULL;
		
		ld *x = NULL;
		
};



