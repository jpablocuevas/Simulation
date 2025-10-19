#include <stdio.h>
#include "2body_beeman.h"

// ------------------ Main function for the Beeman algorithm --------------

int main (void){
	
	ld dt  = 0.1;
	
	int T = 1000;
	
	size_t vec_size = 3;
	
	ld m_1 = 1, m_2; // Mass of the sun
	
	m_2 = m_1/1048; // Jupiter's mass in solar units
	
	beeman (m_1, m_2, dt, T, vec_size);

	return 0;
}
