set encoding utf8

set title '2D Ising model thermalization, β = 0.48, L = 100' font "Times-Roman, 18"
set xlabel "C (cycles)" font "Times-Roman, 18"
set ylabel "<m>" font "Times-Roman, 18"
set xrange [0:1000]
set yrange [0:1]

plot "thermalization_data.txt" using 1:2 title "" lt 7 lc 24 with lines
