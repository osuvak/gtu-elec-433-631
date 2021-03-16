#!/usr/bin/perl

# Onder Suvak (C) 2021

use strict;
use warnings;

my $fname = 'my_text_file.txt';

# NOTE: Alternatives for the 'open' function calls.
open ( FILE , "<$fname" );
# open ( FILE , "<" . "$fname" );
# open ( FILE , "<" . $fname );
# open ( FILE , '<' . $fname );

# NOTE : The following will not work.
# open ( FILE , '<$fname' ) or die "Cannot find the text file.";

my $flag_use_foreach = 0;

my @lines = <FILE>;
close( FILE );

# NOTE : New line characters are removed through
#        nested split and join utilization.
my @lines_newline_removed
  = split( "\n" , join( '' , @lines ) );
print
  "\nFile Content (through \@lines_newline_removed) :\n" ,
  join( "\n" , @lines_newline_removed );

# print
#   "\n" ,
#   "File Content :" , "\n" ,
#   join( '' , @lines );
print
  "\nFile Content :\n" ,
  join( '' , @lines );

print
  "\n" ,
  "Content in the lines :" , "\n";
if ($flag_use_foreach)
{ # using range based foreach
  my $cnt = 0;
  foreach my $ll (@lines)
  {
    chomp($ll);
    print 
      "Line " , sprintf( '%3d' , ++$cnt ) , "\n" ,
      $ll , "\n";
  }
}
else
{ # using the usual for loop syntax
  for ( my $kk = 0 ; $kk < 1 + $#lines ; ++$kk )
  {
    chomp( $lines[$kk] );
    print 
      "Line " , sprintf( '%3d' , 1 + $kk ) , "\n" ,
      $lines[$kk] , "\n";
  }
}

print
  "\n" ,
  "File Content :" , "\n" ,
  join( '' , @lines );