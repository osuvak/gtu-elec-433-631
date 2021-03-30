// Onder Suvak (C) 2020
 
#include <iostream>
#include <iomanip>
#include <string>

#include "bitset_utils/stuff_bitset_utils.hh"

namespace os_test {
  namespace bitset_tests {
    
void
computing_no_bits_to_shift ();

void
obtain_masked_results ();
  
} } // namespace

int
main ()
{
  using namespace
    os_test::bitset_tests;
  
//   computing_no_bits_to_shift();
  obtain_masked_results();
  
  return 0;
}

namespace os_test {
  namespace bitset_tests {
void
computing_no_bits_to_shift 
()
{
  using namespace std;
  using namespace os_test::bitset_utils;
  
  const unsigned int width_val = 24;
  
  vec_of_data_type 
    masks 
      { data_type { 0x01  } ,
        data_type { 0x06  } ,
        data_type { 0x060 } ,
      } ;
      
  for ( const auto & item : masks )
  {
    bool flag_shift = false;
    unsigned int kk;
    for ( kk=0 ; kk<item.size() ; ++kk )
    {
      if ( item[kk] && !(kk==0) )
      {
        flag_shift = true;
        break;
      }
    }
    
    cout 
      << setw(width_val) << "Mask :  " << item << endl;
      
    if ( flag_shift )
    {
      cout 
        << setw(width_val) << "Shift Value :  " 
        << kk << endl;
      cout 
        << setw(width_val) << "Shifted :  " 
        << (item >> kk) << endl;
    }
    
    cout << endl;
  } // for
}

void
obtain_masked_results ()
{
  using namespace std;
  using namespace os_test::bitset_utils;
  
  const unsigned int width_val = 24;
  
  auto fh_print
    = [width_val]
      ( const std::string  id ,
        const data_type &  arg
      )->void
      {
        cout 
          << setw(width_val) << id << " :  "
          << arg << endl;
      };
  
  data_type    arg_in( 0x3502639 );
  BitExtractor ob    ( arg_in );
  
  const auto &
    results = ob.get_results();
  const auto
    results_unshifted = ob.get_results_unshifted();
  
  cout << endl;
  for ( unsigned int 
          kk = 0 ; 
          kk < BitExtractor::vec_of_masks.size() ;
          ++kk )
  {
    fh_print( "Data" ,
              arg_in );
    fh_print( "Mask" ,   
              BitExtractor::vec_of_masks[kk] );
    fh_print( "Unshifted Result" , 
              results_unshifted[kk] );
    fh_print( "Result" , 
              results[kk] );
    cout << endl;
  }
}

} } // namespace