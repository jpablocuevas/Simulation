# include <iostream>
# include <new>
# include <fstream>
# include <cstdlib>
# include <ctime>

typedef long double ld;

class Mem {

    public:

        Mem (size_t, size_t);

        Mem (size_t);

        size_t N, M;

        ld *x = nullptr;

        ld **X = nullptr;

        std :: fstream file;

        ld *alloc_arr (void);

        ld **alloc_matrix (void);

        void dealloc_arr (void);

        void dealloc_matrix (void);

        void rand_arr (void);

        void rand_matrix (void);

        void print_arr (void);
        
        void print_matrix (void);

        void create_file (ld *, ld *, size_t, std :: string);
        
};