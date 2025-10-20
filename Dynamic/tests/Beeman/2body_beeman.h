// -------------- Functions for the Beeman algorithm applied to the two body problem ---------------

#include <stdio.h>

typedef long double ld;

// ------------------------- Functions ------------------------

// Function that prints a vector

void print_vec (ld *, size_t);

// Distance function between two points

ld dis (ld *, ld *, size_t);

// Returns the acceleration from the gravitational potential

ld *acc (int, ld, ld, ld*, ld*, size_t);

// Function that updates the position given its velocity. It is used to obtain a (t) from a (t - dt) for the algorithm

ld *x_step (ld*, ld*, ld , size_t);

// Updates the velocity from the old and next positions and accelerations

ld *v_step (ld *, ld *, ld *, ld *, ld, size_t);

// Function that updates new and old coordinates

void update (ld *, ld *, size_t );

// Beeman's algorithm

void beeman (ld, ld, ld, int, size_t);




