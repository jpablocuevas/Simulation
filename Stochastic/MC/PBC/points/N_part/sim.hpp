# include "mem.hpp"

class Sim : public Mem  {

	public:
		
		Sim (size_t no_part, size_t no_coord, ld *steps, ld *dims, unsigned int C, unsigned int M, unsigned int a);
		
	private: 
		
		ld* rand_arr (unsigned int, unsigned int);
	
};

