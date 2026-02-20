# include "harmonic.hpp"


Harmonic :: Harmonic (ld f, ld kappa, ld gamma[3], ld m, ld dt, ld t_f, ld x_0, ld v_0, ull X_1_seed, ull X_2_seed) {

    // Simulation parameters

    this -> f = f;

    this -> kappa = kappa;

    for (size_t i = 0; i < 3; i ++) {

        this -> gamma[i] = gamma[i];
    }

    this -> m = m;

    this -> x_0 = x_0;

    this -> v_0 = v_0;

    this -> dt = dt;

    // Memory allocation

    N = size_t (t_f / dt);

    x = new ld [N];

    v = new ld [N];

    time = new ld [N];

    // Simulation 

    F = F_rand (X_1_seed, X_2_seed);

    Euler (dt, t_f, gamma[0], "data_1");

    Euler (dt, t_f, gamma[1], "data_2");

    Euler (dt, t_f, gamma[2], "data_3");

    // Memory deallocation

    delete [] x;

    delete [] v;

    delete [] time;

    delete [] F;

}

ld Harmonic :: x_mid (ld x_old, ld v_old){

    return x_old + dt / 2. * v_old;
}

ld Harmonic :: v_mid (ld x_old, ld v_old, ld F, ld gamma) {

    return v_old - gamma * dt / 2. * v_old + F / m * dt / 2. - (f * dt) / (2. * m) * x_old;
}

ld Harmonic :: x_new (ld x_old, ld v_old, ld F, ld gamma) {

        return x_old + v_mid (x_old, v_old, F, gamma) * dt;
}

ld Harmonic :: v_new (ld x_old, ld v_old, ld F, ld gamma) {

    return v_old - gamma * v_mid (x_old, v_old, F, gamma) * dt + F / m * dt - f / m * dt * x_mid (x_old, v_old);
}

void Harmonic :: Euler (ld dt, ld t_f, ld gamma, std :: string name) {

    std :: cout << "Simulation starting..." << '\n';

    std :: cout << "Simulation parameters: " << '\n';

    std :: cout << "γ = " << gamma << ",\n";
    
    std :: cout << "κ = " << kappa << ",\n";

    std :: cout << "m = " << m << ",\n";
   
    std :: cout << "f = " << f << ",\n";

    std :: cout << "kB = 1" << ".\n";

    std :: cout << "Initial conditions: \n";
    
    std :: cout << "x_0 = " << x_0 << ", v_0 = " << v_0 << '\n';

    // Initial conditions

    *(x + 0) = x_0;

    *(v + 0) = v_0;

    *(time + 0) = 0.;

    // Simulataion main loop

    ld t = 0.;

    for (size_t i = 1; i < N; i ++) {

        *(x + i) = x_new (x_0, v_0, *(F + i), gamma);

        *(v + i) = v_new (x_0, v_0, *(F + i), gamma);

        // Updates position, velocity and time step.

        x_0 = *(x + i);

        v_0 = *(v + i);

        *(time + i) = t;

        t = t + dt;
    }

    create_file (name);

    std :: cout << "Simulation finished. \n";

    // Resets all data for further simulations

    x_0 = *(x + 0);

    v_0 = *(v + 0);
    
    reset (x, N);

    reset (v, N);

    reset (time, N);

}

void Harmonic :: create_file (std :: string name) {

    file.open (name + ".txt", std :: ios :: out);

    for (size_t i = 0; i < N; i ++) {

        file << *(time + i) << ' ' << *(x + i) << ' ' << *(v + i) << '\n';
    }

    file.close ();
}

ld * Harmonic :: F_rand (ull X_1_seed, ull X_2_seed) {
		
        ull a_1 = pow (7, 5), b_1 = 0;
		
		ull a_2 = pow (6, 6), b_2 = 0;
		
		ull M = pow (2, 30) - 1; 

        ull X_1, X_2;
		
		ld pi = 3.141592653589;
		
		ld U_1, U_2;
		
		ld *Z_1 = new ld [M];
		
		ld *Z_2 = new ld [M];

        // Box-Muller algorithm

        std :: cout << "Generating random numbers... \n";

        for (size_t i = 0; i < M; i++) {
        
            X_1 = (a_1 * X_1_seed + b_1) - ull(((a_1 * X_1_seed + b_1) / M) * M); 

            X_2 = (a_2 * X_2_seed + b_2) - ull (((a_2 * X_2_seed + b_2) / M) * M);

// This is the computation of the remainder of the Euclidean division of a * seed + b and M, i.e., (a * seed + b) mod M.

            U_1 = ld (X_1) / M;
            
            U_2 = ld (X_2) / M;
            
            *(Z_1 + i) = sqrt (- 2 * log (U_1)) * cos (2 * pi * U_2);
            
            *(Z_2 + i) = sqrt (- 2 * log (U_1)) * sin (2 * pi * U_2);
            
            X_1_seed = X_1;
            
            X_2_seed = X_2;
        } 
		
        std :: cout << "Random numbers generated. \n";

		return Z_1;	
};


void Harmonic :: print_arr (ld *x, size_t x_size) {

    for (size_t i = 0; i < x_size; i ++) {

        std :: cout << *(x + i) << '\n';
    }
}


void Harmonic :: reset (ld *x, size_t x_size) {

    for (size_t i = 0; i < x_size; i ++) {

        *(x + i) = 0.;
    }
}
