# include <iostream>
# include <iomanip>
# include <new>
# include <cmath>
# include <fstream>

# define pi 3.1415926535

typedef long double ld;

class Rod {

    public:

        Rod (size_t, size_t, ld);

    private: 

        size_t N_x, N_t;

        ld *x = nullptr;

        ld *t = nullptr;

        ld **u = nullptr;

        ld dx = 0., dt = 0., t_f, courant;

        std :: fstream file_sim, file_exact;

        void alloc_lattice (void);

        void dealloc_lattice (void);

        void simulate (void);

        ld u_exact (ld, ld);

        void print_arr (ld *, size_t);

};