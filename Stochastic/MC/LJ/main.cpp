# include "lj.hpp"

int main (void) {

    time_t seed;

    srand (time (&seed));

    std :: cout << std :: fixed  << std :: setprecision (12);

    // Simulation parameters

    size_t parts_cell = 64, n_cells = 3;

    LennJon :: ld L[3] = {100., 100., 100.};

    LennJon :: ld delta[3] = {}

    LennJon :: ld T = 2., dt = 0.001, t_total = 0.1, r_c = *(L + 0) / 2.;

    // Simulation constructor

    LennJon sim (parts_cell, n_cells, &(*(L + 0)), &(*(delta + 0)) T, dt, t_total, r_c);

    return 0;
}
