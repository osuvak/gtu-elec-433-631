// Onder Suvak (C) 2020

#include<sstream>
#include<iostream>
#include<iomanip>
#include<string>
#include<vector>
#include<algorithm>

std::string
get_text
()
{
  using namespace std;
  
  std::stringstream ss;
  ss << "*** stringstream example ***" << endl;
  ss << "Onder Suvak" << endl;
  ss << "Gebze Technical University" << endl << endl;
  
  std::vector<int> v = {1, 2, 3, 4, 5};
  std::for_each
    ( v.begin(), v.end(),
      [](int & item) { item *= 10; }
    );
  ss 
    << "I can put numbers into my string stream in a for loop:"
    << endl;
  for (auto item : v)
    ss  << "  " << setw(4) << item;
  ss << endl;
  
  return ss.str();
}

int
main (void)
{
  using namespace std;
  cout << get_text();
  
  return 0;
}