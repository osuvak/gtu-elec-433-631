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
  Updates
    Commented through with questions on
      Wed Jun 17 11:05:58 AST 2020
"""

import numpy  as np
import math   as ml
import random as rnd
"""
  Q:
    What is an import alias?
    What would we do to import just a single submodule
      inside a module with an alias?
    Is it possible to import multiple modules with a single
      import command?
"""
rnd.seed()
"""
  Q:
    What does the command above do? If I did not have this
      one in the octave implementation, how must I have decided
      that a seed determination is not necessary to be carried
      out by the developer?
    What is the default seed for the random number generator
      when called as above? Why would we refrain from feeding
      a seed with a constant value to the generator? Also
      what does the above call tell us about the seed value
      determined being global or local? What may be the
      advantages or disadvantages associated with either
      alternative (i.e., global or local seed value)?
"""

"""
  Q:
    What do we do for line continuation for a single command?
      We have examples below for assignments.
"""
no_mc = 100000
lam   = 1. / 10
time_to_wait = \
  10.
total_min_in_hour = \
  60.

"""
  Q:
    What is the list data structure in python?
    What is a generator (I am not referring to the random
      number generator in here) in python?
    How will the random variable samples generated with
      "rnd.random()" below be distributed? What will be
      probabilistic distribution associated?
    And what happens when we multiply the samples generated
      by "rnd.random()" with a constant, as in the python
      generator below? How will the resulting samples be
      distributed now?
"""
arrival_times = \
  [ total_min_in_hour*rnd.random() for kk in range(no_mc) ]
"""
  Q:
    What is the return type of "np.zeros()", as used below?
      Is it one that corresponds directly to the matrix data
      structure of octave? Or is it something else?
    What are the dimensions for "result" below going to be?
      How can we check the dimensions through the "shape"
      attribute? And what is the type for the "shape" attribute
      of "result"?
"""
result = \
  np.zeros(no_mc)

"""
  Q:
    What is the return type for each of "range()" and "len()"?
    Could not I have utilized "np.arange()" instead of "range()"?
      Are the return types for the stated functions the same?
      If not how can they be used interchangably in the statement
      below?
    What does "range()" return with a single input argument?
      Are there other possibilities for the input argument set of
      "range()"?
    Could I iterate through "arrival_times" in a different way,
      possibly making use of the "in" keyword? Why do I not
      prefer the indicated alternative in here?
"""
for kk in range(len(arrival_times)):
  if arrival_times[kk] > total_min_in_hour - time_to_wait:
    continue
  else:
    """
      Q:
        What is the common type for the "True" and "False" values
          in python?
    """
    flag_valid_sample = False
    """
      Q:
        Does it matter what "sample" is assigned to at this
          point? What is special about the "None" type? Are
          there any contexts where the usage of "None" perhaps
          makes more sense?
    """
    sample = None
    while not flag_valid_sample:
      u = rnd.random()
      """
        Q:
          What is the difference between "1" and "1." in python?
            Would the value of "x" below differ if I had used
            "1" instead of "1." in the indicated assignment?
          How is the call for the "log()" function different
            compared to the call in octave? Are there any more
            functions encapulated inside the "math" module?
      """
      x = - 1. / lam * ml.log(1. - u)
      if arrival_times[kk] + x < total_min_in_hour:
        flag_valid_sample = True
        sample = x
    if sample > time_to_wait:
      result[kk] = 1.

print "Probability of Waiting for more than 10 min:"
"""
  Q:
    Notice that I did not have to code a function to sum up
      the entries in "result", how is that possible? What is
      "np.sum()" able to do in order to compute the stated
      sum?
    If you have a type that you defined yourself in python,
      perhaps through a class definition of yours, how would
      you enable the "len()" function to operate on it? Checking
      the member functions for the type that "result" belongs to
      would help in this case.
"""
print "  %.6f" % ( np.sum(result) / len(result) )