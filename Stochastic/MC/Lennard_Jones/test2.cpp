# include <iostream>

class Test {

    public:

        Test (int val);

    private:
        
        int n[3];

        int val;

        void fill (void);

        void print (void);
};

Test :: Test (int val) {

    this -> val = val;

    fill ();

    print ();
}

void Test :: fill (void) {

    for (size_t i = 0; i < 3; i ++) {

        *(n + i) = - val / 3;
    }
}

void Test :: print (void) {

    for (size_t i = 0; i < 3; i ++) {

        std :: cout << *(n + i) << '\n';
    }
}

int main (void) {

    Test test (3);

    return 0;
}