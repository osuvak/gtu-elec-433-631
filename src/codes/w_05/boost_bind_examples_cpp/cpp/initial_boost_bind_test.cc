// Onder Suvak (C) 2020

#include <boost/config.hpp>
#include <boost/bind.hpp>

#include <iostream>
#include <iomanip>

void
increment
(int val, int & number)
{
  number += val;
}

int
main(void)
{
  using namespace std;
  
  const int val = 5;
  int number = 10;
  
  auto fh = 
    boost::bind( increment, val, _1 );
    
  cout << "Number:" << setw(6) << number << endl;
  fh(number);
  cout << "Number:" << setw(6) << number << endl;
  fh(number);
  fh(number);
  cout << "Number:" << setw(6) << number << endl;
  
  return 0;
}