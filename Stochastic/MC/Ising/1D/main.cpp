#include "ising.hpp"


int main (void) {

    long int seed = 183848193;

    srand ((unsigned int) time (&seed));

    std :: cout << std :: fixed << std :: setprecision (20);

    size_t N = 500, C = 1000;

    ld B = 5., mu = -1., J = -2.;

    std :: string config = "up";

    // Throught this simulation the Boltzmann constant kB is set to unity

    // Creates an array of temperature values

    ld *T;

    size_t T_size = 200;

    T = new ld [T_size];

    ld T_0 = 0., dT = 0.5;

    for (size_t i = 0; i < T_size; i ++) {

        *(T + i) = T_0 + dT;

        T_0 = *(T + i);
    } 

    // Calls the simulation algorithm 

    Ising sim (N, C, config, mu, B, J, &(*(T + 0)), T_size);

    delete [] T;

    return 0;
}