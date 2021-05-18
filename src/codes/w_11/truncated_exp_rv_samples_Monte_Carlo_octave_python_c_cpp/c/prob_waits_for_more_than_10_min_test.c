/*
 * This file is part of the "dev-in-place" repository located at:
 * https://github.com/osuvak/dev-in-place
 * 
 * Copyright (C) 2020  Onder Suvak
 * 
 * For licensing information check the above url.
 * Please do not remove this header.
 * */

/*
 * Updates:
 *   Commented through with questions on
 *     Thu Jun 25 12:38:45 AST 2020
 * */

#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
#include <stdbool.h>
#include <math.h>

/*
 * Q:
 *   Is there any reason to refrain from using a "define"
 *     statement as below in C or C++?
 * */
#define NO_MC  100000

double
get_fp_random_standard_uniformly_distributed_single
()
{
  /*
   * Q:
   *   What does the call to "rand()" return below? And why
   *     do we divide it by "RAND_MAX"?
   *   What would happen if we had not resorted to C-style
   *     type-casting through "(double) ..."?
   * */
  return rand() / ((double) RAND_MAX);
}

void
get_fp_random_uniformly_distributed
(
  /*
   * Q:
   *   Are they any benefits to making use of an input
   *     argument with type "double **"?
   * */
  double ** array_ptr_ptr ,
  int       no_samples ,
  double    range_min ,
  double    range_max
)
{
  /*
   * Q:
   *   What is the difference between "calloc(...)"
   *     and "malloc(...)" for memory allocation? Except
   *     possibly the syntactic one, involving the number
   *     and types of input arguments? Will we explicitly
   *     make use of an advantage (perhaps an extra operation)
   *     that "calloc(...)" provides us?
   * */
  *array_ptr_ptr
    = calloc( no_samples , sizeof(double) );
  /*
   * Q:
   *   Why do we make use of the alias below? Is it indispensible?
   * */
  double * ptr_alias
    = *array_ptr_ptr;
    
  /*
   * Q:
   *   Would the "for (int kk=0 ; ...)" syntax work in C?
   *   Does the assignment "ptr_alias[kk] = ..." point out
   *     the advantage of using the alias?
   *   Why would one prefer in the for loop below 
   *    "for ( ... ; ++k )" instead of "for ( ... ; k++ )"?
   **/  
  int kk;
  for ( kk=0 ; kk<no_samples ; ++kk )
    ptr_alias[kk] 
      = get_fp_random_standard_uniformly_distributed_single()
        * ( range_max - range_min )
        + range_min;
  /*
   * Q:
   *   What is the reason for the scale and shift operations
   *     above, for each of the samples returned by the function
   *     "get_fp_random_standard_uniformly_distributed_single()"?
   * */
}

/*
 * Q:
 *   How do we interpret or simply "read" the declaration
 *     "const double * array_ptr"?
 *   Is there a particular reason the type "const double *"
 *     is preferable to "double *" in the signature below?
 * */
double
sum_of_array_of_doubles
(
  const double * array_ptr ,
  int            no_entries
)
{
  double sum = 0.;
  int    kk;
  for ( kk=0 ; kk<no_entries ; ++kk )
    sum += array_ptr[kk];
  return sum;
}

/*
 * Q:
 *   Do we need this prototype? Can we do without it?
 * */
double
compute_probability ();

int
main (void)
{
  double prob = compute_probability ();
  
  printf( "Probability of Waiting for more than 10 min:\n" );
  printf( "  %.6f\n" , prob );
  /*
   * Q:
   *   Why would "%8.6f" and similar ones to that with also 
   *     almost any integer above "8" make sense for the 
   *     formatting call above, but not "%7.6f" and any 
   *     integer below "7"?
   * */
  
  return 0;
}

double
compute_probability ()
{
  /*
   * Q:
   *   How do the following two lines of code set the seed
   *     for the random number generator, using the current
   *     time information?
   *   Is the typecast "((unsigned) ...)" necessary below?
   * */
  time_t t;
  srand((unsigned) time(&t));
  
  double lam = 1. / 10;
  double time_to_wait 
    = 10.;
  double total_min_in_hour
    = 60.;
    
  /*
   * Q:
   *   If, in the function call below, what we are sending
   *     as the 1st argument is effectively of type "double **",
   *     then why not declare a variable through
   *     "double ** arrival_times_ptr_ptr;" and send this one
   *     instead as the indicated argument? Would the code
   *     compile? Would the code work?
   * */
  double * arrival_times_ptr;
  get_fp_random_uniformly_distributed
    ( &arrival_times_ptr , NO_MC , 0. , 60. );
  
  /*
   * Q:
   *   Why do we particularly prefer "calloc(...)" instead
   *     of "malloc(...)" in the call below? As a note,
   *     the array pointed to by "result_ptr" is designed to
   *     hold "0." or "1." in its entries.
   * */
  double * result_ptr
    = calloc( NO_MC , sizeof(double) );
  
  /*
   * NOTE:
   *   This is the actual loop for Monte Carlo simulation.
   * Q:
   *   Is this a so-called embarrassingly parallelizable
   *     loop? If yes, look up methods to parallelize the
   *     iterations in the loop.
   * */
  int kk;
  for ( kk=0 ; kk<NO_MC ; ++kk )
  {
    if ( arrival_times_ptr[kk] > total_min_in_hour - time_to_wait )
      continue;
    else
    {
      /*
       * Q:
       *   Is "bool" only a type alias or a distinct type in C?
       *   If the former is the correct way to describe "bool",
       *     then how are "false" and "true" defined in C?
       * */
      bool flag_valid_sample = false;
      /*
       * Q:
       *   Will "sample" ever continue to maintain the indicated
       *     value set through initialization after we manage to
       *     break out of the while loop? 
       * */
      double sample = -99.;
      
      while ( ! flag_valid_sample )
      {
        double u 
          = get_fp_random_standard_uniformly_distributed_single();
        double x
          = - 1. / lam * log(1. - u);
        if ( arrival_times_ptr[kk] + x < total_min_in_hour )
        {
          flag_valid_sample = true;
          sample = x;
        }
      } // while
      
      if ( sample > time_to_wait )
        result_ptr[kk] = 1.;
      /*
       * Q:
       *   Why is there not an else statement above
       *     setting the indicated entry to 0.? Why
       *     can we do without it?
       * */
    } // else
  } // for
    
  double prob
    = sum_of_array_of_doubles(result_ptr, NO_MC) 
      / ((double) NO_MC);
  /*
   * Q:
   *   Do we actually need the typecast "((double) NO_MC)"
   *     above? Can we do without it?
   * */
    
  free(arrival_times_ptr);
  free(result_ptr);
  /*
   * Q:
   *   What would happen without the "free(...)" statements
   *     above?
   * */
  
  return prob;
}
