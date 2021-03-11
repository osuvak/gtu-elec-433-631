// Onder Suvak (C) 2021

#include <stdio.h>
#include <stdlib.h>

int
main (void)
{
  typedef unsigned int local_type;
  
  local_type * m_ptr
    = (local_type *) malloc( 1 * sizeof( local_type ) );
  local_type * c_ptr
    = (local_type *) calloc( 1 , sizeof( local_type ) );
  
  printf( "  %16u\n" , *m_ptr );
  printf( "  %16d\n" , *c_ptr );
    
  return 0;
}