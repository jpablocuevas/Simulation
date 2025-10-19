#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef long double ld;


// Function that returns the acceleration based on the force

ld *acc (ld, ld, ld m, ld *, size_t);

ld *acc (ld m, ld b, ld *g, ld *v, size_t, n){ // *g is the acceleration array due to Earth's gravity 

	ld *a;
	
	a = malloc (sizeof (ld)*n);
	
	int i;
	
	for (i = 0; i < n; i++){
	
		a[i] = g[i] - b / m * v[i];
	}
	
	return a;
}


// Function that updates the coordinates of an array

void update (ld *, ld*, size_t);

void update (ld *old, ld *new, size_t n){

	int i;
	
	for (i = 0; i < n; i++){
	
		old [i] = new[i];
	}
}

// Verlet integration function

void vel_verlet (ld, ld, ld, int, size_t, ld);

void vel_verlet (ld m, ld g_val, ld b, int T, size_t n, ld dt){

	// Creating position, velocity and acceleration arrays
	
	ld *x_new, *x_old;
	ld *v_new, *v_old;
	ld *a_new, *a_old;
	
	x_new = (ld*) calloc (n, sizeof (ld));
	x_old = (ld*) calloc (n, sizeof (ld));
	
	v_new = (ld*) calloc (n, sizeof (ld));
	v_old = (ld*) calloc (n, sizeof (ld));
	
	a_new = (ld*) calloc (n, sizeof (ld));
	a_old = (ld*) calloc (n, sizeof (ld));
	
	// Initial conditions

	ld x_0 = 0., y_0 = 0., z_0 = 0.; // Measured in m
	ld vx_0 = 0., vy_0 = 3.54, vz_0 = 10. ; // Measured in m / s
	
	x_old[0] = x_0;
	x_old[1] = y_0;
	x_old[2] = z_0;
	
	v_old[0] = vx_0;
	v_old[1] = vy_0;
	v_old[2] = vz_0;

	ld *g;
	
	g = (ld*) malloc (sizeof (ld)*n);
	
	ld b = 1.6 * pow(10, -2) // Measured in N*s/m2
	
	g[0] = 0;
	g[1] = 0;
	g[2] = -g_val; // Constant gravitarional acceleration in the - z direction
		
	int i, j;
	
	a_old =  (ld *) acc(m, b, g, v_old);
	
	for (i = 0; i < T; i++){
	
		
		for (j = 0; j < n; j++){  // Updating the position array
		
			x_new[j] = x_old[j] + dt*v_old[j] + pow(dt, 2) / 2 * a_old[j];
		}
		
		a_new = (ld *) acc(m, b, g, v_); // Computing the new acceleration usint x_new
		
		for (j = 0; j < n; j++){  // Updating the velocity array
			
			v_new [j] = v_old [j] + (a_old[j] + a_new[j]) * dt/2;
		}
		
		update (x_old, x_new);
		update (v_old, v_new);
		update (a_old, a_new);
	
	}
	
	free (x_old);
	free (x_new);
	
	free (v_old);
	free (v_new);
	
	free (a_old);
	free (a_new);
	
	free (g);

}



int main (void){


	int T;
	ld T, dt = 0.1, g_val = 9.81;

	return 0;
}











int main (void){






	return 0;
}
