%  Onder Suvak (C) 2021

close all
clear variables
clear classes

N  = 101;
f0 = 1e3;
no_periods = 5;

T = 1 / f0;
t = linspace( ...
    0. , no_periods * T , no_periods * N + 1 );

x = [ cos( 2 * pi * f0 * t ) ; ...
      sin( 2 * pi * f0 * t ) ];

figure;
plot(t , x , 'LineWidth' , 3 )
title ( sprintf( '%d Periods of Sine/Cosine' , no_periods ) )
xlabel( 't (sec)' )
ylabel( 'Signal' )
grid on