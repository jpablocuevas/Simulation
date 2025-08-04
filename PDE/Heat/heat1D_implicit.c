# include <stdio.h>
# include <stdlib.h>
# include <math.h>

// Metallic rod of total length of 10cm. Time measured in seconds, distance in cm and temperature in Celsius.

int main (void) {
		
	int i, j;
	
	// Simulation parameters
	
	double t0 = 0, tf = 1, xf = 10, x0 = 0, dt = 0.1, dx = 2;
	
	double C = 0.2174, rho = 2.7, k_p, k, lambda; // Physical parameters
	
	k_p = 0.49; // cals / s*cm*C
	
	k = k_p / (C*rho);
	
	lambda = k * dt / (dx*dx); // This method is both convergent and stable if lambda \leq 1/2 or dt \leq 1/2 dx^2 / k
	
	printf ("lambda = %.8lf \n", lambda);
	// Memory allocation. The first index is used for the temporal storage, and the second for spatial storage
	
	size_t x_size, t_size;
	
	x_size = (size_t) fabs (xf-x0) / dx;
	
	t_size = (size_t) fabs (tf-t0) / dt;
	
	printf ("Time array size: %zu. Spatial array size: %zu \n", t_size, x_size);
	
	double **T;
	
	T = malloc (t_size * sizeof (double *));
	
	if (T == NULL) {
	
		printf ("Error. Memory could not be allocated! \n");
		
		exit (1);
	}
	
	for (i = 0; i < t_size; i++) {
	
		* (T + i) = malloc (x_size * sizeof (double));
		
		if (*(T +i) == NULL) {
	
		printf ("Error. Memory could not be allocated! \n");
		
		exit (1);
		}
	}
	
	// Boundary conditions
	
	for (i = 0; i < t_size; i++) {
		
		for (j = 0; j < x_size; j++) {
	
			* (* (T + i) + 0) = 100; // First boundary contidion 
			
			* (* (T + i) + x_size - 1) = 50; // Second boundary contidion 
		}
	}
	
	// Main loop. PDE solution
	
	for (i = 0; i < t_size -1; i++) {
		
		for (j = 1; j < x_size - 1; j++) {
	
			T [i+1][j] = T[i][j] + lambda * (T[i][j+1] - 2*T[i][j] + T[i][j-1]);
		}
	}
	
	// Printing the solution
	
	for (i = 0; i < t_size; i++) {
		
		for (j = 0; j < x_size; j++) {
	
			//printf ("T[%d][%d] = %.8lf ", i, j, *(*(T + i) + j));
			printf ("%.8lf ", *(*(T + i) + j));
		}
		
		printf ("\n");
	}
	
	// Freeing the dynamically allocated double pointer
	
	for (i = 0; i < t_size; i++) {
		
		free (*(T + i));
	}
	
	free (T);

	return 0;
}




