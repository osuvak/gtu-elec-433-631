%  Onder Suvak (C) 2021
close all
clear variables
clear classes

oa = myclass();
oa.number = 5;

disp('number in oa :')
disp( sprintf('%4d', oa.number) )

fh = @(x) x * oa.number;

disp('fh(2) :')
disp( sprintf('%4d', fh(2)) )

oa.number = 4;

disp('number in oa :')
disp( sprintf('%4d', oa.number) )

disp('fh(2) :')
disp( sprintf('%4d', fh(2)) )

clear oa;
disp('Cleared ''oa''.')

disp('fh(2) :')
disp( sprintf('%4d', fh(2)) )
