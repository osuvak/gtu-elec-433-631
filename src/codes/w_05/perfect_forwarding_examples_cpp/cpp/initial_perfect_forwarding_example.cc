// Onder Suvak (C) 2020

#include<string>
#include<iostream>
#include<iomanip>
#include<vector>

namespace os_test {
  
  class Treater
  {
  public:
    Treater ()
    :
    number_(120),
    text_("treated")
    {}
    ~Treater() = default;
    
    Treater &
    treat
    (
      std::vector<int> & v ,
      std::string      & text
    )
    {
      v.push_back(number_);
      text += "_" + text_;
      return *this;
    }
    
  private:
    int         number_;
    std::string text_;
  };
  
  template<class T, class... U>
  void
  call_treat(T & obj, U&&... u)
  {
    obj.treat(std::forward<U>(u)...);
  }
  
} // namespace

int
main (void)
{
  using namespace os_test;
  using namespace std;
  
  auto fh_print 
    = [](const std::vector<int> & vec, 
         const std::string &      text)
      {
        cout 
          << "Vector Contents:" << endl;
        for ( auto item : vec )
          cout << "  " << setw(6) << item;
        cout << endl;
        
        cout 
          << "Text Content:" << endl
          << "  " << text << endl;
      };
  
  std::vector<int> v = {1, 2, 3};
  std::string      name("Onder Suvak");
  Treater obj;
  
  cout << "*** Before Treatment ***" << endl;
  fh_print(v, name);
  call_treat<Treater>(obj, v, name);
  cout << "*** After  Treatment ***" << endl;
  fh_print(v, name);
  
  return 0;
}