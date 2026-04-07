# include "stats.hpp"

Stats :: Stats () {

}

ld Stats :: E_X (ld *data, size_t data_size) {

    ld mu = 0;

    for (size_t i = 0; i < data_size; i ++) {

        mu = mu + * (data + i);
    }

    return mu / ld (data_size);
}

ld Stats :: Var_X (ld *data, size_t data_size) {

    ld sigma_2 = 0;

    ld mu = E_X (data, data_size);

    for (size_t i = 0; i < data_size; i ++) {

        sigma_2 = sigma_2 + pow (*(data + i) - mu, 2.);
    }

    return sigma_2 / ld (data_size - 1);
}