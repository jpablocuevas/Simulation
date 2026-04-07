# include <iostream>
# include <iomanip>
# include <new>
# include <cmath>
# include <cstdlib>
# include "rand_nums.hpp"

typedef long double ld;

class Stats {

    public: 

        Stats ();

        ld E_X (ld *, size_t);

        ld Var_X (ld *, size_t);
};