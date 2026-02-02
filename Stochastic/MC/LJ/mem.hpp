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
		
		// Constructor overloading to set a tens, grid or arr.

		Mem (void); 

		Mem (size_t, size_t, size_t); // Sets tens.

		Mem (size_t, size_t); // Sets grid.

		Mem (size_t); // Sets arr.
		
		typedef long double ld;

		size_t i, j, k; // Used for cycles. 

		size_t n, m, l; // Sizes of tens, grid and arr.

		ld ***tens = NULL; // tens pointer
		
		ld **grid = NULL; // grid pointer

		ld *arr = NULL; // arr pointer
		
		std :: fstream file; // File object to print particles coordinates. 
		
		// Dynamic memory allocation for array, grid and "tensor".

		ld ***alloc_tens (void); 

		ld **alloc_grid (void); 
		
		ld *alloc_arr (void); 

		void get_tens_size (void);

		void get_grid_size (void);

		void get_arr_size (void);

		void dealloc_tens (ld ***);
		
		void dealloc_grid (ld **);

		void dealloc_arr (ld *);
		
		// Sets tens, grid and arr to random numbers

		void set_tens_rand (ld ***);

		void set_grid_rand (ld **);
		
		void set_arr_rand (ld *);
		
		// Printing methods

		void print_tens (ld ***);

		void print_grid (ld **);
		
		void print_arr (ld *);
		
		void create_file (ld **, unsigned int);

};



