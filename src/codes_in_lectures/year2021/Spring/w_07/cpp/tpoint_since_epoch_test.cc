// Onder Suvak (C) 2021

/* See the original examples at:
 *   http://www.cplusplus.com/reference/chrono/time_point/time_point/
 *   http://www.cplusplus.com/reference/chrono/duration/duration/
 * */

#include <iostream>
#include <chrono>
#include <ctime>
#include <ratio>
#include <vector>

int main ()
{
  using namespace std;
  using namespace std::chrono;
  
// NOTE : Code in the original example below.
/*
  system_clock::time_point tp_epoch;    // epoch value
  
  time_point <system_clock,duration<int>> tp_seconds (duration<int>(1));

  system_clock::time_point tp (tp_seconds);

  std::cout << "1 second since system_clock epoch = ";
  std::cout << tp.time_since_epoch().count();
  std::cout << " system_clock periods." << std::endl;

  // display time_point:
  std::time_t tt = system_clock::to_time_t(tp);
  std::cout << "time_point tp is: " << ctime(&tt);
*/

  typedef std::chrono::duration<int> 
    seconds_type;
  typedef std::chrono::duration<int, std::milli> 
    milliseconds_type;
  typedef std::chrono::duration<int, std::ratio<60>> 
    minutes_type;
  typedef std::chrono::duration<int, std::ratio<60*60>> 
    hours_type;

  using os_duration_type
//     = hours_type;
    = minutes_type;
//     = seconds_type;
    
  using tpoint_duration_type
    = time_point<system_clock, os_duration_type>;
    
  std::vector<tpoint_duration_type> vec_tpoints;
  for (unsigned int kk=1 ; kk<=5 ; ++kk)
    vec_tpoints.emplace_back( os_duration_type(kk) );
  
  for ( auto item : vec_tpoints )
  {
    system_clock::time_point tp( item );
    std::time_t tt = system_clock::to_time_t( tp );
    cout 
      << "time_point tp :  " << ctime(&tt);
//       << endl;
  }
  
  return 0;
}