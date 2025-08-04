#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


int main (void){

	int i, a, b;

	// Seed

	time_t seed;

	srand ((unsigned) time (&seed));
	
	// Random number range
	
	a = -50;
	b = 10;
	
	// (x,y,z) random coordinates on a file
	
	FILE* file;

	file = fopen("randompts.txt", "w");

	fputs("x \t y \t z \t \n", file);
	
	int p1, p2, p3;
	
	for ( i = 0; i < 500; i++){
	
		p1 = pow (-1,rand ()% abs (b-a)); // Parity variable to generate both positive and negative numbers
		p2 = pow (-1,rand ()% abs (b-a));
		p3 = pow (-1,rand ()% abs (b-a));
	
		fprintf(file, "%f \t %f \t %f \t \n", (double) (p1*rand ()% abs (b-a)), (double) (p2*rand ()% abs (b-a)), (double) (p3*rand ()% abs (b-a)) );
		
	} 
	
	fclose (file);


	return 0;
}
