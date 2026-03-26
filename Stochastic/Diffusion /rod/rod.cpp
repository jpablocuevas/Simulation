# include "rod.hpp"

Rod :: Rod (size_t N_x, size_t N_t, ld t_f) {

    this -> N_x = N_x;

    this -> N_t = N_t;

    this -> t_f = t_f;

    alloc_lattice ();

    simulate ();

    dealloc_lattice ();
}

void Rod :: alloc_lattice (void) {

    size_t i;

    // Memory allocation

    x = new ld [N_x];

    if (x == nullptr) {

        std :: cout << "Memory allocation for x failed. \n";

        exit (1);
    }

    t = new ld [N_t];

    if (t == nullptr) {

        std :: cout << "Memory allocation for t failed. \n";

        exit (1);
    }

    u = new ld * [N_t];

    if (u == nullptr) {

        std :: cout << "Memory allocation for u failed. \n";

        exit (1);
    }

    for (i = 0; i < N_t; i ++) {

        *(u + i) = new ld [N_x];

        if (*(u + i) == nullptr) {

            std :: cout << "Memory allocation for *(u + " << i << ") failed. \n";

            exit (1);
        }
    }

    // Step sizes

    dx = (1 - 0) / ld (N_x - 1);

    dt = (t_f - 0) / ld (N_t - 1);

    courant = dt / (dx * dx);

    // Lattice setup

    size_t j = 1;

    for (i = 0; i < N_x; i ++) {
        
        *(x + i) = 0 + (j - 1) * dx;

        j ++;
    } 
    
    j = 1;

    for (i = 0; i < N_t; i ++) {
        
        *(t + i) = 0 + (j - 1) * dt;

        j ++;
    }

    j = 0;

    // Boundary conditions and file management.

    file_sim.open ("sim_data.txt", std :: ios :: out);

    file_exact.open ("exact_data.txt", std :: ios :: out);

    file_sim.precision (15);

    file_exact.precision (15);

    for (j = 0; j < N_x; j ++){
        
        *(*(u + 0) + j) = sin (pi * *(x + j));

        file_sim << 0. << ' ' << *(x + j) << ' ' << *(*(u + 0) + j) << '\n';

        file_exact << 0. << ' ' << *(x + j) << ' ' << u_exact(*(x + j), 0) << '\n';
    }

    print_arr (*(u + 0), N_x);

    print_arr (*(u + 1), N_x);
}

void Rod :: dealloc_lattice (void) {

    delete [] x;

    delete [] t;

    for (size_t i = 0; i < N_t; i ++) {

        delete [] *(u + i);
    }

    delete u;
}

void Rod :: simulate (void) {

    // i is for time, j for space

    std :: cout << "Simulation of the diffusion equation on a thin rod. \n";

    std :: cout << " Step sizes: \n dx: " << dx << ", dt = " << dt << ".\n";

    std :: cout << "Courant parameter: " << courant << ".\n";

    size_t i, j;

    for (i = 0; i < N_t - 1; i ++) {

        for (j = 1; j < N_x - 1; j ++) {

            u[i + 1][j] = u[i][j] + courant * (u[i][j + 1] - 2. * u[i][j] + u[i][j - 1]);

            file_sim << *(t + i) << ' ' <<  *(x + j) << ' ' << *(*(u + i) + j) << '\n';

            file_exact << *(t + i) << ' ' <<  *(x + j) << ' ' << u_exact(*(x + j), *(t + i)) << '\n';
        }

        file_sim << '\n';

        file_exact << '\n';
    }

    file_sim.close ();

    file_exact.close ();
}

ld Rod :: u_exact (ld x, ld t) {

    return sin (pi * x) * exp (- pi * pi * t);
}

void Rod :: print_arr (ld *arr, size_t arr_size) {
    
    for (size_t i = 0; i < arr_size; i ++) {

        std :: cout << *(arr + i) << '\n';
    }
}