# include "mem.hpp"

class Ising: public Mem {

    public:

        Ising (size_t, size_t, std :: string, ld, ld, ld *, size_t);

    private:

        std :: string set_grid;

        size_t L, C; // Grid size, number of cycles.

        ld J, B; // Interaction parameter, external magnetic field.

        ld **S = nullptr; // Matrix that stores the configuration of the system. 

        ld *M_arr = nullptr; // Stores the total magnetization on each cycle.

        ld *M_avg_arr = nullptr; // Stores the average total magnetization after all cycles. 

        ld *m_avg_arr = nullptr; // Mean magnetization per site. 

        void init_grid (void); // Initiates the grid with PBC.

        ld H (size_t, size_t, bool); // Computes the Hamiltonian of the system.

        void Metropolis (ld *, size_t); // MC implementation using the Metropolis algorithm.

        ld rand_num (ld, ld); // Random number in the interval (a, b).

        ld M_total (void); // Total mangnetization of a configuration.

        ld M_avg_analytical (ld); // Analytical solution of the average magnetization. This is only valid in the B = 0 case.

        ld M_avg_sim (); // Returns the total average magnetization after all cycles are done.

        void magnetization_data (ld *, ld *, ld *, size_t, std :: string);
};