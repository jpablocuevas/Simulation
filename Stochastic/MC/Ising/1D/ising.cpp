#include "ising.hpp"

// Constructor 

Ising :: Ising (size_t N, size_t C, std :: string config, ld mu, ld B, ld J, ld *T, 
    size_t T_size) {

    this -> N = N;

    this -> C = C;

    this -> mu = mu;

    this -> B = B;

    this -> J = J;

    this -> config = config;

    // Memory allocation 
    
    S = new ld [N];

    M_sim_arr = new ld [T_size];

    M_exact_arr = new ld [T_size];

    // Calls the simulation function

    Metropolis (T, T_size);

    // Cleans the dynamically allocated memory

    delete [] S;

    delete [] M_sim_arr;

    delete [] M_exact_arr;

}

ld Ising :: rand_num (ld a, ld b) {

    return  (ld) abs (b - a) * (ld) rand () / RAND_MAX + a;
}

void Ising :: set_system (void) {

    ld alpha;
    
    size_t i;

    if (config == "up") {

        for (i = 0; i < N; i ++) {

            *(S + i) = 1;
        }
    }

    else if (config == "down") {

    for (i = 0; i < N; i ++) {

            *(S + i) = -1;
        } 
    }

    else if (config == "random") {

    for (i = 0; i < N; i ++) {

            alpha = rand_num (0., 1.);

            if (alpha > 0.5) {

                *(S + i) = 1;
            }
            
            else {

                *(S + i) = -1;
            }
        } 
    }         
}

ld Ising :: H (size_t spin, bool flip) {

    // This ensures that the last atom is sometimes randomly selected

    if (spin == N) {

        spin = N - 1;
    }

    ld M_energy = 0, J_energy = 0;

    if (flip == true) {

        *(S + spin) = -1 * *(S + spin);
    }

    for (size_t i = 0; i < N; i ++) {

        M_energy = M_energy + *(S + i);

        if (i == N - 1) {
            
            M_energy = M_energy + *(S + i);

            J_energy = J_energy + *(S + N - 1) * *(S + 0);

            continue;
        }

        J_energy = J_energy + *(S + i) * *(S + (i + 1));
            
    }

    return - mu * B * M_energy - J * J_energy;
}

void Ising :: Metropolis (ld *T, size_t T_size) {

    size_t spin;

    ld H_old, H_new, dH;

    for (i = 0; i < T_size; i ++) {

        *(M_exact_arr + i) = M_avg_exact (*(T + i));

        set_system ();

        // Metropolis-Hastings algorithm

        for (j = 0; j < C; j ++) {

            // Chooses a random atom whose spin is to be flipped. It goes up to N so that the last 
            // atom of the chain can also be chosen. 

            spin = (size_t) rand_num (0, N); 

            H_old = H (spin, false); // Computes the energy without the flipped spin on an atom.

            H_new = H (spin, true); // Computes the energy due to the flipped spin.

            dH = H_new - H_old;

            if (dH > 0) {

                if (rand_num (0., 1.) > exp (- dH / *(T + i))) {
                    
                    // Flips back the spin on the atom. New configuration is rejected.

                    *(S + spin) = - 1 * *(S + spin); 
                }
            }

            else {

                // The function H (size_t, bool) already flips the particle with index spin, so
                // if the configuration is accepted nothing changes.

                *(S + spin) = *(S + spin);
            }
        }

       *(M_sim_arr + i) =  mu * M_avg_sim () / N;
    }

    // File for plotting 

    create_file (T, T_size);
}
 
ld Ising :: M_avg_exact (ld T) {

    return (ld) mu * sinh (mu * B / T) / sqrt (pow (sinh (mu * B / T), 2) + exp (4 * J / T));
}

ld Ising :: M_avg_sim (void) {

    ld M = 0;

    for (size_t i = 0; i < N; i ++) {

        M = M + *(S + i);
    }

    return M;
}

void Ising :: print_arr (ld *arr, size_t arr_size) {

    for (size_t i = 0; i < arr_size; i ++) {
        
        std :: cout << *(arr + i) << '\n';
    }
}

void Ising :: create_file (ld *T, size_t T_size) {

    std :: cout << std :: fixed << std :: setprecision (20);

    file.open ("mean_magnetization_data.txt", std :: ios :: out);

    for (size_t i = 0; i < T_size; i ++) {

        file << *(T + i) << ' ' <<  *(M_exact_arr + i) << ' ' << *(M_sim_arr + i) << '\n';
    }

    file.close ();
}