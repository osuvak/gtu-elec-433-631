// Onder Suvak (C) 2020

#include <cmath>
#include <algorithm>
#include <vector>
#include <tuple>
#include <iostream>
#include <string>

#include "stuff_utilities.hh"

namespace common_typedefs
{
  using namespace os_test::iterator_testers;
  
  using local_type   
    = std::shared_ptr<Container>;
  using func_ptr_type
    = bool(*)(local_type &);
  using fhandle_type 
//     = std::function<bool(local_type &)>;
    = std::function< std::remove_pointer<func_ptr_type>::type >;
}

void
test_single ();
void
test_multiple ();

int
main(void)
{
  test_single();
  test_multiple ();
  
  return 0;
}

void
test_single ()
{
  std::cout << std::endl 
    << "***count_if - Single Lambda Expression Test***" << std::endl;
  
  using namespace os_test::iterator_testers;
  using namespace common_typedefs;
  
  const int 
    VAL_MIN = 5, 
    VAL_MAX = 16;
    
  const int
    VAL_CHECK = 160;
  
  auto vec_in 
    = get_vector_of_containers_in_range(VAL_MIN, VAL_MAX);
  
  auto fh_square_more_than
    = [VAL_CHECK](local_type & item)->bool 
      { return std::pow(item->get_number(), 2.) > VAL_CHECK; };
  
  int count = 
    std::count_if( vec_in.begin(), vec_in.end(), 
                   fh_square_more_than );
  
  std::cout 
    << "Number of Containers with a Number whose Square is More Than "
    << VAL_CHECK << ":"
    << std::endl
    << "  "
    << count
    << std::endl;
}

void
test_multiple ()
{
  std::cout << std::endl 
    << "***count_if - Multiple Lambda Expressions Test***" << std::endl;
  
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
  
  int tmp;
    
  tmp = numbers[0];
  vec_tuples.push_back(
    std::make_tuple(
      tmp ,
      "Number of Containers with a Number whose Square is Less Than" ,
      [tmp](local_type & item)->bool 
        { return std::pow(item->get_number(), 2.) < tmp; }
    )
  );
  
  tmp = numbers[1];
  vec_tuples.push_back(
    std::make_tuple(
      tmp ,
      "Number of Containers with a Number that is More Than" ,
      [tmp](local_type & item)->bool 
        { return item->get_number() > tmp; }
    )
  );
  
  for (auto & item : vec_tuples)
  {
    auto number_current = std::get<0>(item);
    auto string_current = std::get<1>(item);
    auto & fh = std::get<2>(item);
    
    int count = 
      std::count_if( vec_in.begin(), vec_in.end(), 
                     fh );
    
    std::cout 
      << string_current
      << " " << number_current << ":"
      << std::endl
      << "  "
      << count
      << std::endl;
  }
}