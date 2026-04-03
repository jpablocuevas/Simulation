# include "stats.hpp"

int main (void) {

    Rand_nums random;

    ld *rand_data = random.Lin_Cong_dis ();

    random.print_arr (rand_data, 50);

    random.print_parameters ();

    Stats stats (rand_data, 50);

    std :: cout << stats.E_X () << '\n';

    std :: cout << stats.Var_X () << '\n';

    stats.clear_data ();

    delete [] rand_data;

    return 0;
}