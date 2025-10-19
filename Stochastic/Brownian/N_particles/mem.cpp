# include "mem.hpp"

// ---------------------- Memory allocation methods ----------------------


Mem :: ld **Mem ::  alloc_matrix (std :: size_t N) {

	ld **X;
	
	std :: cout << "N = " << N << '\n';
	
	X = new ld *[N];
	
	if (X == NULL) {
	
		std:: cout << "Memory allocation failed!" << '\n';
		
		exit (0);
	}
	
	for (i = 0; i < N; i ++) {
	
		*(X + i) = new ld [3];
		
		if (*(X + i) == NULL) {
			
			std:: cout << "Memory allocation failed!" << '\n';
		
			exit (0);
		}
	}
	
	return X;
}

Mem :: ld *Mem :: alloc_array (std :: size_t N) {

	ld *x;
	
	x = new ld [N];
	
	if (x == NULL) {
	
		std:: cout << "Memory allocation failed!" << '\n';
		
		exit (0);
	}
	
	return x;
}

void Mem:: dealloc_matrix (ld **X, std :: size_t N) {

	for (i = 0; i < N; i ++) {
	
		delete [] *(X + i);
	}
	
	delete [] X;
}

void Mem :: dealloc_array (ld *x) {

	delete [] x;
}


void Mem :: modify_matrix (ld **X, std :: size_t N) {

	for (i = 0; i < N; i ++) {
	
		for (j = 0; j < 3; j ++) {
	
			*(*(X + i) + j) =  (ld) rand () / RAND_MAX;
		}
	}
}

void Mem :: print_matrix (ld **X, std :: size_t N) {

	for (i = 0; i < N; i ++) {
	
		for (j = 0; j < 3; j ++) {
	
			std:: cout << *(*(X + i) + j) << ' ';
		}
		
		std:: cout << '\n';
	}
}

void Mem:: print_array (ld *x, std :: size_t N) {

	for (i = 0; i < N; i ++) {
		
		std :: cout << *(x + i) << '\n';
	}
}



