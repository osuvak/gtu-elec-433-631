// Onder Suvak (C) 2021

#pragma once

namespace os_test {
  
class Incrementor
{
private:
  int number_;
  
public:
  Incrementor
  (
    int  number
  )
  :
  number_(number)
  {}
  
  ~Incrementor() = default;
  
  Incrementor &
  set_number
  (
    int  number
  )
  {
    number_ = number;
    return *this;
  }
  
  int
  compute
  (
    int arg_in
  )
  {
    return arg_in + number_;
  }
  
  static
  int
  s_compute
  (
    int    arg_in, 
    void * custom_instance_ptr
  )
  {
    auto * obj_ptr
      = static_cast<Incrementor *>(custom_instance_ptr);
    return obj_ptr->compute(arg_in);
  }
};

} // namespace