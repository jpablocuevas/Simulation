set encoding utf8

set title 'U(x) = f / 2 x^2 − κx' font "Times-Roman, 18"
set xlabel "t" font "Times-Roman, 18"
set ylabel "x(t)" font "Times-Roman, 18"
set xrange [0:101]
set yrange [0:1]

plot "data_1.txt" using 1:2 title "γ = 0.259" lt 7 lc 7 with lines, "data_2.txt" using 1:2 title "γ = 4.73" lt 7 lc 22 with lines, "data_3.txt" using 1:2 title "γ = 8.86" lt 7 lc 17 with lines, 