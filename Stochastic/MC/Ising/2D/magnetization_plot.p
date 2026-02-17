set encoding utf8

set title '2D Ising model mean magnetization, L = 40' font "Times-Roman, 18"
set xlabel "(β J) ^ - 1" font "Times-Roman, 18"
set ylabel "<M>" font "Times-Roman, 18"
set xrange [0:4]
set yrange [-1:1]

plot "magnetization_data.txt" using 1:2 title "Analytical solution" lt 3 lc 4 ps 1#, "magnetization_data.txt" using 1:3 title "MC simulation" lt 7 lc 8 ps 1
