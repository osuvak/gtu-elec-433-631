// Onder Suvak (C) 2021

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

namespace os_test {
  
  class FatherClass 
  {
  protected:
    int  number_;
    
  public:
    FatherClass  
    (
      int number = 0
    )
    :
    number_(number)
    {}
    
    virtual
    ~FatherClass () {}
    
    virtual
    int
    compute
    (
      int  number
    ) = 0;
    
  };
  
  class Multiplier
  :
  public
  FatherClass 
  {
  public:
    Multiplier
    (
      int  number
    )
    :
    FatherClass(number)
    {}
    ~Multiplier () {}
    
    virtual
    int
    compute
    (
      int  number
    )
    {
      return number_ * number;
    }
  };
  
  class Incrementor
  :
  public
  FatherClass 
  {
  public:
    Incrementor
    (
      int  number
    )
    :
    FatherClass(number)
    {}
    ~Incrementor () {}
    
    virtual
    int
    compute
    (
      int  number
    )
    {
      return number_ + number;
    }
  };
  
} // namespace

int
main (void)
{
  using namespace std;
  using namespace os_test;
  
  std::vector<FatherClass *> 
    vec_ptr;
    
  vec_ptr.push_back
    ( new Multiplier ( 5 ) );
  vec_ptr.push_back
    ( new Incrementor( 2 ) );
    
  const int number_input = 6;
  for ( auto * item : vec_ptr )
    cout
      << "  " << setw(4) << item->compute(number_input)
      << endl;
    
  for ( auto * item : vec_ptr )
    delete item;
  
  return 0;
}