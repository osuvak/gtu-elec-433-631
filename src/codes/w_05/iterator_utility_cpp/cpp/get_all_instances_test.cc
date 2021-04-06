// Onder Suvak (C) 2020

#include <cmath>
#include <algorithm>
#include <vector>
#include <tuple>
#include <iostream>
#include <string>
#include <iomanip>

#include "stuff_utilities.hh"

namespace common_typedefs
{
  using namespace os_test::iterator_testers;
  
  using local_type   
    = std::shared_ptr<Container>;
  using func_ptr_type
    = bool(*)(local_type &);
  using fhandle_type 
    = std::function< std::remove_pointer<func_ptr_type>::type >;
}

void
test_multiple ();

int
main(void)
{
  test_multiple ();
  
  return 0;
}

void
test_multiple ()
{
  std::cout << std::endl 
    << "***Get All Instances - Multiple Lambda Expressions Test***" << std::endl;
  
  using namespace os_test::iterator_testers;
  using namespace common_typedefs;
  
  using utility_tuple_type 
    = std::tuple<int, std::string, fhandle_type>;
  using vector_of_tuples_type
    = std::vector<utility_tuple_type>;
  
  const int 
    VAL_MIN = 5, 
    VAL_MAX = 16;
  
  const int numbers[2] = { 160 , 11 };
  vector_of_tuples_type vec_tuples;
  
  auto vec_in 
    = get_vector_of_containers_in_range(VAL_MIN, VAL_MAX);
  using local_iterator_type 
    = decltype(vec_in.begin());
  using vec_local_iterator_type 
    = std::vector<local_iterator_type>;
  using vec_vec_local_iterator_type 
    = std::vector<vec_local_iterator_type>;
  vec_vec_local_iterator_type
    vec_results(2, vec_local_iterator_type(0));
  
  int tmp;
    
  tmp = numbers[0];
  vec_tuples.push_back(
    std::make_tuple(
      tmp ,
      "Content of Containers with a Number whose Square is Less Than" ,
      [tmp](local_type & item)->bool 
        { return std::pow(item->get_number(), 2.) < tmp; }
    )
  );
  
  tmp = numbers[1];
  vec_tuples.push_back(
    std::make_tuple(
      tmp ,
      "Content of Containers with a Number that is More Than" ,
      [tmp](local_type & item)->bool 
        { return item->get_number() > tmp; }
    )
  );
  
  tmp = 0;
  for (auto & item : vec_tuples)
  {
    auto number_current = std::get<0>(item);
    auto string_current = std::get<1>(item);
    auto & fh = std::get<2>(item);
    
    auto current_iterator = vec_in.begin();
    while( current_iterator != vec_in.end() )
    {
      auto found_iterator = 
        std::find_if( current_iterator, vec_in.end(), 
                      fh );
      if ( found_iterator != vec_in.end() )
      {
        vec_results[tmp].push_back(found_iterator);
        ++found_iterator;
        current_iterator = found_iterator;
      }
      else
        break;
    }
    
    std::cout 
      << string_current
      << " " << number_current << ":"
      << std::endl
      << "  ";
    for (auto & content : vec_results[tmp])
      std::cout << " " << std::setw(4) << (*content)->get_number();
    std::cout << std::endl;
      
    ++tmp;
  }
}