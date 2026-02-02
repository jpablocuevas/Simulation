set encoding utf8

set title 'Grid 0' font "Times-Roman, 18"
set xlabel "x^{*}" font "Times-Roman, 18"
set ylabel "y^{*}" font "Times-Roman, 18"
set zlabel "z^{*}" font "Times-Roman, 18"
set xrange [-55: 55];
set yrange [-55: 55];
set zrange [-55: 55];

splot "positions0.txt" lt 7 lc 9 ps 1
