# include "rand_nums.hpp"


Rand_nums :: Rand_nums (ull X_0, ull a, ull b, ull c, size_t U_size) {

    this -> X_0 = X_0;

    this -> a = a;

    this -> b = b;

    this -> c = c;

    this -> U_size = U_size;
    
}


ld * Rand_nums :: Lin_Cong_dis (void) {

    ld *U = new ld [U_size];

    *(U + 0) = ld (X_0) / c;

    for (size_t i = 1; i < U_size; i ++) {

        X_1 = (a * X_0 + b) % c;

        *(U + i) = ld (X_1) / c;

        X_0 = X_1;
    }

    return U;
}

ld * Rand_nums :: Two_Point_dis (ld x_1, ld x_2, ld p_1) {

    std :: cout << "Generating random numbers... \n";

    ld *X = new ld [U_size];

    ld *U = new ld [U_size];

    U = Lin_Cong_dis ();

    for (size_t i = 0; i < U_size; i ++) {

        if (*(U + i) <= p_1) {

            *(X + i) = x_1;
        }

        else {

            *(X + i) = x_2;
        }
    }

    delete [] U;

    std :: cout << "Algorithm completed.\n";

    return X;
}

ld * Rand_nums :: Exp_dis (ld lambda) {

    std :: cout << "Generating random numbers... \n";

    ld *X = new ld [U_size];

    ld *U = new ld [U_size];

    U = Lin_Cong_dis ();

    for (size_t i = 0; i < U_size; i ++) {

        *(X + i) = - log (1. - *(U + i)) / lambda;
    }

    delete [] U;

    std :: cout << "Algorithm completed.\n";

    return X;
}

ld ** Rand_nums :: Box_Muller_dis (void) {

    std :: cout << "Generating random numbers... \n";

    ld *X_1 = new ld [U_size];

    ld *X_2 = new ld [U_size];

    ld *U_1 = new ld [U_size], *U_2 = new ld [U_size];

    U_1 = Lin_Cong_dis ();

    U_2 = Lin_Cong_dis ();

    for (size_t i = 0; i < U_size; i ++) {

        *(X_1 + i) = sqrt (- 2. * log (*(U_1 + i))) * cos (2 * pi * *(U_2 + i));

        *(X_2 + i) = sqrt (- 2. * log (*(U_1 + i))) * sin (2 * pi * *(U_2 + i));
    }

    delete [] U_1;

    delete [] U_2;

    ld **X = nullptr;

    X = new ld * [2];

    *(X + 0) = X_1;

    *(X + 1) = X_2;

    std :: cout << "Algorithm completed.\n";

    return X;
}

ld ** Rand_nums :: Polar_Marsiaga_dis (void) {

    std :: cout << "Generating random numbers... \n";

    ld *X_1 = new ld [U_size];

    ld *X_2 = new ld [U_size];

    ld *U_1 = new ld [U_size], *U_2 = new ld [U_size];

    U_1 = Lin_Cong_dis ();

    U_2 = Lin_Cong_dis ();

    ld W, V_1, V_2;

    for (size_t i = 0; i < U_size; i ++) {

        V_1 = 2. *  *(U_1 + i) - 1.;

        V_2 = 2. *  *(U_2 + i) - 1.;

        W = V_1 * V_1 + V_2 * V_2;
        
        *(X_1 + i) = V_1 * sqrt (- 2 * log (W) / W);

        *(X_2 + i) = V_2 * sqrt (- 2 * log (W) / W);
    }

    delete [] U_1;

    delete [] U_2;

    ld **X = nullptr;

    X = new ld * [2];
    
    *(X + 0) = X_1;

    *(X + 1) = X_2;

    std :: cout << "Algorithm completed.\n";

    return X;
}

void Rand_nums :: print_arr (ld *X, size_t X_size) {

    for (size_t i = 0; i < X_size; i ++) {

        std :: cout << *(X + i) << '\n';
    }
}