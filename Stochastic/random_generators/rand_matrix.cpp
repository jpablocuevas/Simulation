# include <iostream>
# include <fstream>
# include <new>
# include <iomanip>
# include <ctime>
# include <cstdlib>


class Rand_matrix {
		
	public:
		
		typedef long double ld;
		
		Rand_matrix (ld seed, unsigned int r, unsigned int c) {
		
			X_seed = seed;
			
			cols = c;
			
			rows = r;
			
			create_matrix ();
		}
		
	private:
		
		ld *nums;
		
		std:: fstream file;
		
		unsigned int  i, j, cols, rows, X, X_seed;
		
		unsigned int M = pow (2, 30) - 1, a = pow (7, 5), b = 0;
	
		void create_matrix () {
			
			std:: cout << std:: fixed << std:: setprecision (10);
			
			// Memory allocation
			
			nums = new ld [M];
			
			for (i = 0; i < M; i++) {
			
				X = (a * X_seed + b) - (unsigned int) ((a * X_seed + b) / M) * M; 

// This is the computation of the remainder of the Euclidean division of a * seed + b and M, i.e., (a * seed + b) mod M.

				*(nums + i) =  (ld) X / M;
				
				X_seed = X;
		}
		
		std :: cout << "Random sequence finished." << '\n';
		
		file.open ("rand_matrix.txt", std:: ios :: out);
		
		if (file.fail ()) {
			
			std:: cout << "File could not be openned" << '\n';
			
			exit (0);
		}
		
		// Matrix filling
		 
		signed int l;
		 
		for (i = 0; i < rows; i ++) {
			
			for (j = 0; j < cols ; j ++) {
			
				if (rand () % 2 == 0 ){
					
					l = -1;
				}
				
				else {
					
					l = 1;
				}
				
				file << 365 * l * *(nums + i + j) << ' ';
			}
			
			file << '\n';
		}
		
		file.close ();
		
		delete [] nums;
	}
};


int main (void) {
	
	srand ( (unsigned) time (NULL));
	
	unsigned int seed;
	
	seed = rand ();
	
	size_t rows = 3, columns = 3;
	
	Rand_matrix rand (seed, rows, columns);
	
	
	return 0;
}

			



