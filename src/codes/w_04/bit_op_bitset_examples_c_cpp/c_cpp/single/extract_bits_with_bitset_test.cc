// Onder Suvak (C) 2020

#include <iostream>
#include <iomanip>
#include <string>
#include <bitset>

int
main ()
{
  using namespace std;
  
  const unsigned int width_val = 16;
  
  std::bitset<16> data 
    ( std::string("0101111001") );
  std::bitset<16> mask
    ( 0x0038 );

  cout << endl;
  cout 
    << setw(width_val) << "data :  " << data << endl;
  cout 
    << setw(width_val) << "mask :  " << mask << endl;
  
  data <<= 1;
  cout << endl;
  cout 
    << setw(width_val) << "data :  " << data << endl;
  cout 
    << setw(width_val) << "mask :  " << mask << endl;
    
  auto result = data & mask;
  cout 
    << setw(width_val) << "result :  " << result << endl;

  auto shifted= result >> 3;
  cout 
    << setw(width_val) << "shifted :  "<< shifted<< endl;

  return 0;
}