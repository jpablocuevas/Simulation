# include "mem.hpp"

// ---------------------- Memory allocation methods ----------------------

// Class constructor

Mem :: Mem (std :: size_t matrix_size) {
	
	N = matrix_size;
} 

Mem :: ld **Mem ::  alloc_matrix (void) {
	
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

Mem :: ld *Mem :: alloc_array (void) {

	x = new ld [N];
	
	if (x == NULL) {
	
		std:: cout << "Memory allocation failed!" << '\n';
		
		exit (0);
	}
	
	return x;
}

void Mem:: dealloc_matrix (ld **M) {

	for (i = 0; i < N; i ++) {
	
		delete [] *(M + i);
	}
	
	delete [] M;
}

void Mem :: dealloc_array (ld *m) {

	delete [] m;
}


void Mem :: set_matrix_rand (ld **M) {

	signed int l;
	
	for (i = 0; i < N; i ++) {
	
		for (j = 0; j < 3; j ++) {
			
			if (rand () % 2 == 0) {
			
				l = - 1;
			}
		
			*(*(M + i) + j) =  l *(ld) rand () / RAND_MAX;
		}
	}
}

void Mem :: set_array_rand (ld *m) {
		
	signed int l;
	
	for (j = 0; j < 3; j ++) {
		
		if (rand () % 2 == 0) {
			
			l = - 1;
		}
		
		*(m + i) = l * (ld) rand () / RAND_MAX;
	}
}

void Mem :: print_matrix (ld **M) {

	for (i = 0; i < N; i ++) {
	
		for (j = 0; j < 3; j ++) {
	
			std:: cout << *(*(M + i) + j) << ' ';
		}
		
		std:: cout << '\n';
	}
}

void Mem:: print_array (ld *m) {

	for (i = 0; i < N; i ++) {
		
		std :: cout << *(m + i) << '\n';
	}
}



