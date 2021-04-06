#!/usr/bin/python

#Onder Suvak (C) 2021

import copy as cp

def print_aoh(aoh):
  print "*** REPORT ***\n"
  for item in aoh:
    print "  Next Item in AoH"
    print \
    "   " , "Name :" , item['name'] , "\n" , \
    "   " , "Year :" , item['year_of_entry']
  print

tmp = { 
  'name' : '' , 
  'year_of_entry' : 0 }

aoh = list()
#aoh = []

aoh.append( cp.copy(tmp) )
aoh[-1]['name']          = 'Onder'
aoh[-1]['year_of_entry'] = 2014

aoh.append( cp.copy(tmp) )
aoh[-1]['name']          = 'Emre'
aoh[-1]['year_of_entry'] = 2015

print_aoh(aoh)