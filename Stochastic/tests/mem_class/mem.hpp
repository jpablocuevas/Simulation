# include <iostream>
# include <iomanip>
# include <new>
# include <fstream>
# include <cstdlib>



class Mem {

	public:
		
		typedef long double ld;
		
		unsigned int i, j, k;
		
		ld **X = NULL;
		
		size_t N, M;
		
		std :: fstream file;
		
		ld **alloc_grid (void);
		
		void get_size (void);
		
		void dealloc_grid (ld **);
		
		void rand_grid (ld **);
		
		void print_grid (ld **);
		
		void print_arr (ld *, size_t);
		
		void create_file (ld **, std :: string);
		
		// Constructor with no parameters. It is used to initialize the class from the Sim class 
		
		Mem ();
		
		// Constructor with parameters to initialize a grid of size N x M
		
		Mem (size_t, size_t); 
};

