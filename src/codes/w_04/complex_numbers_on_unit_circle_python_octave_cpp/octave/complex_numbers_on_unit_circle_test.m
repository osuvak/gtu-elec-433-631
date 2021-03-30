%  Onder Suvak (C) 2020

close all
clear variable
clear classes

rel_tol = 1e-06;
abs_tol = 1e-10;

no_pts = 100;

fh_check_relative ...
  = @(computed, desired) ...
      ( norm(computed - desired) ...
          <= abs_tol + rel_tol * norm(desired) );

angles ...
  = linspace(-pi, +pi, no_pts);
complex_points ...
  = exp(1j * angles);

angles_computed ...
  = atan2( ...
      imag(complex_points) , ...
      real(complex_points) );

unity_norm_check_values ...
  = abs( abs(complex_points) - 1 );
indices = find( unity_norm_check_values <= rel_tol );

flag_check_norm ...
  = isempty( setdiff( 1:numel(complex_points) , indices ) );

disp('Check for unity norm of all values on the complex unit circle :')
if flag_check_norm
  disp('  YES')
else
  disp('  NO')
end

flag_check_angles ...
  = fh_check_relative(angles_computed, angles);
  
disp('Check for compliance of each returned arg and original angle tuples :')
if flag_check_angles
  disp('  YES')
else
  disp('  NO')
end