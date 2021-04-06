// Onder Suvak (C) 2020

#include <cmath>
#include <algorithm>
#include <vector>
#include <tuple>
#include <iostream>
#include <string>
#include <iomanip>

#include "stuff_utilities.hh"
#include "stuff_stackoverflow.hh"

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

int
main(void)
{
  std::cout << std::endl 
    << "***std::transform with back_emplacer test***" << std::endl;
  
  using namespace os_test::iterator_testers;
  using namespace common_typedefs;
  
  using namespace std;
  
  const int 
    VAL_MIN = 5, 
    VAL_MAX = 16;
  
  auto vec_in 
    = get_vector_of_containers_in_range(VAL_MIN, VAL_MAX);
  std::vector<int> 
    vec_out;
    
//   std::vector<local_type>
  decltype(vec_in)
    vec_out_desired;
  
  std::transform(
    vec_in.begin(), vec_in.end(), std::back_inserter(vec_out),
    [](local_type & obj_ptr)->int
      { return std::pow(obj_ptr->get_number(), 2.); }
  );
  
  std::transform(  
    vec_out.begin(), vec_out.end(),
    stack_overflow_stuff::back_emplacer(vec_out_desired),
    [](int number)
      { return std::make_shared<Container>(number); }
  );
  
  using utility_tuple_type 
    = std::tuple<std::string, const decltype(vec_in) &>;
  using vector_of_tuples_type
    = std::vector<utility_tuple_type>;
  
  vector_of_tuples_type vec_tuples;
  vec_tuples.push_back(
    std::forward_as_tuple(
      "Original Numbers" ,
      vec_in
    )
  );
  vec_tuples.push_back(
    std::forward_as_tuple(
      "Original Numbers Squared" ,
      vec_out_desired
    )
  );
  
  for ( auto & item : vec_tuples )
  {
    auto string_current 
      = std::get<0>(item);
    const 
    auto & vec_current
      = std::get<1>(item);
    
    std::cout 
      << string_current << ":"
      << std::endl
      << "  ";
    for (const auto & content : vec_current)
      std::cout << " " << std::setw(4) << content->get_number();
    std::cout << std::endl;
  }
  
  return 0;
}
