# include "mem.hpp"
# include <cmath>

class LennJon : public Mem {

    public:

        LennJon (size_t parts_cell, size_t n_cells, ld *L, ld *delta, ld T, ld dt, ld t_total, ld r_c);

    private:

        size_t parts_cell, n_cells;  // Particles per cell, number of cells

        ld L[3], dx[3]; // Simulation cell size, step size to initialize particles in a cell

        ld delta[3]; // Trial move array size

        short n[3]; // Array that stores the position of the i-th simulation cell

        size_t n_part[3]; // Counts the number of particles per side of the simulation cell

        ld T, dt, t_total, r_c; // Temperature, time, time step, total time, cutoff radius

        ld ***X = nullptr;// Stores the positions of all particles in all cells

        ld x[3]; // Coordinates of the randomly selected particle to be moved.

        void set_grid_cube (ld **, short*); // Sets the i-th cell in a cubic array
        
        ld dis (ld *, ld *); // Distance between two particles

        ld my_rand (ld a, ld b); // Uniform random number in the interval (a, b)

        ld U_LJ (size_t); // Potential energy of the system

        void move (size_t); // Moves a random particle 

        void Metropolis (void); // Metropolis-Monte Carlo simulation algorithm 
};
