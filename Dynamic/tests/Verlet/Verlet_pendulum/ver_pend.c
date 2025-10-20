#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ver_pend.h"




ld acc (ld theta, ld l, ld g) {

	return  -(ld) g / l * sin (theta);
}

ld theta_step (ld theta, ld v_theta, ld dt) {

	return theta + dt * v_theta;
}



void stoermer_verlet (ld theta_0, ld v_theta_0, ld l, ld g, ld dt, int T) {

	ld theta_old, theta_next, theta_new;
	
	ld v_theta;
	
	// Initial conditions
	
	ld pi = 3.1415926535;
	
	theta_old = theta_0; // Radians
	v_theta = v_theta_0; // Radians / s
	
	// File management
	
	FILE *pos;
	
	pos = fopen ("position.txt", "w");
	
	fputs ("x \t y \t  \n", pos);
	
	// Algorithm
	
	float t = 0.;
	
	theta_next = (ld) theta_step (theta_old, v_theta, dt);
	
	fprintf (pos, "%Lf \t %Lf \t \n", l*cos (theta_old), l*sin(theta_old));
	fprintf (pos, "%Lf \t %Lf \t \n", l*cos (theta_next), l*sin(theta_next));
	
	while (t < (float) T) {
	
	
		theta_new = 2*theta_next - theta_old + pow (dt , 2) * acc (theta_next, l, g);
		
		theta_old = theta_next;
		theta_next = theta_new;
			
		fprintf (pos, "%Lf \t %Lf \t \n", l*cos (theta_new), l*sin(theta_new));

	
		t = t + dt;
	}
	
	
	fclose (pos);
}

void vel_verlet (ld theta_0, ld v_theta_0, ld l, ld g, ld dt, int T) {
	

}








