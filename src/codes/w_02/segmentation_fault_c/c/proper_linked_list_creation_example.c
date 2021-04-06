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
  // Try the following numbers for SZ
  const int SZ 
//     = 1;
//     = 2;
//     = 3;
    = 10;
  
  Container 
    *tmp_ptr , 
    *first_ptr = NULL , 
    *previous_ptr;
  int kk;

  // I will not make use of the array of pointers below.
//   Container *c_ptr_array[SZ];

  // ***allocate and assign numbers***
  if (SZ < 1)
    return 0;
  
  // allocate the first one
  first_ptr = malloc( sizeof(Container) );
  first_ptr->number = 0;
  first_ptr->next   = NULL;
  
  previous_ptr = first_ptr;
  
  // allocate the others
  for ( kk = 1 ; kk < SZ ; ++kk )
  {
    tmp_ptr = malloc( sizeof(Container) );
    tmp_ptr->number = kk;
    tmp_ptr->next   = NULL;
    
    previous_ptr->next = tmp_ptr;
    previous_ptr = previous_ptr->next;
  }
  
  // ***report***
  /* NOTE:
   *   Indeed this is not how a linked list should be traversed.
   *   Should be coded without making use of "kk".
   * 
   * WARNING:
   *    This implementation does not report when (SZ == 1) checks.
   */ 
  
  // one of the choices made below should create a segfault
  const int LAST_INDEX
//     = SZ;
    = SZ-1;
    
  // choose how the linked list is traversed, 
  //   there is only one method implemented for now.
  bool flag_traverse_through_links 
//     = false;
    = true;
  
  if ( flag_traverse_through_links )
  {
    tmp_ptr = first_ptr;
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
    {}
  }
  
  printf( "\nHERE without segfault!\n" );
  
  // ***deallocate*** (more tricky, cannot use c_ptr_array!)
  /* NOTE: 
   *   The deallocation scheme below could be made more
   *   neat and compact.    
   */
  
  printf("\n");
  if (first_ptr == NULL)
    ;
  else if (first_ptr->next == NULL)
  {
    printf( 
      "Freeing the container with number %3d.\n" , 
      first_ptr->number
    );
    free(first_ptr);
    first_ptr = NULL;
  }
  else
  {
    previous_ptr = first_ptr;
    tmp_ptr      = first_ptr->next;
    
    // either of the while conditions should work
//     while ( tmp_ptr != NULL )
    while ( tmp_ptr )
    {
      printf( 
        "Freeing the container with number %3d.\n" , 
        previous_ptr->number
      );
      free(previous_ptr);
      previous_ptr = tmp_ptr;
      tmp_ptr = tmp_ptr->next;
    }
    if (previous_ptr)
    {
      printf( 
        "Freeing the container with number %3d.\n" , 
        previous_ptr->number
      );
      free(previous_ptr);
    }
    
    first_ptr = NULL;
  }
  
  printf( "\nDeallocation done.\n" );
  
  return 0;
}