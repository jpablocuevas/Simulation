// --------------- Functions for the Verlet integration applied to a simple pendulum ---------------

typedef long double ld;


ld acc (ld, ld, ld);

ld theta_step (ld, ld, ld);

void stoermer_verlet (ld, ld, ld, ld, ld, int);

void vel_verlet (ld, ld, ld, ld, ld, int);
