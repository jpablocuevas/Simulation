# include "pend.hpp"

Double_pend :: Double_pend (ld dt, ld t_f, ld g, ld *theta_0, ld *theta_t_0, ld *m, ld *l) {	
	
	// System setup 
	
	g_val = g;
	
	m1 = *(m + 0);
	m2 = *(m + 1);
	
	l1 = *(m + 0);
	l2 = *(m + 1);
	
	// Memory allocation
	
	theta_old = new ld [2];
	theta_new = new ld [2];
	
	theta_t_old = new ld [2];
	theta_t_mid = new ld [2];
	theta_t_new = new ld [2];
	
	theta_tt_old = new ld [2];
	theta_tt_new = new ld [2];
	
	// Initial conditions
	
	for (i = 0; i < 2; i ++) {
		
		*(theta_old + i) = *(theta_0 + i);
		
		*(theta_t_old + i) = *(theta_t_0 + i);
	}

	// Velocity verlet function
	
	Verlet_vel (dt, t_f);
	
	delete [] theta_old;
	delete [] theta_new;
	
	delete [] theta_t_old;
	delete [] theta_t_mid;
	delete [] theta_t_new;
	
	delete [] theta_tt_old;
	delete [] theta_tt_new;
	
}

void Double_pend :: acc (ld *theta, ld *theta_t, ld *theta_tt) {
	
	// These new variables are defined for clarity purpouses only, for the expressions for the angular acceleration of both angles are somewhat cumbersome
	
	ld theta1, theta2, theta1_t, theta2_t;
	
	theta1 = *(theta + 0);
	theta2 = *(theta + 1);
	
	theta1_t = *(theta_t + 0);
	theta2_t = *(theta_t + 1);
	
	ld d;
	
	d = m1 + m2 - m2 * pow (cos(theta1 - theta2), 2);
	
	// Acceleration for each angle 
	
	*(theta_tt + 0) = - (g_val * (2 * m1 + m2) * sin(theta1) + g_val * m2 * sin(theta1- 2 * theta2) + l1 * m2 * sin(2 * (theta1 - theta2)) * pow (theta1_t, 2) + 2 * l2 * m2 * sin(theta1 - theta2) * pow (theta2_t, 2)) / (2 * l1 * d); 
	
	*(theta_tt + 1) = sin (theta1-theta2) * (g_val * (m1 + m2) * cos (theta1) + l1 * (m1 + m2) * pow (theta1_t, 1) + l2 * m2 * cos(theta1 - theta2) * pow (theta2_t, 2)) / (l2 *d);
	
}

void Double_pend :: update (ld *x_old, ld *x_new) {

	for (i = 0; i < 2; i ++) {
		
		*(x_old + i) = *(x_new + i);
	}
}	

void Double_pend :: Verlet_vel (ld dt, ld t_f) {
	
	// Initial conditions
	
	std :: cout << "Initial positions" << '\n';
	
	std :: cout << "theta1_0 = " << *(theta_old + 0) << '\n';
	
	std :: cout << "theta2_0 = " << *(theta_old + 1) << '\n';
	
	std :: cout << "Initial velocities" << '\n';
	
	std :: cout << "theta1_t_0 = " << *(theta_t_old + 0) << '\n';
	
	std :: cout << "theta2_t_0 = " << *(theta_t_old + 1) << '\n';
	
	std :: cout << "Rod lengths: " << '\n';
	
	std :: cout << "l_1 = " << l1<< '\n';
	
	std :: cout << "l_2 = " << l2<< '\n';
	
	std :: cout << "Masses: " << '\n';
	
	std :: cout << "m_1 = " << m1<< '\n';
	
	std :: cout << "m_2 = " << m2<< '\n';
	
	std :: cout << "Gravitational acceleration: " << '\n';
	
	std :: cout << "g = " << g_val << '\n';
	
	// File oppening to map the pendulums' positions
	
	pos_file.open ("positions.txt", std :: ios :: out);
	
	ang_file.open ("angles.txt", std :: ios :: out);
	
	// Verlet algorithm
	
	t = 0;
	
	pos_file << l1 * sin (*(theta_old + 0)) << ' ' << - l1 * cos (*(theta_old + 0)) << ' ' << l1 * sin (*(theta_old + 0)) + l2 * sin (*(theta_old + 1)) << ' ' << - (l1 * cos (*(theta_old + 0)) + l2 *  cos (*(theta_old + 1)));
		
		pos_file << '\n';
		
		ang_file << t  << ' ' << *(theta_new + 0) << ' ' << *(theta_new + 1);
		
		ang_file << '\n';
		
	while (t < t_f) {
		
		acc (theta_old, theta_t_old, theta_tt_old);
		
		for (i = 0; i < 2; i ++) {
			
			*(theta_t_mid + i) = *(theta_t_old + i) + dt / 2. * *(theta_tt_old + i);
			
			*(theta_new + i) = *(theta_old + i) + dt * *(theta_t_mid + i);
		}
		
		acc (theta_new, theta_t_new, theta_tt_new);
		
		for (i = 0; i < 2; i ++) {
			
			*(theta_t_new + i) = *(theta_t_mid + i) + dt / 2. * *(theta_tt_new + i);
		}
		
		update (theta_old, theta_new);
		
		update (theta_t_old, theta_t_mid);
		
		update (theta_t_mid, theta_t_new);
		
		update (theta_tt_old, theta_tt_new);
		
		pos_file << l1 * sin (*(theta_new + 0)) << ' ' << - l1 * cos (*(theta_new + 0)) << ' ' << l1 * sin (*(theta_new + 0)) + l2 * sin (*(theta_new + 1)) << ' ' << - (l1 * cos (*(theta_new + 0)) + l2 *  cos (*(theta_new + 1)));
		
		pos_file << '\n';
		
		ang_file << t  << ' ' << *(theta_new + 0) << ' ' << *(theta_new + 1);
		
		ang_file << '\n';
		
		t = t + dt;
	}
	
	pos_file.close ();
	
	ang_file.close ();
}


