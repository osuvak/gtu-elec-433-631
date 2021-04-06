// Onder Suvak (C) 2020

#include "utilities/input_data_generators.hh"

namespace os_test {
  namespace iterator_testers {
    
  std::vector< std::shared_ptr<Container> >
  get_vector_of_containers_in_range
  (int val_min, int val_max)
  {
    using local_type = 
      std::vector< std::shared_ptr<Container> >;
      
    local_type vec;
    for ( int kk=val_min ; kk <= val_max ; ++kk )
      vec.push_back( std::make_shared<Container>(kk) );
    
    return vec;
  }
    
} } // namespace
