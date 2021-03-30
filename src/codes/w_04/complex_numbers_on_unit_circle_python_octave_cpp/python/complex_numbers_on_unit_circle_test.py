#!/usr/bin/python

#Onder Suvak (C) 2020

import numpy as np

rel_tol = 1e-06
abs_tol = 1e-10

no_pts = 100

fh_check_relative \
  = lambda computed, desired : \
      ( np.linalg.norm(computed - desired) \
          <= abs_tol + rel_tol * np.linalg.norm(desired) )

angles \
  = np.linspace(-np.pi, +np.pi, no_pts)
complex_points \
  = np.exp(1.j * angles)

angles_computed \
  = np.arctan2(
      np.imag(complex_points) ,
      np.real(complex_points) )

unity_norm_check_values \
  = np.abs( np.abs(complex_points) - 1. )
indices = np.where( unity_norm_check_values <= rel_tol )

flag_check_norm \
  = ( 0 == len( np.setdiff1d( 
                  range(len(complex_points)) , indices ) ) )
                  #np.arange(len(complex_points)) , indices ) ) )

print 'Check for unity norm of all values on the complex unit circle :'
if flag_check_norm:
  print '  YES'
else:
  print '  NO'

flag_check_angles \
  = fh_check_relative(angles_computed, angles);
  
print 'Check for compliance of each returned arg and original angle tuples :'
if flag_check_angles:
  print '  YES'
else:
  print '  NO'
