// Onder Suvak (C) 2021

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

#include <cstdio>
#include <cstdlib>

// #define  GENERATE_ITOA_ERROR

int
main (void)
{
  using namespace std;
  
  std::stringstream  
    ss;
  std::string 
    name("Onder");
  
  unsigned int cnt = 1;
  
  for ( unsigned int kk = 0 ; kk < 5 ; ++kk )
  {
    ss << name << " " << cnt++;
    if ( kk < 4)
      ss << " ";
  }
  
  cout 
    << "String out of String Stream :" << endl
    << "  " << ss.str() << endl;

#ifdef GENERATE_ITOA_ERROR    
  cnt = 1;
  std::string result;
  for ( unsigned int kk = 0 ; kk < 5 ; ++kk )
  {
    char buffer[12];
    itoa(cnt++, buffer, 10);
    result += name;
    result += std::string(" ") + buffer;
    if ( kk < 4)
      result += " ";
  }
  
  cout 
    << "String with String Concatenation :" << endl
    << "  " << result << endl;
#endif
    
  return 0;
}