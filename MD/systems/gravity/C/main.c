# include "sys.h"


int main (void) {
	
	time_t seed;

	srand ((unsigned) time (&seed));
	
	size_t N = 3; 
	
	ld dt = 0.1, t_f = 100.;
	
	sys (N, dt, t_f);
	
	return 0;
}


