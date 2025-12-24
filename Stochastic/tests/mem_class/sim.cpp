# include "sim.hpp"


Sim :: Sim (size_t set_N, size_t set_M): Mem () {

	Mem mem (set_N, set_M);
	
	std :: cout << "N in constructor: " << N << '\n';
	
	std :: cout << "M in constructor: " << M << '\n';
	
	ld **X;
	
	X = mem.alloc_grid ();
	
	mem.rand_grid (X);
	
	mem.print_grid (X);
	
	Move (X);
	
	mem.print_grid (X);
	
	mem.dealloc_grid (X);
}

void Sim :: Move (ld **X) {
	
	std :: cout << "N in func: " << N << '\n';
	
	std :: cout << "M in func: " << N << '\n';
	
	for (i = 0; i < N; i ++) {
		
		for (j = 0; j < M; j ++) {
			
			*(*(X +i) + j) = *(*(X + i) + j) + 1.5;
		}
	}
}
