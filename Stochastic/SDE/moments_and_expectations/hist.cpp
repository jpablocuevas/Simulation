# include "stats.hpp"
# include <fstream>

int main (void) {

    ld *rand_data;

    size_t rand_data_size = 2000000;

    Rand_nums random (rand_data_size);

    rand_data = random.Lin_Cong_dis ();

    random.print_arr (rand_data, 50);

    random.print_parameters ();

    // Partition of the interval (0, 1) into equally spaced parts of length 10 ^ -2 each and 
    // counting the number of random numbers that lie within each sub-interval

    ld a = 0., b = 1., dx = pow (10, -2);

    size_t N = abs (b - a) / dx;

    size_t *count_data = new size_t [N];

    std :: fstream file;

    file.open ("hist_data.txt", std :: ios :: out);

    size_t i, j;

    for (i = 0; i < N; i ++) {

        for (j = 0; j < rand_data_size; j ++) {
            
            if (*(rand_data + j) >= a + i * dx && *(rand_data + j) <= a + (i + 1) * dx) {

                *(count_data + i) = *(count_data + i) + 1;
            }
        }

        file << i << ' ' << *(count_data + i) << '\n';
    }

    file.close ();

    random.print_arr (count_data, N);

    Stats stats (rand_data, 50);

    std :: cout << stats.E_X () << '\n';

    std :: cout << stats.Var_X () << '\n';

    stats.clear_data ();

    delete [] rand_data;

    delete [] count_data;

    return 0;
}