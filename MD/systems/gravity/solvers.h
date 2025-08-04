typedef long double ld;

class Verlet {

	private:
		
		long double **X_0, **V_0, **X, **A; // Position, velocity and acceleration 
		
		unsigned int i, j, k;
		
	
	public:
		
		void set_system (size_t, ld, ld **, ld **);
		
		void verlet_pos (void);


};

class Beeman {

	private: 
	
	public:
	
	

};
