# include "mem.hpp"

class Rand: public Mem {
	
	public:
		
		Rand (size_t, unsigned int , unsigned int);
		
	private:
	
		unsigned int i, n;
		
		unsigned int  X_1, X_1_seed, X_2, X_2_seed;
		
		const unsigned int a_1 = pow (7, 5), b_1 = 0;
		
		const unsigned int a_2 = pow (6, 6), b_2 = 0;
		
		const unsigned int M = pow (2, 30) - 1;
		
		const ld pi = 3.141592653589;
		
		ld U_1, U_2;
		
		ld *Z_1;
		
		ld *Z_2;
		
		void norm_rand ();
};





