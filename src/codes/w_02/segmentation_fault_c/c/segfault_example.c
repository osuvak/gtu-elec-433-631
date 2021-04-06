// Onder Suvak (C) 2020

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef
  struct Container_
  {
    int                 number;
    struct Container_ * next;
  }Container;


int
main(void)
{
  const int SZ = 10;
  Container *c_ptr_array[SZ];
  Container *tmp_ptr;
  int kk;
  
  // Is instantiation of ll as below allowed in C?
  // What about C++?
//   for ( int ll=0 ; kk < SZ ; ++ll )
//     ;
  
  // ***allocate and assign numbers***
  for ( kk = 0 ; kk < SZ ; ++kk )
  {
    c_ptr_array[kk] = malloc( sizeof(Container) );
    c_ptr_array[kk]->number = kk;
  }
  
  // ***set next for each***
  for ( kk = 0 ; kk < SZ-1 ; ++kk )
    c_ptr_array[kk]->next = c_ptr_array[kk+1];
  c_ptr_array[SZ-1]->next = NULL;
    
  // ***report***
  
  // one of the choices made below should create a segfault
  const int LAST_INDEX
//     = SZ;
    = SZ-1;
    
  // choose how the linked list is traversed, either works.
  bool flag_traverse_through_links 
//     = false;
    = true;
  
  if ( flag_traverse_through_links )
  {
    tmp_ptr = c_ptr_array[0];
  }
  printf( "\n" );
  for ( kk = 0 ; kk < LAST_INDEX ; ++kk )
  {
    if (flag_traverse_through_links)
    {
      printf( "I have %3d and the next one has %3d.\n" ,
              tmp_ptr->number ,
              tmp_ptr->next->number
      );
      tmp_ptr = tmp_ptr->next;
    }
    else
    {
      printf( "I have %3d and the next one has %3d.\n" ,
              c_ptr_array[kk]->number ,
              c_ptr_array[kk]->next->number
      );
    }
  }
  
  printf( "\nHERE without segfault!\n" );
  
  // ***deallocate***

  printf("\n");
  // Can I do without the {} for the for loop below?
  for ( kk = 0 ; kk < SZ ; ++kk )
  {
    printf( 
      "Freeing the container with number %3d.\n" , 
      c_ptr_array[kk]->number
    );
    free( c_ptr_array[kk] );
  }
  printf( "\nDeallocation done.\n" );
  
  return 0;
}