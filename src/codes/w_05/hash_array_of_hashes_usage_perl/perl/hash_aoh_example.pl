#!/usr/bin/perl
# /*
#  * This file is part of the "dev-in-place" repository located at:
#  * https://github.com/osuvak/dev-in-place
#  * 
#  * Copyright (C) 2020  Onder Suvak
#  * 
#  * For licensing information check the above url.
#  * Please do not remove this header.
#  * */

# This source code file was
#   Commented through (with interspersed questions) on
#     Fri Apr 24 17:27:31 AST 2020

use strict;
use warnings;

# hash initialization
# Questions:
#   Could I have an empty hash as well at first?
#     How would I add (key, value) pairs then?
#   How do we iterate through a hash with the defined keys?
my %tmp = 
  (
    'name'          => '' ,
    'year_of_entry' => 0
  );

# Questions: 
#   What happens if you omit the "{}" delimiters below?
#     See the "push" commands used twice below.

# array of hashes
# Questions: 
#   Do we know for sure that @aoh is destined to be an array
#     at this point? What a stupid question! Then, let me try
#     this one: Do we know for sure that @aoh is destined to be 
#     an array at this point?
#   In perl what can an array hold? Is it allowed to contain
#     objects of dissimilar types for example? Difficult question!
my @aoh = ();

# See here.
# The calls below ( with "{...}" and "\..." ) are both
#   syntactically correct. However, a call with just "..."
#   (with ... replaced by %tmp in each of the previous calls)
#   would produce errors. And only the usage with "{...}" is
#   the correct one.
# Questions:
#   Why is this so?
push @aoh , { %tmp };
# push @aoh , \%tmp;

# This is how one gains access to the items stored in @aoh
#   Watch the syntax and operators. Perl is heavily loaded
#   with such antiquities, it takes time to get used to them.
# Questions:
#   If "$aoh[-1]" were just a hash, the syntax below would
#     generate errors. Then what is "$aoh[-1]" indeed?
#   Also, how do we gain access to the value associated with a
#     key, with the particular (key, value) pair stored in a hash?
$aoh[-1]->{name} 
  = 'Onder';
$aoh[-1]->{year_of_entry} 
  = 2014;

# And here!
push @aoh , { %tmp };
# push @aoh , \%tmp;
$aoh[-1]->{name} 
  = 'Emre';
$aoh[-1]->{year_of_entry} 
  = 2015;
  
# report
print "*** REPORT ***\n";
# Questions:
#   This is just one way of iterating through an array.
#     What are others?
#   Will the variable "$item" continue to be defined in the
#     workspace after the scope of foreach comes to an end?
#     What if we had another variable "$item" defined before
#     this foreach control flow comes about?
#   It is possible to use just a "for" based control flow below,
#     without "$item" being defined. However, I seem to need
#     "$item" in the body of the flow. I am confused, this
#     appears to be a contradiction. Enlighten me!
foreach my $item (@aoh)
{
  print "  Next Item in AoH\n";
  # Questions:
  #   I suspect that the print statement below can be
  #     written with a single string accommodating the
  #     variables (e.g., "$item->{name}") inside it as
  #     well. Am I right?
  #   If I do not delve into the execution of the practice
  #     described above, which may not be alogether advisable
  #     (why not?), I suspect also that the separators ","
  #     below can be replaced by ".". Am I right?
  print 
    "    " , "Name : " , $item->{name} , "\n" ,
    "    " , "Year : " , $item->{year_of_entry} , "\n" ;
}