# include <iostream>
# include <new>
# include <fstream>
# include <iomanip>
# include <ctime>
# include <cstdlib>

class Mem {

	public:
		
		Mem (std :: size_t);
		
		typedef long double ld;
		
		unsigned int i, j, k;
		
		std :: size_t N;
		
		ld **alloc_matrix (void);
		
		ld *alloc_array (void);
		
		void dealloc_matrix (ld **);
		
		void dealloc_array (ld *);
		
		void set_matrix_rand (ld **);	
		
		void set_array_rand (ld *);
		
		void print_matrix (ld **);
		
		void print_array (ld *);
		
	private:
		
		ld **X = NULL;
		
		ld *x = NULL;
};


