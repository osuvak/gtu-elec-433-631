// Onder Suvak (C) 2021

#include <omp.h>
#include <iostream>
#include <iomanip>

// #define  USE_CRITICAL_SECTION

int
main (void)
{
  using namespace std;
  
  const
  int total = 20;
  int thread_number;
  
  #pragma omp parallel private(thread_number)
  {
    #pragma omp for schedule(dynamic) nowait
    for( int ii = 0 ; ii < total ; ++ii )
    {
      thread_number = omp_get_thread_num();
#ifdef  USE_CRITICAL_SECTION
      #pragma omp critical(print_info)
      {
#endif
        cout 
          << "Thread " << setw(4) << thread_number
          << "    "
          << "Processing Number " << setw(4) << ii
          << endl;
#ifdef  USE_CRITICAL_SECTION
      }
#endif
    }
  }
  
  return 0;
}