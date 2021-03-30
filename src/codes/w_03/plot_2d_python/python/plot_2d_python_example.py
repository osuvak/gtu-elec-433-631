#!/usr/bin/python

#Onder Suvak (C) 2021

import matplotlib
matplotlib.use("Qt4Agg")
import matplotlib.pyplot as plt

import numpy as np

N  = 101
f0 = 1.e3
no_periods = 5

T = 1 / f0
t = np.linspace(
    0. , no_periods * T , no_periods * N + 1 )

x = np.array( ( np.cos( 2 * np.pi * f0 * t ) , 
                np.sin( 2 * np.pi * f0 * t ) ) )
x = np.transpose(x)
print t.shape
print x.shape

plots_lwidth   = 4.
label_fontsize = 24

fig = plt.figure()
rect = fig.patch
rect.set_facecolor('white')

ax = fig.add_subplot(111)
ph = ax
#ph = plt

phandle = ph.plot( 
  t , x , linewidth = plots_lwidth )

ax.set_title ( 
  '%d Periods of Sine/Cosine' % no_periods , 
  fontsize = label_fontsize , 
  y = 1.01 )
ax.set_ylabel( 'Signal' , fontsize = label_fontsize )
ax.set_xlabel( 't (sec)', fontsize = label_fontsize )

figManager = plt.get_current_fig_manager()
figManager.window.showMaximized()

plt.show()
