# include "mem.hpp"

class Ising: public Mem {

    public:

        Ising (size_t, size_t, std :: string, ld, ld, ld *, size_t);

    private:

        std :: string set_grid;

        size_t L, C; // Grid size, number of cycles.

        ld J, B; // Interaction parameter, external magnetic field.

        ld **S = nullptr; // Matrix that stores the configuration of the system. 

        ld *m = nullptr; // Average magnetization per site.

        void init_grid (void); // Initiates the grid with PBC.

        ld H (size_t, size_t, bool); // Computes the Hamiltonian of the system.

        void Metropolis (ld *, size_t); // MC implementation using the Metropolis algorithm.

        ld rand_num (ld, ld); // Random number in the interval (a, b).

        ld M_avg_sim (void); // Average magnetizatio from the simulation.

        ld M_avg_analytical (ld); // Analytical solution of the average magnetization. This is only valid in the B = 0 case.
};