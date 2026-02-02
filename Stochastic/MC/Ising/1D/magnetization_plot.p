set encoding utf8

set title 'MC simulation vs exact magnetization' font "Times-Roman, 18"
set xlabel "β" font "Times-Roman, 18"
set ylabel "M" font "Times-Roman, 18"
set xrange [0:101]
set yrange [0:1]

plot "mean_magnetization_data.txt" using 1:2 title "Exact solution" lt 7 lc 22 ps 1, "mean_magnetization_data.txt" using 1:3 title "MC simulation" lt 7 lc 10 ps 1
