set title "Diffusion on a thin rod"
set xlabel "t"
set ylabel "x"
set zlabel "u (x, t)"
set hidden3d
set dgrid3d 50,50 qnorm 10
splot "sim_data.txt" w lines lc 12, "exact_data.txt"  w lines lc 3