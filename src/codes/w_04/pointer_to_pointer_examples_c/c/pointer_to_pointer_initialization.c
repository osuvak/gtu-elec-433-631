// Onder Suvak (C) 2020

#include <stdio.h>
#include <stdlib.h>

typedef
  struct NumberContainer_
  { int number; }
  NumberContainer;

void
initialize_ptr_of_ptr
(
  NumberContainer ** container_ptr_ptr ,
  int                no_items
);

void
print_ptr
( 
  const NumberContainer * container_ptr, 
  int                     no_items 
);

int
main (void)
{
  const int NO_ITEMS = 10;
  NumberContainer **container_ptr_ptr
    = malloc( sizeof(NumberContainer *) );
  
  initialize_ptr_of_ptr
    ( container_ptr_ptr, NO_ITEMS);
  print_ptr
    (*container_ptr_ptr, NO_ITEMS);

  free(*container_ptr_ptr);
  free(container_ptr_ptr);
  
  return 0;
}

void
initialize_ptr_of_ptr
(
  NumberContainer ** container_ptr_ptr ,
  int                no_items
)
{
  int kk;
  *container_ptr_ptr 
    = malloc( 
        no_items *
        sizeof(NumberContainer) );
    
  NumberContainer * ptr_alias 
    = *container_ptr_ptr;
  for ( kk=0 ; kk<no_items ; ++kk )
    ptr_alias[kk].number = no_items - kk;
}

void
print_ptr
( 
  const NumberContainer * container_ptr, 
  int                     no_items 
)
{
  int kk;
  for ( kk=0 ; kk<no_items ; ++kk )
    printf( "Item with index %4d has %4d.\n" , 
            kk , container_ptr[kk].number );
}
