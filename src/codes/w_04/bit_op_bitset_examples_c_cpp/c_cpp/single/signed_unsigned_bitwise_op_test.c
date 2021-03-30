// Onder Suvak (C) 2020

#include <stdio.h>

void
print_numbers
(
  const char *         id ,
  const int *          a ,
  const unsigned int * b
)
{
  printf("\n");
  printf("*** %s ***\n" , id);
  printf( "Signed Integer   :\n  0x%.8x\n" , *a );
  printf( "Unsigned Integer :\n  0x%.8x\n" , *b );
}

int
main ()
{
  int          a_s  = 0;
  unsigned int b_us = 0;
  
  printf( "Size of int :\n  %d\n" , 
          sizeof(a_s) );
  printf( "Size of unsigned int :\n  %d\n" , 
          sizeof(b_us) );
  
  print_numbers("Original Numbers", &a_s, &b_us);
  
  a_s -= 3;
  print_numbers("Decremented signed int by 3", &a_s, &b_us);
  
  b_us -= 2;
  print_numbers("Decremented unsigned int by 2", &a_s, &b_us);
  
  a_s >>= 1;
  b_us>>= 1;
  print_numbers("Shifted both right by 1 bit", &a_s, &b_us);
  
  return 0;
}