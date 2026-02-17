# include "ising.hpp"


int main (void) {

    long seed = 19674236486920;

    srand (time (&seed));

    std :: cout << std :: fixed << std :: setprecision (10);

    size_t L = 100, C = 10000;

    std :: string init_grid = "up";

    ld J = 1., B = 0.;

    ld *beta;

    size_t beta_size = 1;

    beta = new ld [beta_size];

    /*ld beta_0 = 1. / 10., dbeta = 0.05;

    for (size_t i = 0; i < beta_size; i ++) {

        *(beta + i) = beta_0 + dbeta;

        beta_0 = *(beta + i);
    }*/

    *(beta + 0) = 0.48;

    Ising sim (L, C, init_grid, J, B, &*(beta + 0), beta_size);

    delete [] beta;

    return 0;
}