// Onder Suvak (C) 2021

#include "c_library.h"
#include "callbacks.h"

#include <iostream>
#include <iomanip>
#include <memory>

namespace os_test {
  
namespace actual_tests {
  void
  callback_in_cpp_test();
  
} // namespace
} // namespace

int
main (void)
{
  using namespace os_test::actual_tests;
  callback_in_cpp_test();
  return 0;
}

namespace os_test {
namespace actual_tests {
  
void
callback_in_cpp_test()
{
  using namespace std;
  using namespace os_test;
  
  auto obj = CLibrary_create_new_instance();
  CLibrary_register_manipulator_function
    (
      obj ,
      Incrementor::s_compute
    );
  obj->number = 5;
  
  auto oa_inc = std::make_shared<Incrementor>(12);
  CLibrary_register_custom_instance_ptr
    (
      obj ,
      static_cast<void *>( oa_inc.get() )
    );
    
  cout 
    << "Number in Instance:" << endl
    << "  " << setw(4) << obj->number << endl;
  
  CLibrary_call_callback_function(obj);
  
  cout 
    << "Number in Instance:" << endl
    << "  " << setw(4) << obj->number << endl;
    
  oa_inc->set_number(-12);
  CLibrary_call_callback_function(obj);  
  
  cout 
    << "Number in Instance:" << endl
    << "  " << setw(4) << obj->number << endl;
  
  CLibrary_destroy_instance(obj);
}
  
} } // namespace