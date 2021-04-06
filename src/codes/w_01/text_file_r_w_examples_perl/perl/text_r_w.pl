#!/usr/bin/perl
# Onder Suvak (C) 2020

use strict;
use warnings;

my $dname = 'content';
my $fname = 'file.txt';
my @numbers = (0 .. 9);

system("mkdir -p $dname");

open ( FILE , ">$dname/$fname" );
foreach my $item (@numbers)
{
  print FILE "$item\n";
}
close( FILE );

open ( FILE , "<$dname/$fname" );
my @content = <FILE>;
close( FILE );

@content = split("\n", join('', @content));
if ( $content[-1] eq '' ) { pop @content; }

print 
  "File \"$fname\" contents:" , "\n  " ,
  join( "  " , @content ) , "\n";