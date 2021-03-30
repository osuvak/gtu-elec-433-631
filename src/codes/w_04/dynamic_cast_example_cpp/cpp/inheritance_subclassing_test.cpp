// Onder Suvak (C) 2020

#include <iostream>
#include <iomanip>
#include <memory>
#include <vector>
#include <unordered_map>
#include <string>

namespace os_test {

void
ctor_dtor_call_auxiliary
(
  std::string  fcn_id ,
  std::string  class_name
)
{
  using namespace std;
  cout 
    << fcn_id + " called: " + class_name + "."
    << endl;
}
  
void
ctor_call
(std::string class_name)
{
  ctor_dtor_call_auxiliary
    ("Constructor", class_name);
}

void
dtor_call
(std::string  class_name)
{
  ctor_dtor_call_auxiliary
    ("Destructor ", class_name);
}

void
member_fcn_call
(
  std::string  class_name ,
  std::string  fcn_name = "do_task"
)
{
  using namespace std;
  cout
    << "Member function \'" + fcn_name
       + "\' called of "    + class_name + " instance." 
    << endl; 
}

class FatherClass
{
private:
  std::string class_name_;
  
public:
  FatherClass()
  :
  class_name_("FatherClass")
  {
//     using namespace std;
//     cout << "Constructor called: FatherClass." << endl;
    ctor_call( class_name_ );
  }
  
  virtual
  ~FatherClass() 
  {
    dtor_call( class_name_ ); 
  }
  
  virtual
  void
  do_task () = 0;
};

class Child_A
:
public FatherClass
{
private:
  std::string class_name_;
  
public:
  Child_A ()
  :
  FatherClass () ,
  class_name_("Child_A")
  {
    ctor_call( class_name_ );
  }
  
  virtual
  ~Child_A ()
  {
    dtor_call( class_name_ );
  }
  
  virtual
  void
  do_task ()
  {
    member_fcn_call( class_name_ );
  }
  
  void
  do_task_special_to_A ()
  {
    member_fcn_call
      ( class_name_ , "do_task_special_to_A" );
  }
};

class Child_B
:
public FatherClass
{
private:
  std::string class_name_;
  
public:
  Child_B ()
  :
  FatherClass () ,
  class_name_("Child_B")
  {
    ctor_call( class_name_ );
  }
  
  virtual
  ~Child_B ()
  {
    dtor_call( class_name_ );
  }
  
  virtual
  void
  do_task ()
  {
    member_fcn_call( class_name_ );
  }
};

void
null_ptr_check
(
  void *       ptr ,
  std::string  job_descriptor = "Unidentified Job"
)
{
  using namespace std;
  
  cout 
    << job_descriptor << ":"
    << endl << "  ";
  if (ptr)
    cout 
      << "NOT NULL";
  else
    cout 
      << "NULL";
  cout << endl;
}
    

namespace typedefs {
  using test_fcn_ptr_type  = void (*)(void);
  using tests_map_type 
    = std::unordered_map< std::string , test_fcn_ptr_type >;
} // namespace

} // namespace

namespace tests_actual {
  void
  child_A_virtual_fcn_call_test
  (void);
  
  void
  polymorphic_ptr_test
  (void);
  
  void
  dynamic_cast_to_subclass_pointer_test
  (void);
  
  void
  dynamic_cast_to_polymorphic_pointer_test
  (void);
} // namespace

int
main (void)
{
  using namespace std;
  using namespace os_test;
  
  using namespace tests_actual;
//   namespace t_ac = tests_actual;
  
  typedefs::tests_map_type 
    tests_map = 
      {
        { "child_A_virtual_fcn_call" , 
           child_A_virtual_fcn_call_test 
        } ,
        { "polymorphic_ptr" ,
           polymorphic_ptr_test
        } ,
        { "dynamic_cast_to_subclass_pointer" ,
           dynamic_cast_to_subclass_pointer_test
        } ,
        { "dynamic_cast_to_polymorphic_pointer" ,
           dynamic_cast_to_polymorphic_pointer_test
        } ,
      };
  
  int ch = 1;
      
  switch (ch)
  {
    case 1:
    {
      cout << endl;
  
      tests_map
      [
//         "child_A_virtual_fcn_call"
//         "polymorphic_ptr"
//         "dynamic_cast_to_subclass_pointer"
        "dynamic_cast_to_polymorphic_pointer"
      ] ();
  
      cout << endl;
      break;
    }
    
    case 2:
    {
      for ( auto & item : tests_map )
      {
        cout 
          << endl
          << "*** TEST " << item.first << " ***" 
          << endl << endl;
//         tests_map[ item.first ] ();
        item.second ();
      }
      cout << endl;
      break;
    }
    
    default:
    {
      cout << "No such choice." << endl;
      break;
    } 
  }
  
  return 0;
}

namespace tests_actual {
  
  void
  child_A_virtual_fcn_call_test
  (void)
  {
    using namespace std;
    using namespace os_test;
    
    //   FatherClass oa_f;
    Child_A oa_c_a;
    oa_c_a.do_task();
  }
  
  void
  polymorphic_ptr_test
  (void)
  {
    using namespace std;
    using namespace os_test;
    
    FatherClass * ob_c_a_ptr = new Child_A;
    ob_c_a_ptr->do_task();
    delete ob_c_a_ptr;
  }
  
  void
  dynamic_cast_to_subclass_pointer_test
  (void)
  {
    using namespace std;
    using namespace os_test;
    
    auto 
    fh_null_ptr_check
      = []( void *       ptr ,
            std::string  job_descriptor = "Unidentified Job"
          )
        {
          cout 
            << job_descriptor << ":"
            << endl << "  ";
          if (ptr)
            cout 
              << "NOT NULL";
          else
            cout 
              << "NULL";
          cout << endl;
        };
    
    FatherClass * ob_c_a_ptr = new Child_A;
//     FatherClass * ob_c_b_ptr = new Child_B;
    
    auto * a_ptr = dynamic_cast<Child_A *>(ob_c_a_ptr);
    fh_null_ptr_check( a_ptr , 
                       "Plain Child_A Pointer Check" );
    
    delete a_ptr;
//     delete ob_c_a_ptr;
//     delete ob_c_b_ptr;
  }
  
  void
  dynamic_cast_to_polymorphic_pointer_test
  (void)
  {
    using namespace std;
    using namespace os_test;
    
    Child_A * a_ptr = new Child_A;
    
    a_ptr->do_task();
    a_ptr->do_task_special_to_A();
    
    auto * ob_c_a_ptr = dynamic_cast<FatherClass *>(a_ptr);
    null_ptr_check( ob_c_a_ptr , 
                    std::string("Polymorphic Pointer Check ")
                      + "(Obtained from Plain Child_A Pointer)" );
    
    ob_c_a_ptr->do_task();
//     ob_c_a_ptr->do_task_special_to_A();
    
    auto * b_ptr = dynamic_cast<Child_B *>(ob_c_a_ptr);
    null_ptr_check( b_ptr , 
                    std::string("Plain Child_B Pointer Check ")
                      + "(Obtained from Polymorphic Pointer)" );
    
    delete a_ptr;
  }
} // namespace
