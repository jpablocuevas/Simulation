#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "2body_beeman.h"


// ------------------------- Units ------------------------

// Distance: AU (Astronomical Units)
// Time: days
// Acceleration: AU^2/Days
// Mass: SM (Solar Masses)

// Gravitational constant

// G=39.485279383758936; # G=4*pi^2 Y^-2*AU*MS^-1


// ------------------------- Functions ------------------------

void print_vec (ld *x, size_t n) {
	
	if (n != 3){
		
		printf ("Cannot print vector. \n");
	}
	
	else {
	
		printf (" (x, y, z) = (% .10Lf, % .10Lf, % .10Lf) \n", x[0], x[1], x[2]);
	}

}
	
ld dis (ld *x, ld *y, size_t n) {

	int i;
	
	ld d = 0.;
	
	for (i = 0; i < n; i++){
	
		d = d + pow (x[i]- y[i], 2);
	}

	return sqrt (d);	
}

ld *acc (int particle, ld m_1, ld m_2, ld *x1, ld *x2, size_t n) {
	
	ld pi = 3.1415926535;
	
	ld G = 4* pow (pi, 2);
	
	ld *a;

	a = (ld *) malloc (sizeof (ld)*n);
	
	int i;
	
	ld d, dx, m;
	
	d = (ld) dis (x1, x2, n);
	
	for (i = 0; i < n; i++){
		
		if (particle == 1){
		
			dx = x1[i]-x2[i];
			m = m_1;
		}
		
		else if (particle == 2){
			
			dx =  x2[i]-x1[i];
			m = m_2;
		}
	
		a[i] = - G*m / pow (d, 3) *dx;
	}
	
	return a;
	
}


ld *x_step (ld *x, ld *v, ld dt, size_t n) {

	int i;

	ld *x_p;

	x_p = (ld *) calloc (n, sizeof (ld));

	for (i = 0; i < n; i++){

		x_p[i] = x[i]+ dt*v[i];
	}

	return x_p;
}

ld *v_step (ld *x_old, ld *x_next, ld *a_old, ld *a_next, ld dt, size_t n) {

	int i;

	ld *v_p;

	v_p = (ld *) calloc (n, sizeof (ld));

	for (i = 0; i < n; i++){

		v_p[i] = (x_next[i] - x_old[i]) / dt + (2*a_next[i] + a_old[i] ) / 6 *dt;
	}

	return v_p;
}

void update (ld *old, ld *new, size_t n) {

	int i;
	
	for (i = 0; i < n; i++){
	
		old [i] = (ld) new[i];
	}
}

void beeman (ld m_1, ld m_2, ld dt, int T, size_t n) {

	// Array setup

	ld *x1_old, *x1_next, *x1_new;
	ld *v1_old, *v1_next, *v1_new;
	ld *a1_old, *a1_next, *a1_new;
	
	ld *x2_old, *x2_next, *x2_new;
	ld *v2_old, *v2_next, *v2_new;
	ld *a2_old, *a2_next, *a2_new;
	
	// Memory allocation. The allocation for some of the arrays is done in other functions.
	
	x1_old = (ld *) calloc (n, sizeof (ld));
	x1_new = (ld *) calloc (n, sizeof (ld));

	v1_old = (ld *) calloc (n, sizeof (ld));
	v1_new = (ld *) calloc (n, sizeof (ld));
	
	 x2_old = (ld*) calloc (n, sizeof(ld));
	 x2_new = (ld*) calloc (n, sizeof(ld));

	v2_old = (ld*) calloc (n, sizeof(ld));
	v2_new = (ld*) calloc (n, sizeof(ld));

	// Initial conditions
	
	x1_old[0] = -5.385202;
	x1_old[1] = - 0.840171;
	x1_old[2] = - 0.229015;

	v1_old[0] = 0.001099944*365;	// Converting the velocities to AU / Year
	v1_old[1] = - 0.006518169*365;
	v1_old[2] = - 0.002820667*365;
	
	
	x2_old[0] = 0.;
	x2_old[1] = 0.;
	x2_old[2] = 0.;
	
	v2_old[0] = 0.;
	v2_old[1] = 0.;
	v2_old[2] = 0.;
	
	// Initial accelerations 
	
	ld *test;
	
	test = (ld *) calloc (n, sizeof (ld));
	
	a1_old = (ld*) acc (1, m_1, m_2, x1_old, x2_old, n);
	a2_old = (ld*) acc (2, m_1, m_2, x1_old, x2_old, n);
	
	// File handiling 
	
	FILE *coord1, *coord2;
	
	coord1 = fopen ("coordinates1.txt","w");
	coord2 = fopen ("coordinates2.txt", "w");
	
	fputs ("x \t y \t z \t \n", coord1);
	fputs ("x \t y \t z \t \n", coord2);
	
	// Beeman's alogrithm

	int i;
	float t = 0.;
	
	// Calculating the next step for position, velocity and acceleration
	
	x1_next = (ld*) x_step (x1_old, v1_old, dt, n);
	x2_next = (ld*) x_step (x2_old, v2_old, dt, n);
	
	a1_next = (ld *) acc (1, m_1, m_2, x1_next, x2_next, n);
	a2_next = (ld *) acc (2, m_1, m_2, x1_next, x2_next, n);
	
	v1_next = (ld*) v_step (x1_old, x1_next, a1_old, a1_next, dt, n);
	v2_next = (ld*) v_step (x2_old, x2_next, a2_old, a2_next, dt, n);
	
	
	fprintf (coord1, "%Lf \t %Lf \t %Lf \t \n", x1_old[0], x1_old[1], x1_old[2]);
	fprintf (coord1, "%Lf \t %Lf \t %Lf \t \n", x1_next[0], x1_next[1], x1_next[2]);
	
	fprintf (coord2, "%Lf \t %Lf \t %Lf \t \n", x2_old[0], x2_old[1], x2_old[2]);
	fprintf (coord2, "%Lf \t %Lf \t %Lf \t \n", x2_next[0], x2_next[1], x2_next[2]);
	
	
	while (t < (float)T){
		
	
		for (i = 0; i < n; i++){
		
			x1_new[i] = x1_next[i] + dt*v1_next[i] + pow (dt,2) / 6 *(4*a1_next[i] - a1_old[i]);
			x2_new[i] = x2_next[i] + dt*v2_next[i] + pow (dt,2) / 6 *(4*a2_next[i] - a2_old[i]);
		}
		
		// Calculating the new accelerations
		
		a1_new = (ld*) acc (1, m_1, m_2, x1_new, x2_new, n);
		a2_new = (ld*) acc (2, m_1, m_2, x1_new, x2_new, n);
		
		// Velocity computation
		
		for (i = 0; i < n; i++){
		
			v1_new[i] = v1_next[i]+ dt / 6 * (2*a1_new[i]+5*a1_next[i]-a1_old[i]);
			v2_new[i] = v2_next[i] + dt / 6 * (2*a2_new[i]+5*a2_next[i]-a2_old[i]);
		}
		
		// Updating all arrays 
		
		update (x1_old, x1_next, n);
		update (x1_next, x1_new, n);
		
		update (v1_old, v1_next, n);
		update (v1_next, v1_new, n);
		
		update (a1_old, a1_next, n);
		update (a1_next, a1_new, n);
		
		update (x2_old, x2_next, n);
		update (x2_next, x2_new, n);
		
		update (v2_old, v2_next, n);
		update (v2_next, v2_new, n);
		
		update (a2_old, a2_next, n);
		update (a2_next, a2_new, n);
		
		if ( (int) t % 20 == 0){
			
			fprintf (coord1, "%Lf \t %Lf \t %Lf \t \n", x1_new[0], x1_new[1], x1_new[2]);
			
			fprintf (coord2, "%Lf \t %Lf \t %Lf \t \n", x2_new[0], x2_new[1], x2_new[2]);

			}
		
		t = t + dt;
	}

	// Freeing the allocated memory 
	
	free (x1_old);
	free (x1_next);
	free (x1_new);
	
	free (v1_old);
	free (v1_next);
	free (v1_new);
	
	free (a1_old);
	free (a1_next);
	free (a1_new);
	
	
	free (x2_old);
	free (x2_next);
	free (x2_new);
	
	free (v2_old);
	free (v2_next);
	free (v2_new);
	
	free (a2_old);
	free (a2_next);
	free (a2_new);
	
	// Closing files 
	
	fclose (coord1);
	fclose (coord2);
}


