// Onder Suvak (C) 2020

#include <tuple>
#include <iostream>
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

int
main (void)
{
  using namespace os_test::iterator_testers;
  using namespace common_typedefs;
  
  using namespace std;
  
  Container oa(67);
  
  cout 
    << "Object has " << setw(4) << oa.get_number() << " before."
    << endl;
  
  using local_tuple_type = std::tuple<Container &>;
    
  local_tuple_type my_tuple 
    = std::forward_as_tuple(oa);
  
  auto & obtained = std::get<0>(my_tuple);
  obtained.set_number(34);
  
  cout 
    << "Object has " << setw(4) << oa.get_number() << " afterwards."
    << endl;
  
  return 0;
}