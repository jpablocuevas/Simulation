# include <iostream>
# include <new>
# include <iomanip>
# include <cmath>


class box_muller {
	
	public:
		
		typedef long double ld;
		
		box_muller (ld seed_1, ld seed_2) {
			
			X_1_seed = seed_1;
			
			X_2_seed = seed_2;
			
			norm_rand ();
		}
		
		void print_arr (unsigned int n) {
			
			std:: cout << "Z_1:      , Z_2:     " << '\n';
			
			for (i = 0; i < n; i ++) {
			
				std:: cout << *(Z_1+ i) << " " << *(Z_2+ i) <<  '\n';
			}
		}
		
	private:
		
		unsigned int i, n;
		
		unsigned int  X_2, X_2_seed, X_1, X_1_seed;
		
		unsigned int a_1 = pow (7, 5), b_1 = 0;
		
		unsigned int a_2 = pow (6, 6), b_2 = 0;
		
		unsigned int M = pow (2, 30) - 1; // M is "shared" among the random number generators
		
		ld pi = 3.141592653589;
		
		ld U_1, U_2;
		
		ld *Z_1 = new ld [M];
		
		ld *Z_2 = new ld [M];
		
		
		void norm_rand (void) {
			
			std:: cout << std:: fixed << std:: setprecision (10);
			
			std:: cout << "Enter the number of random numbers: " << '\n';
			
			std:: cin >> n;
			
			std:: cout << M << '\n';
			
			for (i = 0; i < M; i++) {
			
				X_1 = (a_1 * X_1_seed + b_1) - (unsigned int) ((a_1 * X_1_seed + b_1) / M) * M; 

				X_2 = (a_2 * X_2_seed + b_2) - (unsigned int) ((a_2 * X_2_seed + b_2) / M) * M;

// This is the computation of the remainder of the Euclidean division of a * seed + b and M, i.e., (a * seed + b) mod M.

				U_1 = (ld) X_1 / M;
				
				U_2 =  (ld) X_2 / M;
				
				*(Z_1 + i) = sqrt (- 2 * log (U_1)) * cos (2 * pi * U_2);
				
				*(Z_2 + i) = sqrt (- 2 * log (U_1)) * sin (2 * pi * U_2);
				
				X_1_seed = X_1;
				
				X_2_seed = X_2;
			} 
			
			std:: cout << "Random sequence finished" << '\n';
			
			print_arr (n);
			
			delete [] Z_1;
			
			delete [] Z_2;
		}
		
			
};


int main (void) {
	
	box_muller:: ld seed_1, seed_2;
	
	std:: cout << "Enter the first seed: " << '\n';
	
	std:: cin >> seed_1;
	
	std:: cout << "Enter the second seed: " << '\n';
	
	std:: cin >> seed_2;

	box_muller rand (seed_1, seed_2);
	
	return 0;
}






