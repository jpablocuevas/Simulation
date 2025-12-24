# include "mem.h"


ld **alloc_matrix (size_t N) {

	ld **X;
	
	X = calloc (N, sizeof (ld *));
	
	for (i = 0; i < N; i ++) {
		
		*(X + i) = calloc (3, sizeof (ld));
	}
	
	return X;
}

ld *alloc_array (size_t N) {

	ld *x;
	
	x = calloc (N, sizeof (ld));
	
	return x;
}

void dealloc_matrix (ld **X, size_t N) {

	for (i = 0; i < N; i ++) {
		
		free (*(X + i));
	}
	
	free (X);
}

void dealloc_array (ld *x) {

	free (x);
}

void init_matrix_rand (ld **X, size_t N) {

	for (i = 0; i < N; i ++) {
		
		for (j = 0; j < 3; j ++) {
			
			*(*(X + i) + j) = (ld) rand () / RAND_MAX;
		}
	}
}

void init_array_rand (ld *x, size_t N) {

	for (i = 0; i < N; i ++) {
		
		*(x + i) = rand () / RAND_MAX;
	}
}

void print_matrix (ld **X, size_t N) {

	for (i = 0; i < N; i ++) {
		
		for (j = 0; j < 3; j ++) {
			
			printf ("%.10Lf ", *(*(X + i) + j));
		}
		
		printf ("\n");
	}
}





