# include "sys.h"

void sys (size_t N, ld dt, ld t_f, unsigned short int method) {
	
	// Memory allocation
	
	ld **X_old, **X_new;
	
	ld **V_old, **V_new;
	
	ld *M; 
	
	X_old = alloc_matrix (N);
	
	X_new = alloc_matrix (N);
	
	V_old = alloc_matrix (N);
	
	V_new = alloc_matrix (N);
	
	M = alloc_array (N);
	
	// Initial conditons
	
	FILE *masses, *init_pos, *init_vel;
	
	masses = fopen ("masses.txt", "r");
	
	init_pos = fopen ("init_positions.txt", "r");
	
	init_vel = fopen ("init_velocities.txt", "r");
	
	if (masses == NULL) {
		
		printf ("Masses file could not be opened! \n");
		
		exit (0);
	}
	
	if (init_pos == NULL) {
		
		printf ("Masses file could not be opened! \n");
		
		exit (0);
	}
	
	if (init_vel == NULL) {
		
		printf ("Masses file could not be opened! \n");
		
		exit (0);
	}
	
	
	for (i = 0; i < N; i ++)
	pos_verlet (X_old, X_new, V_old, V_new, M, N, dt, t_f);
	
	
	/*switch (method) {
	
		case 0:	
			
			pos_verlet (N, dt, t_f);
			
		case 1: 
		
			vel_verlet (N, dt, t_f);
			
		case 2:
			
			stoermer_verlet (N, dt, t_f);
			
		case 3:
			
			beeman (N, dt, t_f);
	}*/
	
	dealloc_matrix (X_old);
	
	dealloc_matrix (X_new);
	
	dealloc_matrix (V_old);
	
	dealloc_matrix (V_new);
	
}

void update (ld **X_old, ld **X_new, size_t N) {

	for (i = 0; i < N; i ++) {
		
		for (j = 0; j < 3; j ++) {
			
			*(*(X_old + i) + j) = *(*(X_new + i) + j);
		}
	}
}

void acc (ld *a, ld **X, ld *M, size_t N, unsigned int k) {
	
	x = *(X + k); // Vector that keeps track of the position of the k-th particle
	
	ld s = 0.;
	
	ld d, G = 4. * pi * pi; 
	
	for (i = 0; i < 3; i ++) {
		
		s = 0.;

		for (j = 0; j < N; j ++) {
		
			if (k - i == 0) {
				
				s = 0.;
				
				break;
			}
			
			else {
				
				d = dis (x, *(X + j));
				
				s = s + *(M + j) * (*(x + i) - *(*(X + j) + i)) / pow (d, 3);
			}
		} 
		
		*(a + i) = s;
	}
	
	for (i = 0; i < 3; i ++) {
		
		*(a + i) = - G* *(a + i);
	}
}

void pos_verlet (ld **X_old, ld **X_new, ld **V_old, ld **V_new, ld *M, size_t N, ld dt, ld t_f) {
	
	// Memory allocation
	
	ld **X_mid;
	
	X = alloc_matrix (N);
	
	ld *a;
	
	a = alloc_vector (3);
	
	// Verlet loop
	
	ld t = 0.;
	
	while (t < t_f) {
	
		for (i = 0; i < N; i ++) {
			
			for (j = 0; j < 3; j ++) {
				
				*(*(X_mid + i) + j) = *(*(X_mid + i) + j)  + dt / 2. * *(*(V_old + i) + j);
			}
			
			acc (a, X_mid, M, N, i);
			
			for (j = 0; j < 3; j ++) {
				
				*(*(V_new + i) + j) = *(*(V_old+ i) + j)  + dt * *(a + j);

				*(*(X_new + i) + j) = *(*(X_mid + i) + j)  + dt / 2. * *(*(V_new + i) + j);

			}
		}
		
		if ( (int) t % 20 == 0) {
			
			print_matrix (X_new, N);
		}
		
		t = t + dt;
	}
	
	dealloc_matrix (X_mid, N);
	
	dealloc_vector (a);
}	
		
/*void vel_verlet (size_t N, ld dt, ld t_f);
			
void stoermer_verlet (size_t N, ld dt, ld t_f);
		
void beeman (size_t N, ld dt, ld t_f);*/

/*void test (size_t N) {
	
	ld **X;
	
	X = alloc_matrix (N);
	
	init_matrix_rand (X, N);
	
	print_matrix (X, N);
	
	init_matrix_rand (X, N);
	
	print_matrix (X, N);
	
	dealloc_matrix (X, N);
}*/


