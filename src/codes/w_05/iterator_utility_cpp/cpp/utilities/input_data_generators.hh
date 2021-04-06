// Onder Suvak (C) 2020

#pragma once

#include<vector>
#include<memory>

namespace os_test {
  namespace iterator_testers {
  
  class Container
  {
  private:
    int number_;
    
  public:
    Container
    (
      int number = 0
    )
    :
    number_(number)
    {}
    
    ~Container () = default;
    
    int
    get_number
    ()
    {
      return number_;
    }
    
    Container &
    set_number
    (int number)
    {
      number_ = number;
      return *this;
    }
  };
  
  std::vector< std::shared_ptr<Container> >
  get_vector_of_containers_in_range
  (int val_min, int val_max);
  
} } // namespace
