# include <iostream>
# include <fstream>
# include <new>
# include <iomanip>


class rand_matrix {
		
	public:
		
		typedef long double ld;
		
		rand_matrix (ld seed, unsigned int r, unsigned int c) {
		
			X_seed = seed;
			
			cols = c;
			
			rows = r;
			
			create_matrix ();
		}
		
	private:
		
		ld *nums;
		
		std:: fstream file;
		
		unsigned int  i, cols, rows, X, X_seed;
		
		unsigned int M = pow (2, 30) - 1, a = pow (7, 5), b = 0;
	
		void create_matrix () {
		
			for (i = 0; i < M; i++) {
			
				X = (a * X_seed + b) - (unsigned int) ((a * X_seed + b) / M) * M; 

// This is the computation of the remainder of the Euclidean division of a * seed + b and M, i.e., (a * seed + b) mod M.

				*(nums + i) =  (ld) X / M;
				
				X_seed = X;
		}
		
		file. open ("rand_matrix.txt", std:: ios :: out);
		
		if (file.fail ()) {
			
			std:: cout << "File could not be openned" << '\n';
			
			exit (0);
		}
		
		for (i = 0; i < rows; i ++) {
			
			for (j = 0; j < cols ; i ++) {
			
				file >> *()
			}
		}
};

			



