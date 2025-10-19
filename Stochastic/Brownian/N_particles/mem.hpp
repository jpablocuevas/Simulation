# include <iostream>
# include <new>
# include <fstream>
# include <iomanip>
# include <ctime>
# include <cstdlib>

class Mem {

	public:
		
		typedef long double ld;
		
		unsigned int i, j, k;
		
		ld **alloc_matrix (std :: size_t);
		
		ld *alloc_array (std :: size_t);
		
		void dealloc_matrix (ld **, std :: size_t);
		
		void dealloc_array (ld *);
		
		void modify_matrix (ld **, std :: size_t);	
		
		void print_matrix (ld **, std :: size_t);
		
		void print_array (ld *, std :: size_t);
};


