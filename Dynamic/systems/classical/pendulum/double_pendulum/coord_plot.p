set encoding utf8

set title 'Double pendulum' font "Times-Roman, 18"
set xlabel "x" font "Times-Roman, 18"
set ylabel "y" font "Times-Roman, 18"
set xrange [-5:5]
set yrange [-2:2]

plot "positions.txt" using 1:2 title "pendulum 1" lt 7 lc 22 ps 1, "positions.txt" using 3:4 title "pendulum 2" lt 7 lc 8 ps 1

