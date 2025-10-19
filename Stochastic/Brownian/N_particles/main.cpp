# include "rand.hpp"


int main (void) {
	
	srand ( (unsigned) time (NULL));
	
	std:: cout << std:: fixed << std:: setprecision (10);
	
	std :: size_t N = 14;
	
	unsigned int seed_1 = 0, seed_2 = 0;
	
	seed_1 = rand ();
	
	seed_2 = rand ();
	
	Rand rand (N, seed_1, seed_2);
		
	/*Mem:: ld **T;
	
	Mem mem;
	
	mem.set_size (N);
	
	T = mem.alloc_matrix ();
	
	mem.modify_matrix (T);
	
	mem.print_matrix (T);
	
	std:: cout << '\n';
	
	mem.modify_matrix (T);
	
	mem.print_matrix (T);
	
	mem.dealloc_matrix (T);*/
	
	return 0;
}




