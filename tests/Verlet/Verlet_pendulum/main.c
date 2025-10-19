#include <stdio.h>
#include "ver_pend.h"


int main (void) {
	
	ld l = 5, g = 9.81, dt = 0.1, pi = 3.1415926535;
	
	int T = 40;
	
	ld theta_0 = pi /2, v_theta_0 = 0;
	
	stoermer_verlet (theta_0, v_theta_0, l, g, dt, T);
	
	return 0;
}
