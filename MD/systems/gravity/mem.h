# include <iostream>
# include <iomanip>
# include <new>
# include <fstream>
# include <cstdlib>
# include <ctime>

typedef long double ld;

class Mem {

	private:

		long double **grid;
		
		std:: ofstream file;
		
		size_t N; 
		
		unsigned int i, j;
		
		ld **alloc_grid (void);

		void dealloc_grid (ld **, size_t);
		
		void fill_grid (void);
		
	public:	
		
		void fill_grid (size_t);
		
		void print_grid (size_t);

};

