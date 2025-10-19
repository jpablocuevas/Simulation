# include "sys.hpp"

int main (void) {
	
	std:: cout << std:: fixed << std:: setprecision (12);
	
	srand ( (unsigned) time (NULL));
	
	std :: size_t N = 3; // Number of particles;
	
	Sys:: ld dt = 0.1, t_f = 200.;
	
	//std:: string method = "verlet_pos";
	
	Sys sys (N, dt, t_f);
	
	/*Mem mem (N);
	
	Mem:: ld **X;
	
	X = mem.alloc_grid ();
	
	unsigned int i;
	
	for (i = 0; i < 10; i ++) {
		
		mem.set_grid_rand (X);
		
		mem.print_grid (X);
		
		std :: cout << '\n';
	}
	
	mem.dealloc_grid (X);*/

	return 0;
}
