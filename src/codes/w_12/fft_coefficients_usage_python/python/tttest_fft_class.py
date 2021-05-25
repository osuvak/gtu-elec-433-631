#!/usr/bin/python

# /*
#  * This file is part of the "dev-in-place" repository located at:
#  * https://github.com/osuvak/dev-in-place
#  * 
#  * Copyright (C) 2020  Onder Suvak
#  * 
#  * For licensing information check the above url.
#  * Please do not remove this header.
#  * */

"""
Updates:
  Commented through with interspersed questions on
    Thu May 14 15:47:55 AST 2020
"""

import getopt, sys
"""
N:
  We are going to make use the imports above for what is
    called "Command Line Argument Processing".
Q:
  Look up what the getopt module is all about.
"""

import matplotlib
#matplotlib.use("gtk")
matplotlib.use("QT4Agg")
"""
Q:
  This is a driver script and there is going to be no 
    plotting except indirectly due to the calls in this script.
    Then why do I need the imports and calls about matplotlib
    in this script?
"""

import math as ml
import numpy as np
import matplotlib.pyplot as plt

import os_fft_operations as sm
"""
Q:
  Above is the module with the recently coded class definition
    inside it. How is it possible to import the module above
    without specifying its path?
"""

def test_dummy():
  print "Dummy Test called."
  
def test_sine_cosine():
  N = 21
  T = 1.e-3
  t = np.linspace(0., T, 1+N)
  """
  Q:
    How can we quickly construct a 2D numpy array out of two
      arrays?
  """
  x = np.array(
    [ np.sin(2 * np.pi / T * t) ,
      np.cos(2 * np.pi / T * t) ] )
  """
  Q:
    How do I get rid of the last column of a 2D array?
    Would the syntax "x[:] = x[:, :-1]" generate errors?
  """
  x = x[:, :-1]
  
  results = []
  for kk in range(x.shape[0]):
    """
    N:
      Below is how a newly instantiated class instance reference
        can be stored inside a list in python.
    Q:
      Compare the "shape"s of x and x[kk, :]. How are they 
        different? Why would the class instance not be able
        to operate on a numpy array with shape (1, N) and would
        be able to do so with an array with shape (N,)? Note
        that we need the comma in (N,) for it to be interpreted
        as a tuple.
    """
    results.append( 
      sm.fft_coefs_manipulator( x[kk, :] ) )
    #results[-1].set_flag_plot_maximize(False)
    #results[-1].change_plot_type('plot')

  for kk in range( len(results) ):
    title_str_t = 'Signal %d in Time Domain'  % (1+kk)
    results[kk].plot_time(title_str_t)
    title_str_f = 'Signal %d in Freq. Domain' % (1+kk)
    results[kk].plot_freq(title_str_f)
    
    """
    N:
      The ctor of the class instance immediately calls
        "to_freq". I call "to_time" below and then invoke
        the plotters to check if the transformations are
        working correctly.
    """
    results[kk].to_time()
    
    title_str_t = 'Signal %d in Time Domain'  % (1+kk)
    results[kk].plot_time(title_str_t)
    title_str_f = 'Signal %d in Freq. Domain' % (1+kk)
    results[kk].plot_freq(title_str_f)
    
def test_step_function():
  N = 21
  ratio = 0.3
  
  x = np.zeros((1, N))
  """
  Q:
    What is a shortcut to assign the same scalar value to
      multiple entries within a numpy array?
  """
  x[0, 0:(ml.ceil(ratio*N))] = 1
        
  """
  Q:
    Do I need to store a single class instance reference in
      a list?
  """
  results = []
  results.append( sm.fft_coefs_manipulator(x[0]) )
  results[-1].plot_time()
  results[-1].plot_freq()
  
def test_triangular():
  N = 101
  K = (N-1) / 2
  x = np.zeros((1, N))
  #print type(x)
  #print x.shape
  """
  Q:
    Why do I need the "float()" call below?
  """
  x[0, 0:(1+K)] = ( np.arange(1, 2+K) - 1 ) / float(K)
  #print type(x)
  #print x.shape
  """
  Q:
    How do I obtain a number of entries within an array
      with indices (consequently order of entries) reversed?
  """
  x[0, (1+K):N] = x[0, (-1+K)::-1]
  
  results = []
  """
  Q:
    The shape of x should turn out to be (1, N). Why am I
      not instantiating the class with x but with x[0]? Crucial
      question.
  """
  results.append( sm.fft_coefs_manipulator(x[0]) )
  """
  N:
    Switching to plot instead of stem, since the number of
      samples is big, with stem the figure will not look nice.
  """
  results[-1].change_plot_type('plot')
  results[-1].plot_time()
  results[-1].plot_freq()
  
  """
  N:
    Computing the derivative in discrete time through an
      operation carried out in the discrete frequency domain.
  Q:
    Again recall the Gibbs phenomenon or look it up.
  """
  oa = results[-1]
  oa.compute_derivative_in_time()
  oa.plot_time()
  oa.plot_freq()
  
  """
  N:
    Can revert to original, because the original input data
      in discrete time is stored in the class instance.
  """
  oa.revert_to_original()
  oa.plot_time()
  oa.plot_freq()
    
"""
Q:
  The structure of the layout of tests and the declaration of
    the dictionary below could be nicer. Perhaps it would be
    better if the defs above were encapsulated by a class,
    and we would then be able to obtain a list of callable
    member variables of the class instance (i.e., member
    functions) whose names satisfy a certain pattern. Therefore,
    obtaining the names of the tests would be automated, and
    the dictionary below would be much more easy to construct in
    automation. Work on the suggested structure and implement it.
  The lambdas below are utilized only for calling the defs above.
    Do these lambdas not need any input parameters? Is it not
    usual for lambdas to have input parameters?
"""
tests_dict = \
  {
    'dummy' : 
      lambda : test_dummy() ,
    'sine_cosine' : 
      lambda : test_sine_cosine() ,
    'step_function' : 
      lambda : test_step_function() ,
    'triangular' : 
      lambda : test_triangular() ,
    }

"""
N:
  Below is the piece of code for command line
    argument processing.
Q:
  Check if the "ch" variable with None assigned ever
    going to be used as a key in an attempt to unsuccessfully
    obtain the corresponding value in the dictionary tests_dict?
"""
ch = None
try:
  """
  Q:
    How do we tell the getopt module to check for necessary
      command line arguments and how do we tell it which of the 
      expected arguments should be checked to have values
      assigned, as in "example=MyExample", with the syntax
      not exactly as indicated?
    What is the difference between sys.argv[1:] and sys.argv?
      Is the former missing some entries with respect to the
      latter? If YES, what is it that is missing?
  """
  opts, args = \
    getopt.getopt( sys.argv[1:], 
                   "e:", ["example="] )
except getopt.GetoptError as err:
  print str(err)
  """
  Q:
    How would you write a suitable usage string for this script,
      to be shown when necessary to communicate to the user how
      to use this script, with which arguments to call it?
  """
  #usage()
  sys.exit(-1)
  
"""
Q:
  Are alternative pieces of syntax available when the example or
    test to be run is given to the script through a command line
    argument?
"""
for o, a in opts:
  if o in ("-e", "--example"):
    ch = a
  else:
    pass

"""
Q:
  How to check if a key exists in a dictionary?
"""
if ch not in tests_dict:
  raise KeyError('No key \'%s\' in dictionary.' % str(ch))

"""
Q:
  Actual test call below. Why do we have the parentheses "()"
    as well?
"""
tests_dict[ch]()
"""
Q:
  Why should we in the general case not have the call below
    in the modules where the actual code for generating
    plots? Why is it preferably placed in a final driver script
    and located there possibly as the last call in the indicated
    script?
"""
plt.show()
