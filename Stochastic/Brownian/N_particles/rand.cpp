# include "rand.hpp"

Rand :: Rand (std :: size_t N, unsigned int seed_1, unsigned int seed_2) {
	
	X_1_seed = seed_1;
			
	X_2_seed = seed_2;
	
	std:: cout << "Seed 1: " << seed_1 << ". Seed 2: " << seed_2 << '\n';
	
	//norm_rand ();
	
	Mem mem;
	
	ld **X_old, X_new;
	
	X = mem.alloc_matrix (N);
	
	for (i = 0; i < N; i ++) {
		
		for (j = 0; j < 3; j++) {
		
			*(*(X + i) + j) = 1.3485848;
		}
	}
	
	mem.print_matrix (X, N);
	
	mem.modify_matrix (X, N);
	
	//delete [] Z_1;
	
	//delete [] Z_2;
	
	mem.print_matrix (X, N);
	
	mem.dealloc_matrix (X, N);

}


void Rand:: norm_rand (void) {
	
	std:: cout << "Seed 1: " << X_1_seed << ". Seed 2: " << X_2_seed << '\n';
	
	Z_1 = new ld [M];
	
	Z_2 = new ld [M];
	
	for (i = 0; i < M; i++) {

		X_1 = (a_1 * X_1_seed + b_1) - (unsigned int) ((a_1 * X_1_seed + b_1) / M) * M; 

		X_2 = (a_2 * X_2_seed + b_2) - (unsigned int) ((a_2 * X_2_seed + b_2) / M) * M;

// This is the computation of the remainder of the Euclidean division of a * seed + b and M, i.e., (a * seed + b) mod M.

		U_1 = (ld) X_1 / M;

		U_2 =  (ld) X_2 / M;

		*(Z_1 + i) = sqrt (- 2 * log (U_1)) * cos (2 * pi * U_2);

		*(Z_2 + i) = sqrt (- 2 * log (U_1)) * sin (2 * pi * U_2);

		X_1_seed = X_1;

		X_2_seed = X_2;
	} 
	
	std:: cout << "Random sequence finished" << '\n';
}
		

		
		
