# include "harmonic.hpp"

int main (void) {

    // Random numbers parameters

    long seed = 19674236486920;

    srand (time (&seed));

    ull X_1_seed = rand (), X_2_seed = rand ();

    // Simulation parameters

    ld f = 1., m = 1., kappa = 0.5;

    ld dt = 0.05, t_f = 100;

    ld gamma[3] = {0.259, 4.73, 8.86};

    // Initial conditions

    ld x_0 = 0.45, v_0 = - 1.35;

    // Simulation

    Harmonic sim (f, kappa, gamma, m, dt, t_f, x_0, v_0, X_1_seed, X_2_seed);

    return 0;
}