# include "rand_nums.hpp"

int main (void) {

    long int seed = 13465784931339969;

    srand (time (&seed));

    std :: cout << std :: fixed << std :: setprecision (10);

    ull X_0, a = ull (pow (7, 5)), b = 0, c = ull (pow (2, 31) - 1);

    X_0 = ull (rand ());

    size_t U_size = 21474833;
    
    Rand_nums random (X_0, a, b, c, U_size);

    ld *U, *X_2_point, *X_exp;

    U = random.Lin_Cong_dis ();

    random.print_arr (U, 30);

    delete [] U;

    std :: cout << "Two point distribution \n";

    ld x_1 = -1, x_2 = 1, p_1 = 0.5;

    X_2_point = random.Two_Point_dis (x_1, x_2, p_1);

    random.print_arr (X_2_point, 20);

    delete [] X_2_point;

    std :: cout << "Exponential distribution \n";

    ld lambda = 2.;

    X_exp = random.Exp_dis (lambda);

    random.print_arr (X_exp, 30);

    delete [] X_exp;

    std :: cout << "Gaussian distribution, Box-Müller algorithm \n";

    ld **X_box_muller; 

    X_box_muller = random.Box_Muller_dis ();

    random.print_arr (*(X_box_muller + 0), 20);

    random.print_arr (*(X_box_muller + 1), 20);

    delete [] *(X_box_muller + 0);

    delete [] *(X_box_muller + 1);

    delete [] X_box_muller;

    std :: cout << "Gaussian distribution, Polar-Marsiaga algorithm \n";

    ld **X_polar_marsiaga;

    X_polar_marsiaga = random.Polar_Marsiaga_dis ();

    random.print_arr (*(X_polar_marsiaga + 0), 20);

    random.print_arr (*(X_polar_marsiaga + 1), 20);

    delete [] *(X_polar_marsiaga + 0);

    delete [] *(X_polar_marsiaga + 1);

    delete [] X_polar_marsiaga;

    return 0;
}