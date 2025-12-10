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
		
		void dealloc_grid (ld **X);
		
		void rand_grid (ld **X);
		
		void print_grid (ld **X);
		
		void print_arr (ld *x, size_t m);
		
		void create_file (ld **X, std :: string name);

		// Constructors
		
		// Constructor with no parameters. It is used to initialize the class from the Sim class 
		
		Mem ();
		
		// Constructor with parameters to initialize a grid of size N x M
		
		Mem (size_t n, size_t m); 
};

