# include "1part.hpp"
 	
Simulate :: ld * Simulate :: rand_arr (unsigned int M, unsigned int a) {
	
	// It is custromary to take b = 0, so it is automatically done here. Also
	// M is usually taken to be prime
	
	unsigned int x, x0, b = 0;
	
	std:: cout << "Enter a seed" << std:: endl;
	
	std:: cin >> x0;
	
	ld *arr = new ld [M];
	
	*(arr + 0)  = (ld) x0 / M;
	
	for (i = 1; i < M; i++) {
	
		x = (a * x0 + b) - (unsigned int) ((a * x0 + b) / M) * M; // mod function
		
		if (rand () % 2 == 0) {
			
			*(arr + i) =  (ld) x / M;
		}
		
		else {
			
			*(arr + i) =   - (ld) x / M;
		}
		
		x0 = x;
	} 
	
	std :: cout << "Random array sequence finished" << '\n';

	return arr;
}

void Simulate :: print_arr (ld *arr, size_t arr_size) {
	
	for (i = 0; i < arr_size; i ++) {
	
		std :: cout << *(arr + i) << '\n';
	}
}

Simulate :: Simulate (ld *s, ld *b, unsigned int C, unsigned int M, unsigned int a, size_t n) {
	
	// Random array
	
	//nums = rand_arr (M, a, x0);
	
	// Memory management
	
	x = new ld [n];
	
	lengths = s; 
	
	sizes = b;
	
	print_arr (lengths, n);
	
	print_arr (sizes, n);
	
	// File management
	
	std :: fstream file;
	
	file.open ("positions.txt", std :: ios :: out);
	
	// Main loop 
	
	std :: cout << "Simulation start. No. of cycles: " << C << '\n';
	
	for (i = 0; i < C; i ++) {
		
		for (j = 0; j < n; j ++) {
			
			// Moves the particle
			
			*(x + j) = *(x + j) + *(lengths+ j) * rand () / RAND_MAX; 
			
			// Checs PBC
			
			while (acc == false) {
			
				if (*(x + j) > *(sizes + j)) {
				
					*(x + j) = - *(sizes + j) + abs (*(x + j) - *(sizes + j));
				}
			
				else if (*(x + j) < - *(sizes + j)) {
				
					*(x + j) = *(sizes + j) - abs (*(x + j) - *(sizes+ j));
				}
				
				if (abs (*(x + j)) < *(sizes + j)) {
				
					acc = true;
				}
				
				else {
					
					acc = false;
				}
			}
			
			acc = false;
		}
		
		if (i % 20 == 0) {
			
			for (j = 0; j < n; j ++) {
				
				file << *(x + j) << ' ';
			}
			
			file << '\n';
		}
	}
	
	print_arr (lengths, n);
	
	print_arr (sizes, n);
	
	file.close ();
	
}




