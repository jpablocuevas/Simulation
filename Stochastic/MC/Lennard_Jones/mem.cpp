# include "mem.hpp"

// ---------------------------- Mem allocation methods ----------------------

// Constructor overloading to set tens, grid or arr

Mem :: Mem (void) {

}

Mem :: Mem (size_t n, size_t m, size_t l) {

	this -> n = n;

	this -> m = m;

	this -> l = l;
}

Mem :: Mem (size_t m, size_t l) {

	this -> m = m;

	this -> l = l;
}

Mem :: Mem (size_t l) {

	this -> l = l;
}

void Mem :: get_tens_size (void) {

	std :: cout << "\"Tensor\" size: = tens[" << n << "]["<< m << "][" << l << ']' << '\n';
}

void Mem :: get_grid_size (void) {

	std :: cout << "Grid size: grid[" << m << "]["<< l << ']' << '\n';
}

void Mem :: get_arr_size (void) {

	std :: cout << "Array size: arr[" << l << ']' << '\n';
}

	ld *** Mem :: alloc_tens (void) {

	tens = new ld **[n];

	if (tens == NULL) {
		
		std :: cout << "Mem allocation failed!" << '\n';
		
		exit (0);
	}

	for (i = 0; i < n; i ++) {

		*(tens + i) = new ld *[m];

		if (*(tens + i) == NULL) {
		
			std :: cout << "Mem allocation failed!" << '\n';
			
			exit (0);
		}

		for (j = 0; j < m; j ++) {

			*(*(tens + i) + j) = new ld [l];

			if (*(*(tens + i) + j)== NULL) {
		
				std :: cout << "Mem allocation failed!" << '\n';
			
				exit (0);
			}
		}
	}

	return tens;
}

	ld **Mem :: alloc_grid (void) {

	grid = new ld *[m];
	
	if (grid == NULL) {
		
		std :: cout << "Mem allocation failed!" << '\n';
		
		exit (0);
	}

	for (i = 0; i < m; i ++) { 
		
		*(grid + i) = new ld [l];
		
		if (*(grid + i) == NULL) {
		
			std :: cout << "Mem allocation failed!" << '\n';
			
			exit (0);
		}
	}
	
	return grid;
}

	ld *Mem :: alloc_arr (void) {

	arr = new ld [l];

	if (arr == nullptr) {
		
		std :: cout << "Mem allocation failed!" << '\n';
			
		exit (0);
	}
	
	return arr;
}

void Mem :: dealloc_tens (ld ***X) {

	for (i = 0; i < n; i ++) {

		for (j = 0; j < m; j ++) {

			delete [] *(*(X + i) + j);
		}
		
		delete [] *(X + i);
	}

	delete [] X;
}
void Mem :: dealloc_grid (ld **X) {
	
	for (i = 0; i < m; i++) {
	
		delete [] *(X + i);
	}
	
	delete [] X;
}

void Mem :: dealloc_arr (ld *X) {
	
	delete [] X;
}

void Mem :: set_tens_rand (ld ***X) {

	ld num;

	for (i = 0; i < n; i ++) {

		for (j = 0; j < m; j ++) {

			for (k = 0; k < l; k ++) {
				
				if (rand () % 2 == 0) {
			
				num = - 1;
			}

			else {

				num = 1;
			}
		
			*(*(*(X + i) + j) + k) = num * (ld) rand () / RAND_MAX;
		
			}
		}
	}
}

void Mem :: set_grid_rand (ld **X) {
	
	signed int num;
	
	for (i = 0; i < m; i ++) {
		
		for (j = 0; j < l; j ++) { 
			
			if (rand () % 2 == 0) {
			
				num = - 1;
			}

			else {

				num = 1;
			}
		
			*(*(X + i) + j) = num * (ld) rand () / RAND_MAX;
		}
	}
}

void Mem :: set_arr_rand (ld *X) {
	
	signed int num;
	
	for (i = 0; i < l; i ++) {
		
		if (rand () % 2 == 0) {
			
			num = - 1;
		}

		else {

			num = 1;
		}
		
		*(X + i) = num * (ld) rand () / RAND_MAX;
	}
}

void Mem :: print_tens (ld ***X) {

	for (i = 0; i < n; i ++) {

		for (j = 0; j < m; j ++) {

			for (k = 0; k < l; k ++) {
				
				std :: cout << *(*(*(X + i) + j) + k) << ' ';
			}

			std :: cout << '\n';
		}

		std :: cout << '\n';
	}		
}

void Mem :: print_grid (ld **X) {
	
	for (i = 0; i < m; i ++) {
		
		for (j = 0; j < l; j ++) {

			std :: cout << *(*(X + i) + j) << ' ';
		}
		
		std :: cout << '\n';
	}
}


void Mem :: print_arr (ld *X) {
	
	for (i = 0; i < l; i ++) {
		
			std :: cout << *(X + i) << '\n';
	}
}

// Printing grid components to a text file

void Mem :: create_file (ld **X, unsigned int name) {
	
	file.open ("positions" + std:: to_string (name) + ".txt", std :: ios :: out);
	
	for (i = 0; i < m; i ++) {
	
		for (j = 0; j < l; j ++) {
	
			file << *(*(X + i) + j) << ' ';
		}
		
		file << '\n';
	}
	
	file.close ();
}

