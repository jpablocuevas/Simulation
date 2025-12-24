# include "mem.hpp"

// Class constructor that does nothing

Mem :: Mem () {
	
	// For some reason the code does not compile if "void" is added to the argument in the constructor, so it is left empty
	
}

Mem :: Mem (size_t set_N, size_t set_M) {

	N = set_N;
	
	M = set_M;
}

void Mem :: get_size (void) {
	
	std :: cout << "N = " << N << ", M = " << M << '\n';
}
	
Mem :: ld ** Mem :: alloc_grid (void) {

	std :: cout << "N in func: " << N << '\n';
	
	std :: cout << "M in func: " << N << '\n';

	X = new ld *[N];
	
	if (X == NULL) {
		
		std :: cout << "Memory allocation failed.";
		
		exit (1);
	}
	
	for (i = 0; i < N; i ++) {
		
		*(X + i) = new ld [M];
		
		if (*(X + i) == NULL) {
			
			std :: cout << "Memory allocation failed.";
		
			exit (1);
		}
	}
	
	return X;
}

void Mem :: dealloc_grid (ld **X) {

	for (i = 0; i < N; i ++) {
	
		delete [] *(X + i);
	}
	
	delete [] X;
}

void Mem :: rand_grid (ld **X) {
	
	ld num;
	
	for (i = 0; i < N; i ++) {
		
		for (j = 0; j < M; j ++) {
		
			if (rand () % 2 == 0) {
				
				num = - (ld) rand () / (ld) RAND_MAX;
			}
			
			else {
				
				num = (ld) rand () / (ld) RAND_MAX;
			}
			
			*(*(X + i) + j) = num;
		}
	}
}

void Mem :: print_grid (ld **X) {
	
	for (i = 0; i < N; i ++) {
		
		for (j = 0; j < M; j ++) {
			
			std :: cout << *(*(X + i) + j) << ' ';
		}
		
		std :: cout << '\n';
	}
}

void Mem :: print_arr (ld *x, size_t m) {
	
	for (i = 0; i < m; i ++) {
	
		std :: cout << *(x + i) << ", ";
	}
	
	std :: cout << '\n';
}

void Mem :: create_file (ld **X, std :: string name) {
	
	std:: cout << std:: fixed << std:: setprecision (12);
			
	file.open ("positions" + name + ".txt", std :: ios :: out);
	
	for (i = 0; i < N; i ++) {
		
		for (j = 0; j < M; j ++) {
		
			file << *(*(X + i) + j) << ' ';
		}
		
		file << '\n';
	}
	
	file.close ();
}




