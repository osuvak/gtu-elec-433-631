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
 * Updates
 *   Commented through with interspersed questions on
 *     Thu Jun 25 13:50:18 AST 2020
 * */

#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cassert>
#include <chrono>
#include <random>
#include <cmath>
#include <vector>

#define NO_MC  100000

/*
 * Q:
 *   What is the advantage of having the opportunity
 *     to make use of namespaces or even nested namespaces?
 * */
namespace os_test {
  namespace elm_218_probability {
    
  class UniformlyDistributedRVGenerator
  {
  /*
   * Q:
   *   Do we need this "private:" indicator? Can we do without it?
   * */
  private:
    unsigned
      seed_; // seed for the random number generator
    std::vector< std::default_random_engine >
      v_generator_;    // vector of generators
  
    // distributions
    std::vector< std::uniform_real_distribution<double> > 
      v_dist_uniform_; // vector of indicated distributions
  
    /*
     * Q:
     *   What are the advantages and disadvantages to keeping
     *     the generator and the distribution in vectors as
     *     indicated above? As a hint, one advantage will 
     *     become clear in the constructor.
     * */
  
  public:
    UniformlyDistributedRVGenerator 
    () 
    {
      /*
       * Q:
       *   What is the "epoch" in this context?
       *   Is the seed thus set through the current time
       *     information a local or global one?
       *   What would be advantages to making use of a local
       *     seed value?
       *   Should the seed for a random number generator be set
       *     every time a sample obeying a certain distribution
       *     is created? Or is this a gruesome mistake? Is this
       *     how we do it in the current source code?
       * */
      seed_ 
        = std::chrono::high_resolution_clock::now()
            .time_since_epoch().count();
    
      /*
       * Q:
       *   What are the arguments to the "emplace_back(...)"
       *     member function of a vector? Do the number and
       *     types of the indicated input arguments differ
       *     for different template parameters for std::vector?
       *   "emplace_back(...)" makes use of a paradigm called
       *     perfect forwarding. What is this concept?
       *   Do the "emplace_back(...)" calls below involve
       *     object copying operations? If yes, is there an
       *     extra call we may utilize to prevent copy operations
       *     during intended in-place constructions in a vector?
       * */
      v_generator_.clear();
      v_generator_.emplace_back( seed_ );
    
      // initialize commonly used distributions
      v_dist_uniform_.emplace_back( 0.0 , 1.0 );
    }
    
    /*
     * Q:
     *   What does the following syntax mean for the destructor?
     *     Are there any other reserved keywords that could be
     *     used instead of "default"? Why is "default" the one
     *     that makes sense in here?
     * */
    ~UniformlyDistributedRVGenerator() 
      = default;
      
    double
    rand
    ()
    {
      /*
       * Q:
       *   What does the "front()" member function return for
       *     std::vector?
       *   There should also be a "back()" member function as
       *     well. What does that one return?
       * */
      return
        v_dist_uniform_.front()( v_generator_.front() );
    }
    
    // rand
    std::vector<double>
    rand_vector
    (
      /*
       * Q:
       *   Why do we declare these input arguments to
       *     be const?
       *   How do we assign default values for input
       *     arguments? Could we list another input
       *     argument below as the last one, and that
       *     without a default value for it?
       * */
      const unsigned int howMany ,
      const double       val_a = 0.0 ,
      const double       val_b = 1.0
    )
    {
      /*
       * Q:
       *   What does "assert" do in here?
       *   This does not seem to be a good example of
       *     the C++ way of checking for errors and 
       *     reporting them. What would you suggest
       *     instead?
       * */
      assert( val_b > val_a );
      /*
       * Q:
       *   Why should we avoid making use of unscoped
       *     namespace usage calls? Below is a scoped
       *     call, so no problem.
       * */
      using namespace std;
    
      /*
       * Q:
       *   What is constructor overloading in C++?
       *   What does the following constructor overload
       *     for std::vector do? Why are we making use of
       *     it in this context?
       *   Are there any other constructor overloads
       *     for std::vector, which possibly would not
       *     make sense in here?
       * */
      vector<double> current( howMany , 0.0 );
    
      /*
       * Q:
       *   How does the range-based for below work?
       *   Why do we work with references denoted by "vv"
       *     below?
       *   Does the for loop below consist of iterations
       *     that are embarrassingly parallelizable?
       *   If you needed to parallelize the iterations in the 
       *     loop below, then would the utilization of the
       *     range-based for be still convenient for
       *     some parallelization methods?
       *     
       * */
      for ( auto & vv : current )
        vv = val_a + ( val_b - val_a ) * rand();
    
      /*
       * Q:
       *   We are returning over here a variable
       *     constructed within the scope of the
       *     member function. Copying such an entity
       *     into a variable in the scope of the caller
       *     could be very costly,
       *     since "howMany" could be really big.
       *     However, if we are careful with the syntax
       *     for the caller and the callee, as we are
       *     in here indeed, then an idiom called
       *     "Copy Elision" is implicitly invoked.
       *     Report what this idiom is about.
       *   Why is returning a reference to "current"
       *     out of the question in here?
       * */
      return current;
    }
  };
  
  double
  sum_of_vector_of_doubles
  (
    /*
     * Q:
     *   How do we interpret or simply read the input
     *     argument declaration below?
     *   Is there a particular reason for making use of
     *     the constant reference type? Why not the plain
     *     "std::vector<double>" type?
     * */
    const std::vector<double> & vec
  )
  {
    double sum = 0.;
    /*
     * Q:
     *   Could we have "for ( auto & item : ... )" below
     *     as well?
     * */
    for ( auto item : vec )
      sum += item;
    return sum;
  }
    
} } // namespace

double
compute_probability ();

int
main (void)
{
  double prob = compute_probability ();
  
  printf( "Probability of Waiting for more than 10 min:\n" );
  printf( "  %.6f\n" , prob );
  
  return 0;
}

double
compute_probability ()
{
  using namespace std;
  using namespace os_test::elm_218_probability;
  
  /*
   * Q:
   *   What is a type alias in C++? What would be the 
   *     advantages to making use of it?
   *   Is there any other syntax for the statement below?
   * */
  using vector_type
    = std::vector<double>;
  
  /*
   * Q:
   *   The constructor for the indicated class does not
   *     accept any input arguments. Then, the variable
   *     declaration below could also be stated as
   *     "UniformlyDistributedRVGenerator rv_gen();"
   *     with the parentheses "()". Am I right? Is there
   *     something wrong with the suggested call?
   * */
  UniformlyDistributedRVGenerator rv_gen;
  
  double lam = 1. / 10;
  double time_to_wait 
    = 10.;
  double total_min_in_hour
    = 60.;
    
  /*
   * Q:
   *   How does automatic type deduction work in C++?
   *     Does it save the day for us in cases similar
   *     to the declaration below?
   * */
  auto arrival_times
    = rv_gen.rand_vector(NO_MC, 0., 60.);
  vector_type result(NO_MC, 0.);
  
  /*
   * NOTE:
   *   This is the actual loop fo the Monte Carlo simulation.
   * Q:
   *   Would the syntax "for ( int kk=0 ; ... )" compile in C?
   * */
  for ( int kk=0 ; kk<NO_MC ; ++kk )
  {
    if ( arrival_times[kk] > total_min_in_hour - time_to_wait )
      continue;
    else
    {
      /*
       * Q:
       *   Is "bool" a type alias or a distinct type in C++?
       * */
      bool flag_valid_sample = false;
      double sample = -99.;
      
      while ( ! flag_valid_sample )
      {
        double u 
          = rv_gen.rand();
        double x
          = - 1. / lam * log(1. - u);
        if ( arrival_times[kk] + x < total_min_in_hour )
        {
          flag_valid_sample = true;
          sample = x;
        }
      } // while
      
      if ( sample > time_to_wait )
        result[kk] = 1.;
    } // else
  } // for
  
  double prob
    = sum_of_vector_of_doubles(result)
      / ((double) NO_MC);
      
  return prob;
}