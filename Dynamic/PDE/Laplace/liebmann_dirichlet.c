#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "funcs.h"


int main (void){
	
	// Grid construction
	
	int i, j, n = 5, m = 5;
	
	double** T, **T_new, **T_old;
	
	T = (double**) alloc_2d (n, m);
	
	T_new = (double**) alloc_2d (n, m);
	
	T_old = (double**) alloc_2d (n, m);
	
	// Initial conditions
	
	for (i = 0; i < n; i++){
	
		T[i][0] = 0.;
		T[i][n-1]  = 100.;
	}
	
	for (i = 1; i < m-1; i++){
	
		T[0][i] = 75.;
		T[m-1][i]  = 50.;
	}
	
	/*for (i = 0; i < n; i++){
	
		for (j = 0; j < m; j++){
		
			printf("T[%i][%i] = %lf \t", i, j, T[i][j]);
		
		}
		
		printf("\n");
	}*/
	
	// Temperature and position file
	
	FILE *temp;
	
	char *name;
	
	
	
	// Finite differences
	
	double e = 100., lambda = 1.5;
	
	
	while (e >= 1.){

		for (j = 1; j < m-1; j++){
	
			for (i = 1; i < n-1; i++){
				
					T_new[i][j] = (T[i+1][j] +T[i-1][j] +T[i][j+1] +T[i][j-1] )/4.;
				
					// Relaxation
				
					T[i][j] = lambda*T_new[i][j]+ (1.-lambda)*T_old[i][j];
					
					printf("T[%i][%i] = %lf \n", i, j, T[i][j]);
					
					
					/*space_plot = fopen (name, "w");

				    	fputs ("Ez \t x \n", space_plot);

				    	for (i = 0; i < Ez_size; i++){

						fprintf(space_plot, "%lf \t %lf \n",Ez[i], pos[i]);
						

						}*/
				}	
			}
			
			e = rel_err(T_new[1][1], T_old[1][1]);
			
			printf(" e = %lf \n",e);
			
			printf("\n");
			
			for (j = 1; j < m-1; j++){
	
				for (i = 1; i < n-1; i++){
				
					T_old[i][j] = T_new[i][j];
				}
			}
			
		}

	dealloc_2d (T, m);
	
	dealloc_2d (T_new, m);
	
	dealloc_2d (T_old, m);

	return 0;
}
