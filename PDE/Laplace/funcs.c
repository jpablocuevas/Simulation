#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "funcs.h"

// Memory allocation functions

double **alloc_2d (int n, int m){

	double **f;

	f  = (double**) calloc (n, sizeof (double*));
	
	int i;
	
	for (i = 0; i < n; i++){
	
		f[i] = (double*) calloc (m, sizeof (double));
	}
	
	return f;

}

void dealloc_2d (double **f, int n){
	
	int i;
	
	for (i = 0; i < n; i++){
	
		free (f[i]);	
	}
	
	free (f);

}

// Relative error 

double abs_val (double x){
	
	if (x < 0){
		return -x;
	}
	
	return x;
}

double rel_err (double new, double old){
	
	return fabs((new-old)/new)*100.;

}

// File naming functions

char str (int n){

	char c;

	switch (n){

	case 0:
	    c = '0';
	    break;

	case 1:
	    c = '1';
	    break;

	case 2:
	    c = '2';
	    break;

	case 3:
	    c = '3';
	    break;

	case 4:
	    c = '4';
	    break;

	case 5:
	    c = '5';
	    break;

	case 6:
	    c = '6';
	    break;

	case 7:
	    c = '7';
	    break;

	case 8:
	    c = '8';
	    break;

	case 9:
	    c = '9';
	    break;

	}
    
    return c;

}

int count_digits (int n){

	int i = 1;
	
	while (n / (int) pow(10,i) > 1){
	
		i++;
	}
	
	return i;
}



char *int_to_char (int n){

	int i, j, count, res, x = 0;
	
	count = count_digits (n); 

	char *num;
	
	num = (char*) malloc (sizeof(char)*(count+1));
	
	j = count-1;
	
	
	for (i = 1; i < count +1; i++){ 
	
		num[j] = str((n % (int) pow (10,i)-x)/ (int) pow (10, i-1)) ;
		
		x = n%(int) pow(10,i);
		
		j--;
		
	}
	
	num[count] = '\0';
	
	return num;
}


char *file_name (int num){

	char *name;
	char str1[10];

	
	return name;

}








