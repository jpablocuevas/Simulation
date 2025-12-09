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
		
		void alloc_grid (void);
		
		void dealloc_grid (void);
		
		void get_grid_size (void);
		
		void rand_grid (void);
		
		void print_grid (void);
		
		void print_arr (ld *arr, size_t arr_size);
		
		void create_file (std :: string name);
		
		// Constructors 
		
		Mem (size_t no_part, size_t no_coord); // This constructor is used when a grid wants to be created
		
		Mem (void); // Constructor with no parameters. It is used to initialize the class from the Sim class 
};

