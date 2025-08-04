# include <iostream>
# include <iomanip>

class Random {

	private:
	
		double *nums;
		
	public: 
		 
		 // Linear congruential generator
		 
		void lin_cong (uint M, uint a, uint b, uint x0) {
			
			std:: cout << std:: fixed << std:: setprecision (12);
			
			uint x;
			
			nums = new double [M];
			
			// It is custromary to take b = 0, so it is automatically done here. Also
			// M is usually taken to be prime
			
			b = 0;
			
			nums [0] = (double) x0 / M;
			
			for (int i = 1; i < M; i++) {
			
				x = (a*x0 + b) - (uint) ((a*x0 + b) / M) * M;
				
				*(nums + i) =  (double) x / M;
				
				x0 = x;
			} 
			
			std:: cout << "Random sequence finished." << std:: endl;
		}
		
		// Fibonacci sequence 
		
		void fib (uint k, uint l, uint M) {
		
			uint max;
			
			if (k > l) {
				
				max = k;
			}
			
			else {
				
				max = l;
			}
			
			for (int i = m; i < M; i ++) {
			
			
				x = 
			}
			
		}
		
		
		void print_arr (size_t n_elements) {
			
			std:: cout << "Random array elements: " << '\n';
			
			for (int i = 0; i < n_elements; i++) {
			
				std:: cout << * (nums + i) << '\n';
			}
		
		}
		
		void free_arr () {
		
			delete [] nums;
		}
	
};



int main (void) {

	uint M = 2147483647, a = 742938285, b = 1, x0;
	
	std:: cout << "Enter a seed" << std:: endl;
	
	std:: cin >> x0;
	
	Random rand_array;
	
	rand_array.lin_cong (M, a, b, x0);
	
	size_t n_elements = 35;
	
	rand_array.print_arr (n_elements);
	
	rand_array.free_arr ();

	return 0;
}





