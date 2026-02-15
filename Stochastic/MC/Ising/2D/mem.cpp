# include "mem.hpp"

Mem :: Mem (size_t N) {

    this -> N = N;

    alloc_arr ();
}

Mem :: Mem (size_t N, size_t M) {

    this -> N = N;

    this -> M = M;

    alloc_matrix ();
}

ld * Mem :: alloc_arr (void) {

     x = new ld [N];

    if (x == nullptr) {

        std :: cout << "arr memory allocation failed. \n";

        exit (1);
    }

    return x;
}

ld ** Mem :: alloc_matrix (void) {

    X = new ld* [N];

    if (X == nullptr) {

        std :: cout << "Matrix memory allocation failed. \n";

        exit (1);
    }

    for (size_t i = 0; i < N; i ++) {

        *(X + i) = new ld [M];
    }

    return X;
}

void Mem :: dealloc_arr (void) {

    delete [] x;
}

void Mem :: dealloc_matrix (void) {

    for (size_t i = 0; i < N; i ++) {

        delete [] *(X + i);
    }

    delete [] X;
}

void Mem :: print_arr (void) {

    for (size_t i = 0; i < N; i ++) {

        std :: cout << *(x + i) << '\n';
    }
}

void Mem :: print_matrix (void) {

    size_t i, j;

    for (i = 0; i < N; i ++) {

        for (j = 0; j < M; j++) {

            std :: cout << *(*(X + i) + j) << ' ';
        }

        std :: cout << '\n';
    }
}

void Mem :: rand_arr (void) {

    for (size_t i = 0; i < N; i ++) {

        *(x + i) = ld (rand ()) / RAND_MAX;
    }
}

void Mem :: rand_matrix (void) {

    size_t i, j;

    for (i = 0; i < N; i ++) {

        for (j = 0; j < M;  j++) {

           *(*(X + i) + j) = ld (rand ()) / RAND_MAX;
        }
    }
}

void Mem :: create_file (ld *x, ld *y, size_t size, std :: string name) {
	
	file.open (name + ".txt", std :: ios :: out);
    
	for (size_t i = 0; i < size; i ++) {

        file << *(x + i) << ' ' << *(y + i) << '\n';
	}
	
	file.close ();
}
