# include <iostream>
# include <iomanip>
# include <new>
# include <fstream>
# include <cstdlib>
# include <cmath>

typedef long double ld;

class Ising {

    public: 

        Ising (size_t N, size_t C, std :: string config, ld mu, ld B, ld J, ld *T, 
    size_t T_size); // Constructor that sets the paramets of the simulation

        ld rand_num (ld, ld); // Random number in the interval [a, b]

        static void print_arr (ld *, size_t); // Prints an arbitrary array 

    private:

        // -------------------- Simulation parameters --------------------

        size_t N, C; // Number of total spins, number of cycles.

        ld mu, B, J; // Magnetic moment, external magnetic field, interaction parameter.

        std :: string config;

        ld *M_sim_arr = nullptr ; // Stores the average magnetization / spin  from the MC simulation.
        
        ld *M_exact_arr = nullptr; // Stores the avg magnetizacion / spin from the exact solution.

        ld *S = nullptr; // Stores the entire configuration information.

        // -------------------- Looping and file parameters --------------------

        size_t i, j, k;  // Iterators.

        std :: fstream file;
                
        // -------------------- Simulation modules --------------------

        void set_system (void); // Starts the system's configuration.
        
        ld H (size_t, bool); // Computes the total energy of the chain.

        ld M_avg_exact (ld); // Computes the exact total magnetization / spin.

        ld M_tot_sim (void); // Computes the simulated total magnetization / spin.

        void Metropolis (ld *, size_t); // Metropolis algorithm simulation.
       
        void create_file (ld *, size_t); // Creates the file to plot simulated vs exact magnetization / spin.
};