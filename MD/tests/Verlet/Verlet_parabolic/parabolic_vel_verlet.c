#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef long double ld;


// Function that returns the acceleration based on the force

ld *acc (ld *, size_t);

ld *acc (ld *g, size_t n){ // *g is the acceleration array due to Earth's gravity 

	ld *a;
	
	a = malloc (sizeof (ld)*n);
	
	int i;
	
	for (i = 0; i < n; i++){
	
		a[i] = g[i];
	}
	
	return a;
}


// Function that updates the coordinates of an array

void update (ld *, ld*, size_t);

void update (ld *old, ld *new, size_t n){

	int i;
	
	for (i = 0; i < n; i++){
	
		old [i] = (ld) new[i];
	}
}

// Verlet integration function

void vel_verlet (ld, ld *, ld *, ld, int, size_t);

void vel_verlet (ld g_val, ld *x_0, ld *v_0, ld dt, int T, size_t n){

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
	
	// Initial conditions. Position is measured in m and velocity in m / s
	
	x_old[0] = x_0[0];
	x_old[1] = x_0[1];
	x_old[2] = x_0[2];
	
	v_old[0] = v_0[0];
	v_old[1] = v_0[1];
	v_old[2] = v_0[2];

	ld *g;
	
	g = (ld*) malloc (sizeof (ld)*n);
	
	g[0] = 0;
	g[1] = 0;
	g[2] = -g_val; // Constant gravitarional acceleration in the - z direction

	a_old =  (ld *) acc (g, n);
	
	// File management 
	
	FILE *pos;
	
	pos = fopen("x_pos.txt", "w");
	
	fputs ("x \t y \t z \t \n", pos);
	
	fprintf (pos, "%Lf \t %Lf \t %Lf \t \n", x_old[0], x_old[1], x_old[2]);
	
	// Main loop 
	
	int j;
	float t = 0.;
	
	while (t <  (float)T) {
	
		for (j = 0; j < n; j++){  // Updating the position array
		
			x_new[j] = x_old[j] + dt*v_old[j] + pow(dt, 2) / 2 * a_old[j];
		}
		
		a_new = (ld *) acc(g, n); // Computing the new acceleration usint x_new. In this case, it is constant so it does not matter. 
						 // Still, for consistenty, it is kept.
		
		for (j = 0; j < n; j++){  // Updating the velocity array
			
			v_new [j] = v_old [j] + (a_old[j] + a_new[j]) * dt/2;
		}

			
		fprintf (pos, "%Lf \t %Lf \t %Lf \t \n", x_new[0], x_new[1], x_new[2]);
		
		update (x_old, x_new, n);
		update (v_old, v_new, n);
		update (a_old, a_new, n); // Same here. The acceleration is constant so this could be omitted 
		
		t = t + dt;
	}
	
	fclose (pos);
	
	free (x_old);
	free (x_new);
	
	free (v_old);
	free (v_new);
	
	free (a_old);
	free (a_new);
	
	free (g);
}

int main (void){

	int T = 250;
	
	size_t vec_size = 3;
	
	ld g_val = 9.81;
	float dt = 0.1;
	
	ld x_0[3], v_0[3];
	
	x_0[0] = 0.;
	x_0[1] = 0.;
	x_0[2] = 0.;
	
	v_0[0] = 14.8;
	v_0[1] = 0.;
	v_0[2] = 1300.45;
	
	vel_verlet (g_val, x_0, v_0, dt, T, vec_size);

	return 0;
}

