# include "stats.hpp"

Stats :: Stats (ld *x, size_t x_size) {

    x = new ld [x_size];

    for (size_t i = 0; i < x_size; i ++) {

        this -> x[i] = x[i];
    }

}

ld Stats :: E_X (void) {

    ld mu = 0;

    for (size_t i = 0; i < x_size; i ++) {

        mu = mu + * (x + i);
    }

    return mu / ld (x_size);
}

ld Stats :: Var_X (void) {

    ld sigma_2 = 0;

    ld mu = E_X ();

    for (size_t i = 0; i < x_size; i ++) {

        sigma_2 = sigma_2 + pow (*(x + i) - mu, 2.);
    }

    return sigma_2 / ld (x_size - 1);
}