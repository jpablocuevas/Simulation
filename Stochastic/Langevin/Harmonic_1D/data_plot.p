set encoding utf8

set title 'U(x) = f / 2 x^2 − κx.  γ = 0.8, κ = 0.5, m = 1, f = 1, kB = 1' font "Times-Roman, 18"
set xlabel "t" font "Times-Roman, 18"
set ylabel "" font "Times-Roman, 18"
set xrange [0:101]
set yrange [0:1]

plot "particle_data.txt" using 1:2 title "" lt 7 lc 7 with lines, "particle_data.txt" using 1:3 title "velocity" lt 7 lc 22 with lines