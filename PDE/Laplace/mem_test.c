#include <stdio.h>
#include "memory.h"


int main (void){

	int i, j;
	
	double **f;
	
	f = alloc_2d (3,3);
	
	for (i = 0; i < 3; i++){
		for (j = 0; j < 3; j++){
		
		printf("f[%d][%d] = %lf \n", i,j, f[i][j]);
		
	
		}
		
	}
	
	dealloc_2d (f,3);


	return 0;
}
