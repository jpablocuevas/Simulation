# include "ising.hpp"


int main (void) {

    long seed = 19674236486920;

    srand (time (&seed));

    std :: cout << std :: fixed << std :: setprecision (10);

    size_t L = 40, C = 1000;

    std :: string init_grid = "random";

    ld J = 5, H = 3;

    ld *beta;

    size_t beta_size = 1;

    beta = new ld [beta_size];

    /*ld beta_0 = 0., dbeta = 0.5;

    for (size_t i = 0; i < beta_size; i ++) {

        *(beta + i) = beta_0 + dbeta;

        beta_0 = *(beta + i);
    }*/

    *(beta + 0) = 0.5;

    Ising sim (L, C, init_grid, J, H, &*(beta + 0), beta_size);

    delete [] beta;

    return 0;
}