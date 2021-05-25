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
  Commented through with interspersed questions on
    Thu May 14 14:55:36 AST 2020
"""

import matplotlib
#matplotlib.use("gtk")
matplotlib.use("QT4Agg")
"""
Q:
  The plotting engine I declare to use above may not apply
    for your platform. How do you get a list available
    plotting engines for yourself?
"""

"""
N:
  Import aliases below make life easier.
"""
import copy as cp
import numpy as np
import matplotlib.pyplot as plt

class fft_coefs_manipulator(object):
  """
  fft_coefs_manipulator(object)
    Computes fft coefficients of input signal and keeps the
    discrete time and frequency representations updated even if
    allowed operations are carried out on the signal.
  """
  
  def __init__(self, x_t, flag_real=True, w_o=1):
    """
    __init__
      ctor of class. Carries out the necessary initializations
      and has the fft coefficients of the input signal computed.
      By default the input signal is assumed to be real.
    """
    None
    
    """
    Q:
      Why not only assignments in the following two lines?
        Why do we need to copy and then store as member
        variables?
    """
    self.x_t_original = cp.copy(x_t)
    self.x_t = cp.copy(x_t)
    """
    Q:
      Do we particularly need to make use of the None type in here?
        Look up a situation where it would be meaningful to have
        the None type utilized.
    """
    self.x_f = None
    """
    Q:
      If self.x_t is of the numpy array type, then the following
        assignment should suggest to you some pieces of information
        about the dimensions of self.x_t. What are they?
      What does the "shape" call return in terms of type and
        nature of data?
    """
    self.N   = self.x_t.shape[0]
    """
    Q:
      If integers and floats are clearly distinct from each other,
        What should I assume about self.N, regarding the next
        line of assignment?
    """
    self.K   = (self.N - 1) / 2
    
    """
    N:
      np.arange returns ndarray type.
    Q:
      What is the difference between python and Octave when
        determining ranges of indices, with the syntax for
        np.arange given below as examples?
    """
    self.indices_t = np.arange(0, self.N)
    self.indices_f = np.arange(-self.K, 1+self.K)
    
    """
    Q:
      How are the default values for the member variables below
        defined?
    """
    self.flag_real \
      = flag_real
    self.w_o \
      = w_o
    
    """
    Q:
      For the two member variables below, do you think the values
        should definitely be determined in the ctor of the class
        and never modified afterwards?
    """
    self.flag_plot_maximize = True
    self.plot_type          = 'stem'
    
    """
    N:
      fft coefficients of the input signal computed below.
    """
    self.to_freq()
    
  def set_w_o(self, w_o):
    self.w_o = w_o
    """
    Q:
      Why does not it always make sense to be able to modify
        the fundamental frequency of the input signal in methods
        that are not the ctor?
    """
    
  def revert_to_original(self):
    self.x_t = cp.copy(self.x_t_original)
    self.to_freq()
    """
    N:
      I prefer to keep the original form of the signal to be
        able to revert to it in case the necessity arises. May
        not always make sense.
    Q:
      Why do I have to call the "to_freq" member function above?
    """
    
  def compute_derivative_in_time(self):
    self.x_f = \
      ( 1j * self.w_o * np.arange(-self.K, 1+self.K) ) \
      * self.x_f
    self.to_time()
    """
    N:
      This is one of the operations that can be carried out
        in the discrete frequency domain and will affect
        the representation in the discrete time domain so that
        effectively the time derivative is computed for the
        signal in hand.
    Q:
      Review the rationale behind the computation carried out
        above.
      Why am I calling the "to_time" member function?
      An octave translation for the piece of code above would
        possibly make use of the elementwise multiplication
        operator ".*"; however, above all I have is the plain
        "*" operator. How can the statements above accomplish
        what I would like them to, in this sense? As a hint,
        look up how numpy.array behaves with the "*" operator.
        Crucial question.
    """
    
  """
  N:
    The two member functions below definitely make sense; I
      should be able to modify my related preferences even
      after the construction of the class instance.
  Q:
    Why do you think it is so?
  """
  def change_plot_type(self, type_str):
    self.plot_type = type_str
    
  def set_flag_plot_maximize(self, lval):
    self.flag_plot_maximize = lval
    
  """
  Q:
    What is a decorator in python?
    Why is a static member function (method) necessary? Does
      a static member function make use of the "self" keyword?
      Does a static member function require a class instance
      to work on?
    How do we define a static member function in python?
  """
  @staticmethod
  def compute_plot_min_max(
    x, y, x_tol, y_tol):
    
    y_val_abs = np.abs( y.max() - y.min() )
    y_val_low  = - y_tol * y_val_abs + y.min()
    y_val_high = + y_tol * y_val_abs + y.max()
    
    x_val_abs = np.abs( x.max() - x.min() )
    x_val_low  = - x_tol * x_val_abs + x.min()
    x_val_high = + x_tol * x_val_abs + x.max()
    
    return x_val_low, x_val_high, y_val_low, y_val_high
    """
    N:
      This function is necessary to compute the boundaries
        of the window illustrated on a plot, the boundaries
        being dependent on the maximum and minimum levels of
        the data to be depicted.
    Q:
      Why do I make use of tolerances above?
      Explain how the high and low boundaries are computed
        above?
      If we are required to plot multiple sets of data on a
        single plot, would the syntax above suffice? How
        would you modify it to capture the necessity just
        stated?
      Is it possible to return multiple variables in a python
        function?
    """
    
  def plot_freq(self, title_str='Signal in Freq. Domain'):
    label_fontsize = 24
    ticks_labelsize= 24
    axis_border_lwidth = 3
    axis_plot_lwidth   = 4
    """
    N:
      Several plot related values to be utilized below defined
        as variables.
    """
    
    y_tol = 0.1
    x_tol = 0.005
    """
    N:
      Tolerances used to have the plots look nicer, otherwise we
        would have left it to the plotting engine to decide which
        window of the data is to be depicted, would in some
        cases cause lots of unused plotting area to be illustrated.
    """
    
    fig = plt.figure()
    rect = fig.patch
    rect.set_facecolor('white')
    """
    Q:
      Examining above, how do we set the background color for the
        space surrounding the actual plot in a figure?
    """
    
    x  = self.indices_f
    y  = self.x_f
    """
    Q:
      Do the assignments above produce copies or aliases (references)
        only? Which one would you prefer in this context?
    """
    
    """
    N:
      Below we are going to have two subplots, one each for
        plotting the real and imaginary parts of the FFT
        coefficients of the current signal.
    Q:
      Why is it advantageous to make use of the list of lists
        defined in the control flow statement below (range based
        for loop)? 
      Would an implementation in Octave be so compact? Would it
        be possible to code in Octave?
    """
    for splt in \
      [
        [ 211 , np.real(y) , 'Real Parts' , 'blue' ] ,
        [ 212 , np.imag(y) , 'Imag Parts' , 'red'  ]
        ]:
      """
      N:
        Below is the compact unpacking syntax, saves much
          effort.
      """
      splt_id, splt_signal, splt_ylabel, splt_plot_color \
        = splt
      
      """
      N:
        Below, according to a choice stored in "self.plot_type"
          for the instance, we command the plotting engine
          to depict either a stem or a continuous plot.
        Below is an example for the case where I regret not
          having the facility to make use of switch-case control
          flow statement available in other programming languages.
      Q:
        Why do I regret the absence of the stated feature in here,
          whereas we must have touched upon the possible 
          alternatives for switch-case?
      """
      ax = fig.add_subplot(splt_id)
      if   self.plot_type == 'stem':
        """
        N:
          The plotting features and management of attributes
            constitute a particularly powerful aspect of python.
        Q:
          Look up the other available methods for the instances
            of plotting ingredients, with examples as given below.
        """
        markerline, stemlines, baseline = \
          ax.stem( x, splt_signal, linefmt='grey', 
                   markerfmt='o', bottom=0., 
                   use_line_collection=True )
        markerline.set_markerfacecolor('red')
        markerline.set_markersize(20)
        markerline.set_mec('black')
        markerline.set_mew('2')
        baseline.set_c ('blue')
        baseline.set_lw(5.)
        """
        Q:
          Why do we need the for loop just below, while
            it was not necessary for the settings above?
        """
        for item in stemlines:
          item.set_lw(5.)
      elif self.plot_type == 'plot':
        ax.plot( x , splt_signal , 
                 color = splt_plot_color ,
                 linewidth = axis_plot_lwidth )
      else:
        pass
      
      """
      Q:
        Explain how we call a static member function
          with the necessary arguments and unpack the
          returned multiple data into separate variables,
          in just a single line of code as below.
      """
      x_val_low, x_val_high, y_val_low, y_val_high \
        = fft_coefs_manipulator.compute_plot_min_max(
            x, splt_signal, x_tol, y_tol)
    
      """
      Q:
        How do we set the limits/boundaries of the subplot?
      """
      ax.set_ylim( [ y_val_low , y_val_high ] )
      ax.set_xlim( [ x_val_low , x_val_high ] )
    
      """
      Q:
        How do we set the line widths for the bounding box
          of the frame encapsulating the actual plot?
      """
      for loc in ['top', 'right', 'bottom', 'left']:
        ax.spines[loc].set_linewidth(axis_border_lwidth)
    
      """
      Q:
        If for some reason I were not satisfied with
          the ticks and labels in a plot, would I be
          able to manage them myself? Does python provide
          me with the necessary features to accomplish this 
          one?
      """
      ax.tick_params(labelsize=ticks_labelsize)
    
      ax.xaxis.grid()
      ax.yaxis.grid()
    
      """
      Q:
        Play around with the "y = ..." keyword argument below
          and see what happens.
      """
      ax.set_title ( '%s (%s)' % (title_str, splt_ylabel) , 
                     fontsize = label_fontsize , y = 1.01 )
      ax.set_ylabel( splt_ylabel ,
                     fontsize = label_fontsize )
      
      """
      Q:
        If I chose to, would I also be able to store the handles
          of all of the axes generated in the individual iterations
          of this for loop as well?
        Why am I assigning "ax_last" in each iteration? Is there
          no other way of doing what I am trying to do (whatever
          it is)?
      """
      ax_last = ax
      del splt_id, splt_signal, splt_ylabel
      
    """
    N:
      We are out of the for loop responsible for generating
        the indicated subplots.
    Q:
      Tell me why I have the following statement making use of
        the "ax_last" reference.
    """
    ax_last.set_xlabel( 'Discrete Freq. Indices' ,
                        fontsize = label_fontsize )
    """
    Q:
      How do we optionally maximize a figure for it to assume
       or exploit the whole screen size in python?
    """
    if self.flag_plot_maximize:
      figManager = plt.get_current_fig_manager()
      figManager.window.showMaximized()
  
  def plot_time(self, title_str='Signal in Time Domain'):
    label_fontsize = 24
    ticks_labelsize= 24
    axis_border_lwidth = 3
    axis_plot_lwidth   = 4
    
    y_tol = 0.1
    x_tol = 0.005
    
    fig = plt.figure()
    rect = fig.patch
    rect.set_facecolor('white')
    
    """
    Q:
      We have only a single subplot in the figure generated
        in this member function. It seems weird to have the
        statement below. Is there any other alternative?
    """
    ax = fig.add_subplot(111)
    x  = self.indices_t
    y  = self.x_t
    
    if   self.plot_type == 'stem':
      markerline, stemlines, baseline = \
        ax.stem( x, y, linefmt='grey', markerfmt='o', bottom=0., 
                 use_line_collection=True )
      markerline.set_markerfacecolor('red')
      markerline.set_markersize(20)
      markerline.set_mec('black')
      markerline.set_mew('2')
      baseline.set_c ('blue')
      baseline.set_lw(5.)
      for item in stemlines:
        item.set_lw(5.)
    elif self.plot_type == 'plot':
      ax.plot( x , y , linewidth = axis_plot_lwidth )
    else:
      pass
    
    x_val_low, x_val_high, y_val_low, y_val_high \
      = fft_coefs_manipulator.compute_plot_min_max(
          x, y, x_tol, y_tol)
    
    ax.set_ylim( [ y_val_low , y_val_high ] )
    ax.set_xlim( [ x_val_low , x_val_high ] )
    
    for loc in ['top', 'right', 'bottom', 'left']:
      ax.spines[loc].set_linewidth(axis_border_lwidth)
    
    ax.tick_params(labelsize=ticks_labelsize)
    
    ax.xaxis.grid()
    ax.yaxis.grid()
    
    ax.set_title ( title_str , 
                   fontsize = label_fontsize , y = 1.01 )
    ax.set_xlabel( 'Discrete Time Indices' ,
                   fontsize = label_fontsize )
    ax.set_ylabel( 'Signal' ,
                   fontsize = label_fontsize )
    
    if self.flag_plot_maximize:
      figManager = plt.get_current_fig_manager()
      figManager.window.showMaximized()
    
  """
  NOTE: On how to permute columns of ndarrays, see the following URL:
    https://stackoverflow.com/questions/20265229/rearrange-columns-of-numpy-2d-array
  """
    
  def to_freq(self):
    self.x_f = np.fft.fft(self.x_t) / self.N
    """
    Q:
      Is there an alternative order of operations through to
        the discrete frequency representation of the signal?
      Explain the fftshift operation carried out below
        (correct for an odd number of samples).
    """
    permuted_col_indices \
      = range(self.K, self.N) \
      + range(0, self.K)
    """
    Q:
      What type does the "range" function return?
      Is the "+" above an overloaded one?
      Would the call above work correctly or even compile
        with the "numpy.arange()" function utilized instead of
        "range"?
    """
    #print permuted_col_indices
    idx = np.empty_like(permuted_col_indices)
    idx[permuted_col_indices] \
      = np.arange(len(permuted_col_indices))
    """
    Q:
      If the resulting array and the original one were not
        of the same number of elements, would the call below
        generate errors?
      Can the operation below be carried out in place? If so,
        what is the advantage?
    """
    self.x_f[:] = self.x_f[idx]
    
  def to_time(self):
    self.x_t = self.x_f * self.N
    """
    Q:
      Is there an alternative order of operations through to
        the discrete time representation of the signal?
      Explain the fftshiftback operation carried out
        below (correct for an odd number of samples).
    """
    permuted_col_indices \
      = range(1+self.K, self.N) \
      + range(0, 1+self.K)
    #print permuted_col_indices
    idx = np.empty_like(permuted_col_indices)
    idx[permuted_col_indices] \
      = np.arange(len(permuted_col_indices))
    self.x_t[:] = self.x_t[idx]
    self.x_t = np.fft.ifft(self.x_t)
    """
    Q:
      If the signal is real in discete time, and operations
        carried out do not modify this aspect, then why would we
        still need to obtain the real parts of the samples
        in the discrete time domain as done below?
    """
    if self.flag_real:
      self.x_t = np.real(self.x_t)
      