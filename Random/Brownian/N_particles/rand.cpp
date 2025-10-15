# include "rand.hpp"

Rand :: Rand (size_t size, unsigned int seed_1, unsigned int seed_2) {
	
	X_1_seed = seed_1;
			
	X_2_seed = seed_2;
	
	std:: cout << "Seed 1: " << seed_1 << ". Seed 2: " << seed_2 << '\n';
	
	Mem mem;
	
	mem.set_size (size);
	
	norm_rand ();
	
	delete [] Z_1;
	
	delete [] Z_2;
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
		
/*Rand:: Rand (size_t size, unsigned int seed_1, unsigned int seed_2) {
	
	Mem mem;
	
	mem.set_size (size);
	
	std:: cout << "N = " << N << '\n';
	
	/*X_1_seed = seed_1;
			
	X_2_seed = seed_2;
	
	ld **X;
	
	set_size (size);
	
	X = alloc_matrix ();
	
	norm_rand ();
	
	for (i = 0; i < N; i ++) {
		
		for (j = 0; j < 3; j ++) {
			
			*(*(X + i) + j) = *(Z_1 + i + j);
		}
	}
	
	print_matrix (X);
	
	delete [] Z_1;
	
	delete [] Z_2;
	
	dealloc_matrix (X);
}*/
		
		
