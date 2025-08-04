#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int count_digits (int);

char str (int);

char *file_name (int);

char *int_to_str (int);



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



char *int_to_str (int n){

	int i, j, count, x = 0;
	
	count = count_digits (n); 

	char *num;
	
	num = (char*) malloc ((count+1)*sizeof(char));
	
	j = count-1;
	
	
	for (i = 1; i < count +1; i++){ 
	
		num[j] = str((n % (int) pow (10,i)-x)/ (int) pow (10, i-1)) ;
		
		x = n%(int) pow(10,i);
		
		j--;
		
	}
	
	num[count] = '\0';
	
	return num;
}


char *file_name (int n){

	int i, j = 0, k = 0, space, count;
	
	count = count_digits (n);

	char *name, *num;
	char  str0[5] = "temp", str1[5] = ".txt";
	
	space = (int) ((sizeof(str0) + sizeof (str1))/ sizeof(char)) + count +1;
	
	name  = malloc (space*sizeof(char));
	
	num =  (char*) int_to_str (n);
	
	// Filling up the name string 
	
	for (i = 0; i < sizeof(str0)/sizeof(str0[0]); i++){
	
		name [i] = str0[i];
		
	}
	
	name [space] = '\0';
	
	return name;

}


int main (void){
	
	int n = 5678472;
	
	char *name;
	
	name = (char*) file_name (n);
	
	printf("%s \n", name);
	
	free (name);
	



	return 0;
}
