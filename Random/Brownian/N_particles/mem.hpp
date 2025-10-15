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
		
		size_t N;
		
		void set_size (size_t);
		
		ld **alloc_matrix (void);
		
		ld *alloc_vector (void);
		
		void dealloc_matrix (ld **);
		
		void dealloc_vector (ld *);
		
		void modify_matrix (ld **);	
		
		void print_matrix (ld **);
};


