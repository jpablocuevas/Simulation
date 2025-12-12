set encoding utf8

set title 'Angular displacement vs time' font "Times-Roman, 18"
set xlabel "t (s)" font "Times-Roman, 18"
set ylabel "θ (π rad)" font "Times-Roman, 18"
set xrange [-5:5]
set yrange [-2:2]

plot "angles.txt" using 1:2 title "θ_1 (t)" lt 7 lc 3 ps 1, "angles.txt" using 1:3 title "θ_2 (t)" lt 7 lc 5 ps 1
