set encoding utf8

set title 'Angle vs time' font "Times-Roman, 18"
set xlabel "x" font "Times-Roman, 18"
set ylabel "y" font "Times-Roman, 18"
set xrange [-5:5]
set yrange [-2:2]

plot "angle.txt" using 1:2 title "angle" lt 7 lc 10 ps 1
