# include "stats.hpp"

int main (void) {

    size_t X_size = size_t (pow (10, 3));
    
    Rand_nums rand (X_size);

    ld *X_exp;
    
    ld lambda = 0.5;

    X_exp = rand.Exp_dis (lambda); 

    //rand.print_arr (X_exp, X_size);

    size_t sizes [4] = {0, 0, 0, 0};

    size_t i;

    for (i = 0; i < X_size; i ++) {

        if (*(X_exp + i) >= 1) {

            *(sizes + 0) = *(sizes + 0) + 1;
        }

        if (*(X_exp + i) >= 2) {

            *(sizes + 1) = *(sizes + 1) + 1;

        }

        if (*(X_exp + i) >= 3) {

            *(sizes + 2) = *(sizes + 2) + 1;
        }

        if (*(X_exp + i) >= 4) {

            *(sizes + 3) = *(sizes + 3) + 1;
        }
    }

    ld *X_1, *X_2, *X_3, *X_4;

    size_t x_1 = 0, x_2 = 0, x_3 = 0, x_4 = 0;

    X_1 = new ld [*(sizes + 0)];

    X_2 = new ld [*(sizes + 1)];

    X_3 = new ld [*(sizes + 2)];

    X_4 = new ld [*(sizes + 3)];

    for (i = 0; i < X_size; i ++) {

        if (*(X_exp + i) >= 1) {

            *(X_1 + x_1) = *(X_exp + i);

            x_1 ++;
        }

        if (*(X_exp + i) >= 2) {

            *(X_2 + x_2) = *(X_exp + i);

            x_2 ++;
        }

        if (*(X_exp + i) >= 3) {

            *(X_3 + x_3) = *(X_exp + i);

            x_3 ++;
        }

        if (*(X_exp + i) >= 4) {

            *(X_4 + x_4) = *(X_exp + i);

            x_4 ++;
        }
    }

    Stats stats;

    std :: cout << "Numerical conditional expectation: \n";

    std :: cout << "E (X | a = 1) = " << stats.E_X (X_1, *(sizes + 0)) << '\n';

    std :: cout << "E (X | a = 2) = " << stats.E_X (X_2, *(sizes + 1)) << '\n';

    std :: cout << "E (X | a = 3) = " << stats.E_X (X_3, *(sizes + 2)) << '\n';

    std :: cout << "E (X | a = 4) = " << stats.E_X (X_4, *(sizes + 3)) << '\n';

    std :: cout << "Exact conditional expectation: \n";

    std :: cout << "E (X | a = 1) = " << 1 + 1 / lambda << '\n';

    std :: cout << "E (X | a = 2) = " << 2 + 1 / lambda << '\n';

    std :: cout << "E (X | a = 3) = " << 3 + 1 / lambda << '\n';

    std :: cout << "E (X | a = 4) = " << 4 + 1 / lambda << '\n';

    delete [] X_1;

    delete [] X_2;

    delete [] X_3;

    delete [] X_4;

    delete [] X_exp;

    return 0;
}