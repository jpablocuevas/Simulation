// This code generates a 2d array of N particles with random positions and calculates the distance betwen them. 

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <time.h>


float rand_num (int inf, int sup) {
	
	return   (float) (rand () % (labs (sup-inf) + 1) + inf) + (float) rand () / RAND_MAX;
}

float dis (float *x_1, float *x_2, size_t x_size) {

	float d = 0;
	
	for (int i = 0; i < x_size; i ++) {
	
		d = d + pow (* (x_1 + i) - *(x_2 + i), 2);
	}
	
	printf ("%f \n", d);
	
	return sqrt (d);
}


void grid_2D (int N, float sigma, size_t x_size) {

	int i;
	
	float x[N][x_size];
	
	float rc;
	
	x[0][0] = rand_num (-5*N, 5*N);
	x[0][1] = rand_num (-4*N, 4*N);
		
	for (i = 1; i < N; i ++ ) {
	
		x[i][0] = rand_num (-5*N, 5*N);
		x[i][1] = rand_num (-4*N, 4*N);
		
		rc = dis (x[i], x[i-1], x_size) - 2*sigma;
		
		printf ("%f \n", rc);
	}

}


int main (void) {
	
	time_t seed;

	srand ((unsigned) time (NULL));

	int N = 2;
	size_t x_size = 2;
	
	float sigma = 0.194390;

	grid_2D (N, sigma, x_size);

	return 0;
}
