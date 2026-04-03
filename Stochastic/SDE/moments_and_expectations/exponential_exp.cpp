# include "rand_nums.hpp"
# include "stats.hpp"

int main (void) {

    long int seed = 13465784931339969;

    srand (time (&seed));

    std :: cout << std :: fixed << std :: setprecision (10);

    ull X_0, a = ull (pow (7, 5)), b = 0, c = ull (pow (2, 31) - 1);

    X_0 = ull (rand ());

    size_t U_size = size_t (pow (10, 3));
    
    Rand_nums rand (X_0, a, b, c, U_size);

    ld *X_exp;
    
    ld lambda = 0.5;

    X_exp = rand.Exp_dis (lambda);

    

    delete [] X_exp;

    return 0;
}