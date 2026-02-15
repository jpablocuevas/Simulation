# include "lj.hpp"

int main (void) {

    time_t seed;

    srand (time (&seed));

    std :: cout << std :: fixed  << std :: setprecision (12);

    // Simulation parameters

    size_t parts_cell = 27, n_cells = 27; // These numbers have to be perfect cubes

    ld L[3] = {100., 100., 100.};

    ld delta[3];

    ld T = 2., dt = 0.001, t_total = 0.1, r_c = *(L + 0) / 2.;

    for (size_t i = 0; i < 3; i ++) {

        *(delta + i) = *(L + i) / 10.;
    }

    // Simulation constructor

    LennJon sim (parts_cell, n_cells, &(*(L + 0)), &(*(delta + 0)), T, dt, t_total, r_c);

    return 0;
}
