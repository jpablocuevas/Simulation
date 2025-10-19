# include <stdio.h>
# include <stdlib.h>
# include <time.h>

typedef long double ld;

unsigned int i, j;

ld **alloc_matrix (size_t);

ld **alloc_arr (size_t);

void dealloc_matrix (ld **, size_t);

void dealloc_array (ld *);

void init_matrix_rand (ld **, size_t);

void init_array_rand (ld *, size_t);

void print_matrix (ld **, size_t);

void print_array (ld *, size_t);
