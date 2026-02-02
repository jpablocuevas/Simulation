# include "mem.hpp"

int main (void) {

    Mem :: ld ***tens1, ***tens2;

    Mem :: ld ** grid1, **grid2;
    
    Mem :: ld *arr1, *arr2;

    Mem mem_tens (3, 4, 3), mem_grid (5, 6), mem_arr (10);

    // Tensors

    tens1 = mem_tens.alloc_tens ();

    mem_tens.get_tens_size ();

    tens2 = mem_tens.alloc_tens ();

    mem_tens.set_tens_rand (tens1);

    mem_tens.set_tens_rand (tens2);

    std :: cout << "tens_1: " << '\n';

    std :: cout << '\n';

    mem_tens.print_tens (tens1);

    std :: cout << "tens_2: " << '\n';

    std :: cout << '\n';

    mem_tens.print_tens (tens2);

    std :: cout << '\n';

    // Grids

    grid1 = mem_grid.alloc_grid ();

    grid2 = mem_grid.alloc_grid ();

    mem_grid.get_grid_size ();

    mem_grid.set_grid_rand (grid1);

    mem_grid.set_grid_rand (grid2);

    std :: cout << "grid_1: " << '\n';

    std :: cout << '\n';

    mem_grid.print_grid (grid1);

    std :: cout << "grid_2: " << '\n';

    std :: cout << '\n';

    mem_grid.print_grid (grid2);

    std :: cout << '\n';
    
    // Arrays

    arr1 = mem_arr.alloc_arr ();

    arr2 = mem_arr.alloc_arr ();

    mem_arr.get_arr_size ();

    mem_arr.set_arr_rand (arr1);

    mem_arr.set_arr_rand (arr2);

    std :: cout << "arr_1: " << '\n';

    std :: cout << '\n';

    mem_arr.print_arr (arr1);

    std :: cout << "arr_2: " << '\n';

    std :: cout << '\n';

    mem_arr.print_arr (arr2);

    mem_tens.dealloc_tens (tens1);

    mem_tens.dealloc_tens (tens2);

    mem_grid.dealloc_grid (grid1);

    mem_grid.dealloc_grid (grid2);

    mem_arr.dealloc_arr (arr1);

    mem_arr.dealloc_arr (arr2);

    return 0;
}