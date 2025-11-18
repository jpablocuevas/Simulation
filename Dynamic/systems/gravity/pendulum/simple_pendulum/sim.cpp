# include "sim.hpp"

Pend :: Pend (ld dt, ld t_f, ld theta_0, ld theta_t_0, ld g, ld l) {

	g_val = g;
	
	l_val = l;
	
	theta_old = theta_0;
	
	theta_t_old = theta_t_0;
	
	theta_tt_old = acc (theta_0);
	
	Verlet_vel (dt, t_f);
}


Pend :: ld Pend :: acc (ld theta) {
	
	return - g_val / l_val * sin (theta);
}

void Pend :: Verlet_vel (ld dt, ld t_f) {

	t = 0.;
	
	// Initial conditions 
	
	std :: cout << "g = " << g_val << '\n';
	
	std :: cout << "l = " << l_val << '\n';
	
	std :: cout << "theta_0 = " << theta_old << '\n';
	
	std :: cout << "theta_t_0 " << theta_t_old << '\n';
	
	// Pendulum position file 
	
	file.open ("positions.txt", std :: ios :: out);
	
	// Verlet algorithm
	
	while (t < t_f) {
	
		theta_t_mid = theta_t_old + dt / 2. * theta_tt_old;
		
		theta_new = theta_old + dt * theta_t_mid;
		
		theta_tt_new = acc (theta_new);
		
		theta_t_new = theta_t_mid + dt / 2. * theta_tt_new;
		
		theta_old = theta_new;
		
		theta_t_old = theta_t_mid;
		
		theta_t_mid = theta_t_new;
		
		theta_tt_old = theta_t_new;
		
		file << l_val * cos (theta_new) << ' ' << l_val * sin (theta_new);
		
		file << '\n';
		
		t = t + dt;
	}
	
	file.close ();
}


