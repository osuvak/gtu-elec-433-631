// Onder Suvak (C) 2020

#include <iostream>
#include <iomanip>
#include <memory>
#include <algorithm>
#include <vector>
#include <string>

namespace os_test {
  class IncrementingFunctor
  {
  private:
    int number_;
    
  public:
    IncrementingFunctor
    (int number=1)
    :
    number_(number)
    {}
    
    int 
    operator()(int y) const 
    { return number_ + y; }
  };
  
  template
  <typename Fcn>
  void
  process_vector
  (
    std::vector<int> & vec,
    Fcn                f
  )
  {
    for ( auto & item : vec )
      item = f(item);
  }
  
} // namespace

int
main (void)
{
  using namespace std;
  using namespace os_test;
  
  auto fh_print = 
    [](std::string              str_desc,
       const std::vector<int> & vec
      )->void
    {
      cout 
        << str_desc << ":" << endl;
      cout << "  ";
      for ( const auto & item : vec )
        cout << setw(4) << item;
      cout << endl;
    };
  
  std::vector<int> vec = {1, 2, 3, 4, 5};
  fh_print(
    "Content Before Processing" , 
    vec );
  
  process_vector( vec , IncrementingFunctor() );
  fh_print(
    "Content After Processing - 1st Phase" , 
    vec );
  
  process_vector( vec , [](int x)->int { return 2*x; } );
  fh_print(
    "Content After Processing - 2nd Phase" , 
    vec );
  
  std::for_each( vec.begin() , vec.end() ,
                 [](int &x)->void { --x; } );
  fh_print(
    "Content After Processing - 3rd Phase" , 
    vec );
  
  return 0;
}