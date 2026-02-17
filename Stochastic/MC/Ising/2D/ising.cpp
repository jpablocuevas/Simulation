# include "ising.hpp"

Ising :: Ising (size_t L, size_t C, std :: string set_grid, ld J, ld B, ld *beta, size_t beta_size): Mem (L + 2, L + 2) {

    // L + 2 rows and cols are passed to the allocation of the grid due to PBC
    
    this -> L = L;

    this -> set_grid = set_grid;

    this -> C = C;

    this -> J = J;

    this -> B = B;

    // Memory allocation 

    S = alloc_matrix ();

    M_arr = new ld [C];

    M_avg_arr = new ld [beta_size];

    m_avg_arr = new ld [C];

    // Initial conditions

    init_grid ();

    // Calling the simulation algorithm

    Metropolis (beta, beta_size);

    // Memory deallocation

    dealloc_matrix ();

    delete [] M_arr;

    delete [] M_avg_arr;

    delete [] m_avg_arr;
}

void Ising :: init_grid (void) {

    size_t i, j;

    ld alpha;

    if (set_grid == "up") {

       for (i = 1; i < N - 1; i ++) {
            
            for (j = 1; j < M - 1; j ++) {
                
                *(*(S + i) + j) = ld (1.);
            }
        }
    }

    else if (set_grid == "down") {

        for (i = 1; i < N - 1; i ++) {
            
            for (j = 1; j < M - 1; j ++) {
                
                *(*(S + i) + j) = ld (- 1.);
            }
        }
    }

    else {

        for (i = 1; i < N - 1; i ++) {
            
            for (j = 1; j < M - 1; j ++) {
                
                alpha = ld (rand ()) / RAND_MAX;

                if (alpha > 0.5) {

                    *(*(S + i) + j) = 1.;
                }

                else {

                    *(*(S + i) + j) = - 1.;
                }
            }
        }
    }

    // Periodic boundary conditions

    // Sets the top and bottom rows

    for (j = 0; j < M; j ++) {

        *(*(S + 0) + j) = *(*(S + N - 2) + j);

        *(*(S + N - 1) + j) = *(*(S + 1) + j);
    }

    // Sets the left and right columns

    for (i = 0; i < N; i ++) {

        *(*(S + i) + 0) = *(*(S + i) + N - 2);

        *(*(S + i) + N - 1) = *(*(S + i) + 1);
    }
}

ld Ising :: H (size_t x, size_t y, bool flip) {

    ld J_sum, B_sum;

    size_t i, j;

    if (flip == true) {

        *(*(S + x) + y) =  - 1. * *(*(S + x) + y);
    }

    for (i = 1; i < L + 1; i ++) {

        for (j = 1; j < L + 1; j ++) {

            J_sum = J_sum + S[i + 1][j] * S[i - 1][j] * S[i][j + 1] * S[i][j -1];

            B_sum = B_sum + *(*(S + i) + j);
        }
    }

    return - J * J_sum / 2. - B * B_sum; // We divide by two because each atom in a bond is counted twice.
}

ld Ising :: M_avg_analytical (ld beta) {

    return ld (pow (1. - 1. / pow (sinh (2. * J * beta), 4.), 1. / 8.));
}

ld Ising :: M_total (void) {

    ld M = 0.;

    size_t i, j;

    for (i = 1; i < L + 1; i ++) {

        for (j = 1; j < L + 1; j ++) {

            M = M + *(*(S + i) + j);
        }
    }

    return abs(M); // We return the total magnetization in the absolute value. 
}

ld Ising :: M_avg_sim () {

    ld s = 0.;

    for (size_t i = 0; i < C; i ++) {

        s = s + *(M_arr + i);
    }

    return s / C;
}

ld Ising :: rand_num (ld a, ld b) {

    return  (ld) abs (b - a) * (ld) rand () / RAND_MAX + a;
}

void Ising :: magnetization_data (ld *x, ld *y, ld *z, size_t size, std :: string name) {

    file.open (name + ".txt", std :: ios :: out);

    for (size_t i = 0; i < size; i ++) {

        file << *(x + i) << ' ' << *(y + i) << ' ' << *(z + i) << '\n';
    }

    file.close ();

}

void Ising :: Metropolis (ld *beta, size_t beta_size) {

    ld H_old = 0., H_new = 0., dH = 0.;

    size_t x_part, y_part;

    size_t i, j;

    ld *cycles;

    cycles = new ld [C];

    // Monte-Carlo loop

    std :: cout << "Simulation starting... \n";
    
    std :: cout << "β = " << *(beta + 0) << '\n';

    std :: cout << "Initial configuration: " << set_grid << '\n';

    for (i = 0; i < beta_size; i ++) {

        for (j = 0; j < C; j ++) {

            // Selects a particle at random from the grid coordinates 

            x_part = size_t (rand_num (1, L + 1));

            y_part = size_t (rand_num (1, L + 1));

            // Computes the energy due to the flipped spin

            H_old = H (x_part, y_part, false);

            H_new = H (x_part, y_part, true);

            dH = H_new - H_old;

            // Metropolis criteria of acceptance

            if (dH > 0.) {

                if (rand_num (0., 1.) > exp (*(beta + i) * dH)) {

                    // Since the function H changes the spin, if the configuration is rejected
                    // the spin is switched back to its original value. If accepted, nothing else
                    // happens. 

                    *(*(S + x_part) + y_part) = - 1. * *(*(S + x_part) + y_part);
                }
            }     
            
            //*(M_arr + j) = M_total ();

            *(m_avg_arr + j) = M_total () / ld (L * L); // Mean magnetization per site.

            *(cycles + j) = ld (j);
        }

        *(M_avg_arr + i) = M_avg_sim ();

        // Thermalization file

        create_file (cycles, m_avg_arr, C, "thermalization_data");
    }

    std :: cout << "Simulation finished. \n";

    // Magnetization data file

    /*ld *J_arr, *M_analytical_arr;

    J_arr = new ld [beta_size];

    M_analytical_arr = new ld [beta_size];

    for (size_t i = 0; i < beta_size; i ++) {

        *(J_arr + i) = 1 / (*(beta + i) * J);

        *(M_analytical_arr + i) = M_avg_analytical (*(beta + i));
    }

    magnetization_data (J_arr, M_analytical_arr, M_avg_arr, beta_size, "magnetization_data");

    delete [] J_arr;

    delete [] M_analytical_arr;*/

    delete [] cycles;
 }
