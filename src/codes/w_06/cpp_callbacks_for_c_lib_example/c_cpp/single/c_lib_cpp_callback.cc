// Onder Suvak (C) 2021

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <memory>

typedef int (*ManipulatorFuncPtrType)(int, void *); 

typedef struct LibraryContainer_
{
  int 
    number;
  ManipulatorFuncPtrType
    func_ptr;
  void *
    custom_instance_ptr;
} LibraryContainer;

LibraryContainer *
CLibrary_create_new_instance
()
{
  LibraryContainer *instance_ptr
    = (LibraryContainer *) 
        calloc(1, sizeof(LibraryContainer));
  return instance_ptr;
}

void
CLibrary_destroy_instance
(
  LibraryContainer *  instance_ptr
)
{
  if (!instance_ptr)
    free(instance_ptr);
}

void
CLibrary_register_manipulator_function
(
  LibraryContainer *      instance_ptr,
  ManipulatorFuncPtrType  func_ptr
)
{
  instance_ptr->func_ptr = func_ptr;
}

void
CLibrary_register_custom_instance_ptr
(
  LibraryContainer *  instance_ptr,
  void *              custom_instance_ptr
)
{
  instance_ptr->custom_instance_ptr
    = custom_instance_ptr;
}

void
CLibrary_call_callback_function
(
  LibraryContainer *  instance_ptr
)
{
  instance_ptr->number =
    instance_ptr->func_ptr
      (instance_ptr->number, instance_ptr->custom_instance_ptr);
}

int
CallbackFunction_increment
(
  int     number ,
  void *  custom_instance_ptr
)
{
  return number + 1;
}

int
CallbackFunction_double
(
  int     number ,
  void *  custom_instance_ptr
)
{
  return 2 * number;
}

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

namespace actual_tests {
  void
  callback_in_c_test();
  
  void
  callback_in_cpp_test();
  
} // namespace
} // namespace

int
main (void)
{
  using namespace os_test::actual_tests;
//   callback_in_c_test  ();
  callback_in_cpp_test();
  return 0;
}

namespace os_test {
  namespace actual_tests {
    
void
callback_in_c_test()
{
  using namespace std;
  
  auto obj = CLibrary_create_new_instance();
  CLibrary_register_manipulator_function
    (
      obj ,
      CallbackFunction_increment
//       CallbackFunction_double
    );
  obj->number = 5;
  
  cout 
    << "Number in Instance:" << endl
    << "  " << setw(4) << obj->number << endl;
  
  CLibrary_call_callback_function(obj);
  
  cout 
    << "Number in Instance:" << endl
    << "  " << setw(4) << obj->number << endl;
  
  CLibrary_destroy_instance(obj);
}
  
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