#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef long double ld;

ld pi = 3.1415926535;

// ------------------------- Units ------------------------

// Distance: AU (Astronomical Units)
// Time: days
// Acceleration: AU^2/Days
// Mass: SM (Solar Masses)

// Gravitational constant

// G=39.485279383758936; # G=4*pi^2 Y^-2*AU*MS^-1


// ------------------------- Functions ------------------------

// Function that prints a vector

void print_vec (ld*);

void print_vec (ld *x){

	printf (" (x, y, z) = (% .10Lf, % .10Lf, % .10Lf) \n", x[0], x[1], x[2]);

}

// Distance function between two points

ld dis (ld *, ld *, size_t);

ld dis (ld *x, ld *y, size_t n){

	int i;
	
	ld d = 0.;
	
	for (i = 0; i < n; i++){
	
		d = d + pow (x[i]- y[i], 2);
	}

	return sqrt (d);	
}


// Returns the acceleration from the gravitational potential

ld *acc (int, ld, ld, ld *, ld *, size_t );

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
			
			dx =  - (x1[i]-x2[i]);
			m = m_2;
		}
	
		a[i] = - G*m / pow (d, 3) *dx;
	}
	
	return a;
}


// Function that evolves the position vector a step of size dt given its velocity

ld *x_step (ld*, ld*, ld , size_t);

ld *x_step (ld *x, ld *v, ld dt, size_t n ){

	int i;
	
	ld *x_p;
	
	x_p = (ld *) calloc (n, sizeof (ld));
	
	for (i = 0; i < n; i++){
	
		x_p[i] = x[i]+ dt*v[i];
	}
	
	return x_p;
}

// Function that updates the coordinates from new to old

void update (ld *, ld *, ld *, size_t);

void update (ld *old, ld *next, ld *new, size_t n){

	int j;
		
	for (j = 0; j < n; j++){
	
		old [j] = next[j];
		next[j] = new[j];
	}
}


// Verlet integration function

void stoermer_verlet (ld, int, ld, ld, size_t);

void stoermer_verlet (ld dt, int T, ld m_1, ld m_2, size_t n){

	// Declaration of arrays
	
	ld *x1_new, *x1_old, *x1_next; // The memory allocation for x_next is done in the x_step function
	ld *x2_new, *x2_old, *x2_next; 
	
	ld *vel1, *a1;
	ld *vel2, *a2;
	
	// Memory allocation
	
	x1_old = (ld *) calloc (n, sizeof(ld));
	x1_new = (ld *) calloc (n, sizeof(ld));
	
	x2_old = (ld *) calloc (n, sizeof(ld));
	x2_new = (ld *) calloc (n, sizeof(ld));
	
	vel1 = (ld *) calloc (n, sizeof(ld));
	vel2 = (ld *) calloc (n, sizeof(ld));
	
	// Initial conditions. This part of the code can be improved by reading the conditions from a file 
	
	ld x1_0, y1_0, z1_0;
	ld v1x_0, v1y_0, v1z_0;
	
	ld x2_0, y2_0, z2_0;
	ld v2x_0, v2y_0, v2z_0;
	
	x1_0 = -5.385202;
	y1_0 = - 0.840171;
	z1_0 = - 0.229015;

	v1x_0 = 0.001099944*365;	// Converting the velocities to AU / Year
	v1y_0 = - 0.006518169*365;
	v1z_0 = - 0.002820667*365;
	
	x2_0 = 0.;
	y2_0 = 0.;
	z2_0 = 0.;

	v2x_0 = 0.;
	v2y_0 = 0.;
	v2z_0 = 0.;
		
	x1_old[0] = x1_0;
	x1_old[1] = y1_0;
	x1_old[2] = z1_0;
	
	vel1[0] = v1x_0;
	vel1[1] = v1y_0;
	vel1[2] = v1z_0;
	
	x2_old[0] = x2_0;
	x2_old[1] = y2_0;
	x2_old[2] = z2_0;
	
	vel2[0] = v2x_0;
	vel2[1] = v2y_0;
	vel2[2] = v2z_0;

	// Verlet loop of T steps
	
	int j;
	float t = 0.;
	
	x1_next = (ld *) x_step (x1_old, vel1, dt, n);
	x2_next = (ld *) x_step (x2_old, vel2, dt, n);
	
	a1 = (ld *) acc (1, m_1, m_2, x1_next, x2_next, n); // The acceleration is evaluated at the evolved position x_next
	a2 = (ld *) acc (2, m_2, m_2, x1_next, x2_next, n);
	
	// Files to write the position of the objects
	
	FILE *pos1, *pos2;
	
	pos1 = fopen("x1_pos.txt", "w");
	pos2 = fopen("x2_pos.txt", "w");
	
	fputs ("x \t y \t z \t \n", pos1);
	fputs ("x \t y \t z \t \n", pos2);
	
	fprintf (pos1, "%Lf \t %Lf \t %Lf \t \n", x1_old[0], x1_old[1], x1_old[2]);
	fprintf (pos1, "%Lf \t %Lf \t %Lf \t \n", x1_next[0], x1_next[1], x1_next[2]);
	
	fprintf (pos2, "%Lf \t %Lf \t %Lf \t \n", x2_old[0], x2_old[1], x2_old[2]);
	fprintf (pos2, "%Lf \t %Lf \t %Lf \t \n", x2_next[0], x2_next[1], x2_next[2]);
	
	
	while (t < (float)T) {	
	
		for (j = 0; j < n; j++){
		
			x1_new[j] = 2*x1_next[j] - x1_old[j] + pow (dt,2)*a1[j];
			x2_new[j] = 2*x2_next[j] - x2_old[j] + pow (dt,2)*a2[j];
		}
		
		// Updating the position arrays
		
		update (x1_old, x1_next, x1_new, n);
		update (x2_old, x2_next, x2_new, n);
		
		a1 = (ld *) acc (1, m_1, m_2, x1_new, x2_new, n);
		a2 = (ld *) acc (2, m_1, m_2, x1_new, x2_new, n);
		
		// File writing

			if ( (int) t % 20 ==0){
			
			fprintf (pos1, "%Lf \t %Lf \t %Lf \t \n", x1_new[0], x1_new[1], x1_new[2]);
			
			fprintf (pos2, "%Lf \t %Lf \t %Lf \t \n", x2_new[0], x2_new[1], x2_new[2]);

			}
		
		t = t + dt;
	}
	
	free (x1_old);
	free (x1_new);
	free (x1_next);
	
	free (x2_old);
	free (x2_new);
	free (x2_next);
	
	free (vel1);
	free (vel2);
	
	free (a1);
	free (a2);

	fclose (pos1); 
	fclose (pos2); 
}

int main (void){
	
	ld dt  = 0.1;
	
	int T = 5000;
	
	size_t vec_size = 3;
	
	ld m_1 = 1, m_2; // Mass of the sun
	
	m_2 = m_1/1048; // Jupiter's mass in solar units
	
	stoermer_verlet (dt, T, m_1, m_2, vec_size);

	return 0;
}
