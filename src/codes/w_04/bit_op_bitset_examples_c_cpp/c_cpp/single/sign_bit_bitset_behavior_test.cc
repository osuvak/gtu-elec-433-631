// Onder Suvak (C) 2020

#include <iostream>
#include <iomanip>
#include <string>
#include <bitset>

// #define NO_BITS 18
// #undef  NO_BITS

int
main ()
{
  using namespace std;
  
  const unsigned int width_val = 16;
  
  const 
  unsigned int NO_BITS 
//     = 18;
    = 16;
  
  std::bitset<NO_BITS> data 
//     ( std::string("100000000101111001") );
    ( std::string("1000000101111001") );
  
  cout << endl;
  cout 
    << setw(width_val) << "data :  "
    << data << endl;
  
  auto shifted_r = data >> 1;
  
  cout << endl;
  cout 
    << setw(width_val) << "data :  "
    << data << endl;
  cout 
    << setw(width_val) << "shifted_r :  "
    << shifted_r << endl;
  
  cout << endl;
  return 0;
}