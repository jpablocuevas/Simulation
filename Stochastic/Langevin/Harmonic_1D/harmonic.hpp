# include <iostream>
# include <iomanip>
# include <new>
# include <fstream>
# include <cmath>
# include <cstdlib>

typedef long double ld;

typedef unsigned long long int ull;

class Harmonic {

    public:

        Harmonic (ld f, ld kappa, ld gamma[3], ld m, ld dt, ld t_f, ld x0, ld v0, ull X_1_seed, ull X_2_seed);

    private:

        ld f, kappa, gamma[3], m; // External forces, friction coefficient, mass of the particle.

        ld dt, x_0, v_0; // Time-step, initial position, intial velocity;
        
        size_t N; // Array size;

        ld *x = nullptr, *v = nullptr, *time = nullptr; // Position, velocity and time arrays;

        ld x_mid (ld, ld); // Position midpoint.

        ld v_mid (ld, ld, ld, ld); // Velocity midpoint.

        ld x_new (ld, ld, ld, ld); // Positions update.

        ld v_new (ld, ld, ld, ld); // Velocity update.

        void Euler (ld, ld, ld, std :: string); // Simulation algorithm.

        std :: fstream file; // File object.

        void create_file (std :: string); // Particle data file.

        ld *F = nullptr; // Array that stores random numbers with normal distribution.

        ld *F_rand (ull, ull); // Box-Muller algorithm. Returns a pointer to an array of random numbers.

        void print_arr (ld *, size_t);

        void reset (ld *, size_t);
    };