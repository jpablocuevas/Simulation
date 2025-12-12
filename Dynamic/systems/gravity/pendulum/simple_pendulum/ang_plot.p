set encoding utf8

set title 'Angular displacement vs time' font "Times-Roman, 18"
set xlabel "t (s)" font "Times-Roman, 18"
set ylabel "θ (π rad)" font "Times-Roman, 18"
set xrange [-5:5]
set yrange [-2:2]

plot "angle.txt" using 1:2 title "θ(t)" lt 7 lc 10 ps 1
