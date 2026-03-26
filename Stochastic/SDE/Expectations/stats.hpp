# include <iostream>
# include <iomanip>
# include <new>
# include <cmath>
# include <cstdlib>

typedef long double ld;

class Stats {

    public: 

        Stats (ld *, size_t);

        ld E_X (void);

        ld Var_X (void);
    
    private:

        ld *x = nullptr;

        size_t x_size;
};