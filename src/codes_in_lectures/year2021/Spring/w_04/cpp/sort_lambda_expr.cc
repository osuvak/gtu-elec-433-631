// Onder Suvak (C) 2021
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>

namespace os_test {
  
class MyContainer
{
private:
  int  number_;
  
public:
  MyContainer
  (
    int  number
  )
  :
  number_(number)
  {}
  
  ~MyContainer() = default;
  
  int
  get_number
  ()
  const
  {
//     ++number_;
    return number_;
  }
};
  
} // namespace

int
main (void)
{
  using namespace std;
  using namespace os_test;
  
  const
  unsigned int  MAX_NUMBER = 10;
  
  const
  std::string  printer_heading ( "Vector Contents" );
  std::string  explanation;
  
  std::vector<MyContainer>  vec;
  for ( unsigned int kk=0 ; kk<MAX_NUMBER ; ++kk )
    vec.emplace_back( MAX_NUMBER - kk );
  
  auto  fh_print
    = [  printer_heading ,
       & 
         explanation ]
      ( const std::vector<MyContainer> & vec )
      {
        cout 
          << printer_heading 
          << " (" << explanation << ")"
          << " :" << endl;
        for ( const auto & item : vec )
          cout << "  " << setw(4) << item.get_number();
        cout << endl;
      };
  
  explanation = "before sorting";
  fh_print(vec);
  
  auto  fh_compare
    = []( 
          const MyContainer & item1 ,
          const MyContainer & item2
        )
      {
        return item1.get_number() < item2.get_number();
      };
  
  std::sort
    ( 
      vec.begin() , 
//       vec.end() , 
      vec.begin() + 5 , 
      fh_compare 
    );
    
  explanation = "after sorting";
  fh_print(vec);
  
  return 0;
}
