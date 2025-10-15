# include "mem.hpp"

// ---------------------- M allocation methods ----------------------

void Mem :: set_size (size_t size) {

	N = size;
	
	std:: cout << "System size: " << N << '\n';
}

Mem :: ld **Mem ::  alloc_matrix (void) {

	ld **M;
	
	M = new ld *[N];
	
	if (M == NULL) {
	
		std:: cout << "Memory allocation failed!" << '\n';
		
		exit (0);
	}
	
	for (i = 0; i < N; i ++) {
	
		*(M + i) = new ld [3];
		
		if (*(M + i) == NULL) {
			
			std:: cout << "Memory allocation failed!" << '\n';
		
			exit (0);
		}
	}
	
	return M;
}

Mem :: ld *Mem :: alloc_vector (void) {

	ld *V;
	
	V = new ld [N];
	
	if (V == NULL) {
	
		std:: cout << "Memory allocation failed!" << '\n';
		
		exit (0);
	}
	
	return V;
}

void Mem:: dealloc_matrix (ld **M) {

	for (i = 0; i < N; i ++) {
	
		delete [] *(M + i);
	}
	
	delete [] M;
}

void Mem :: dealloc_vector (ld *V) {

	delete [] V;
}


void Mem :: modify_matrix (ld **M) {

	for (i = 0; i < N; i ++) {
	
		for (j = 0; j < 3; j ++) {
	
			*(*(M + i) + j) =  (ld) rand () / RAND_MAX;
		}
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



