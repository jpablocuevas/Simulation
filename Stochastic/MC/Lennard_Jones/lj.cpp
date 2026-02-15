#include "lj.hpp"

// Constructor 

LennJon :: LennJon (size_t parts_cell, size_t n_cells, ld *L, ld *delta, ld T, ld dt, ld t_total, ld r_c) : Mem (n_cells, parts_cell, 3) {

    // Simulation parameters

    this -> parts_cell = parts_cell;

    this -> n_cells = n_cells;

    for (i = 0; i < 3; i ++) {

        // I do not use pointer notation here because it does not compile

        this -> L[i] = *(L + i); 

        this -> delta[i] = *(delta + i);

        // Sets the distance among particles along the three Cartesian axes.

        *(dx + i) = *(L + i) / (ld) pow (parts_cell, 1. / 3.);
    }

    this -> T = T; 

    this -> dt = dt;

    this -> t_total = t_total;

    this -> r_c = r_c;

    // Memory allocation

    X = alloc_tens ();

    // Initial conditions

    for (i = 0; i < 3; i ++) {

        *(n + i) = - short (n_cells) / 3; // Starts the lattice vector in the last cell
    }   

    /*for (i = 0; i < n_cells; i ++) { // Setting every cell in a cubic array 

        set_grid_cube (*(X + i), &(*(n + 0)));

        for (j = 0; j < 3; j ++) {

        }
    }*/

    set_grid_cube (*(X + 0), &(*(n + 0)));

    print_grid (*(X + 0));

    create_file (*(X + 0), 0);
    
    // Simulation

    //Metropolis ();

    // Memory deallocation

    dealloc_tens (X);
}

//------------------- Simulation methods -------------------  

void LennJon :: set_grid_cube (ld **grid, short *n) {

     // Stars the particle counter per side of the box at one.

     for (i = 0; i < 3; i ++) {

        *(n_part + i) = 1;
     }

    for (i = 0; i < parts_cell; i ++) {

        for (j = 0; j < 3; j ++) {

            *(*(grid + i) + j) = - (*(L + j) + *(dx + j)) / 2. + *(n_part + j) * *(dx + j) + *(L + j) * *(n + j);
        }

        *(n_part + 0) = *(n_part + 0) + 1;

        if (*(n_part + 0) > (size_t) pow (parts_cell, 1. / 3.) + 1) {

            *(n_part + 0) = 1;

            *(n_part + 1) = *(n_part + 1) + 1;

        }

        if (*(n_part + 1) > (size_t) pow (parts_cell, 1. / 3.) + 1) {

                *(n_part + 0) = 1;

                *(n_part + 1) = 1;

                *(n_part + 2)  = *(n_part + 2) + 1;
            }
    }
}

ld LennJon :: dis (ld *x, ld *y) {

    ld s = 0;

    for (size_t i = 0; i < 3; i ++) {

        s = s + pow (*(x + i) - *(y + i), 2);
    }

    return sqrt (s);
}

    ld  LennJon :: my_rand (ld a, ld b) {

    ld min = a;

    if (b <= a) {

        min = b;
    }

    return (ld) abs (b - a) * (ld) rand () / RAND_MAX + min;
}

    ld LennJon :: U_LJ (size_t part) {

    ld U = 0, d;

    for (i = 0; i < parts_cell; i ++) {

        for (j = 0; j < parts_cell; j ++) {

        }
    }

    return U;
}

void LennJon :: move (size_t part) {

    for (i = 0; i < 3; i ++) {

       *(x + i) = my_rand (- *(L + i) / 3, *(L + i) / 3);
    }
}


void LennJon :: Metropolis (void) {

    ld U_old, U_new, t = 0;

    size_t part;

    while (t < t_total) {

        part = (size_t) my_rand (0, parts_cell * n_cells  - 1);


        t = t + dt;
    }

}
