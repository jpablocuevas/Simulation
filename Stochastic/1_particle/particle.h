class Particle {
	
	private:
		
		uint n; 
		
		size_t d;
		
		double *x, *l;
		
		void delete_particle (void);
	
	public:
	
		void create_particle (size_t, double *);
		
		void move_particle (unsigned int);
};




