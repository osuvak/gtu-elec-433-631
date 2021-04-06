// Onder Suvak (C) 2020

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cstdio>

namespace os_test {
  
  class NumberSequence
  {
  private:
    std::vector<double> vec_internal_;
    
  public:
    NumberSequence
    (
      const std::vector<double> & vec_in
    )
    :
    vec_internal_(vec_in)
    {}
    
    ~NumberSequence() = default;
    
    friend
    std::ostream & operator<< 
    (
      std::ostream &         stream,
      const NumberSequence & obj
    );
  };
  
  class StringHolder
  {
  private:
    std::string str_internal_;
    
  public:
    StringHolder
    (
      const std::string  str_in = "No Content"
    )
    :
    str_internal_(str_in)
    {}
    
    ~StringHolder() = default;
    
    friend
    std::ostream & operator<< 
    (
      std::ostream &       stream,
      const StringHolder & obj
    );
  };
  
  std::ostream & operator<< 
  (
    std::ostream &         stream,
    const NumberSequence & obj
  )
  {
    using namespace std;
    for (auto item : obj.vec_internal_)
      printf( "  %7.2f", item );
    return stream;
  }
  
  std::ostream & operator<< 
  (
    std::ostream &       stream,
    const StringHolder & obj
  )
  {
    stream 
      << "*** " << obj.str_internal_ 
      << " ***";
    return stream;
  }
} // namespace

int
main ()
{
  using namespace os_test;
  using namespace std;
  
  StringHolder hello( "Hello World!" );
  
  std::vector<double> vec_in;
  for ( int kk=1 ; kk<=10 ; ++kk )
    vec_in.push_back( kk );
  NumberSequence vec_holder( vec_in );
  
  cout 
    << hello << endl
    << vec_holder << endl;
  
  return 0;
}