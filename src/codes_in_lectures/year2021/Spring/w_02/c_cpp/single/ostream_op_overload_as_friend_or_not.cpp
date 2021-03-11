// Onder Suvak (C) 2021

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

#define  USE_FRIEND_ATTRIBUTE

namespace os_test {
  
class IDContainer
{
private:
  std::string   name_;
  unsigned int  number_;
  
public:
  IDContainer
  (
    std::string   name ,
    unsigned int  number
  )
  :
  name_(name) ,
  number_(number)
  {}
  
  ~IDContainer () = default;
  
  std::string
  get_ID
  ()
  const
  {
    using namespace std;
    
    std::stringstream  ss;
    ss << name_ << number_;
    
    return ss.str();
  }

#ifdef  USE_FRIEND_ATTRIBUTE
  friend
  std::ostream &
  operator<<
  (
    std::ostream &       ss, 
    const IDContainer &  obj
  );
#endif
};
  
std::ostream &
operator<<
(
  std::ostream &       ss, 
  const IDContainer &  obj
)
{
#ifdef  USE_FRIEND_ATTRIBUTE
  ss << obj.name_ << obj.number_;
#else
  ss << obj.get_ID();
#endif
  return ss;
}

} // namespace

int
main (void)
{
  using namespace std;
  using namespace os_test;
  
  IDContainer obj("Onder", 123);
  
  cout 
    << "Object ID :" << endl
    << "  " << obj << endl;
  
  return 0;
}