# include <iostream>
# include <iomanip>
# include <cstdlib>
# include <ctime>

typedef long double ld;

ld my_rand (ld a, ld b) {

    ld min = a;

    if (b <= a) {

        min = b;
    }

    return (abs (b - a) * (ld) rand () / RAND_MAX) + min;
}

int main (void) {

    time_t seed;

    srand (time (&seed));

    std :: cout << std :: fixed  << std :: setprecision (12);

    ld a = -5.2948, b = 8.384754;

    for (unsigned int i = 0; i < 30; i ++) {

        std :: cout << my_rand (a, b) << '\n';
    }
}