# include "pend.hpp"


int main (void) {
	
	
	Double_pend :: ld dt = 0.1, t_f = 10, g = 9.81, pi = 3.141592653589;
	
	Double_pend :: ld theta_0 [2] = {pi / 10., pi / 5.}, theta_t_0 [2] = {-0.9, 0.4};
	
	Double_pend :: ld m [2] = {1, 1.748}, l[2] = {2.4, 1.8};
	
	Double_pend pendulum (dt, t_f, g, &theta_0[0], &theta_t_0[0], &m[0], &l[0]);
	
	return 0;
}




