# include <iostream>
# include <iomanip>
# include <new>
# include <cstdlib>
# include <ctime>

typedef long double ld;

typedef unsigned long long int ull;

# define pi 3.14159265358979

class Rand_nums {

    public:

        Rand_nums (ull X_0, ull a, ull b, ull c, size_t U_size);

        void print_arr (ld *, size_t);

        ld * Lin_Cong_dis (void); // Linear congruential generator. Uniform distribution in (0, 1).

        ld * Two_Point_dis (ld x_1, ld x_2, ld p_1); // Two point generator.

        ld * Exp_dis (ld); // Exponential distribution generator.

        ld ** Box_Muller_dis (void); // Gaussian Box-Müller algorithm generator.

        ld ** Polar_Marsiaga_dis (void); // Gaussian Polar-Marsiaga algorithm generator.

    private: 

        ull X_0, X_1, a, b, c; // U (0, 1) uniform distribution parameters.
        
        size_t U_size; // Uniform distribution array size.
};