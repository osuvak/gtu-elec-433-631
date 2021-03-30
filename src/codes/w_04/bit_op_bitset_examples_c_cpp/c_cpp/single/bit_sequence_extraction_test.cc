// Onder Suvak (C) 2020

#include <iostream>
#include <iomanip>
#include <string>
#include <bitset>
#include <vector>

namespace os_test {
  namespace bitset_utils {

template
<unsigned long N>
unsigned int
get_no_bits_to_shift
(
  const std::bitset<N> & arg_in
)
{
//   using local_data_type
//     = std::bitset<N>;
    
  unsigned int kk;
  for ( kk=0 ; kk<arg_in.size() ; ++kk )
  {
    if ( arg_in[kk] )
    {
      break;
    }
  }
  
  return kk;
}

} } // namespace

#define STREAM_LENGTH  28

namespace os_test {
  namespace bitset_utils {

using data_type
  = std::bitset<STREAM_LENGTH>;

using vec_of_data_type
  = std::vector< data_type >;
  
class BitExtractor
{
public:
  const
  static
  vec_of_data_type
    vec_of_masks;

private:
  data_type
    data_;
    
  vec_of_data_type
    vec_of_results_;
    
  std::vector<unsigned int>
    vec_of_shift_values_;
    
public:
  
  BitExtractor
  (
    const data_type  data
  )
  :
  data_(data)
  {
    vec_of_results_.reserve
      ( vec_of_masks.size() );
      
    vec_of_shift_values_.reserve
      ( vec_of_masks.size() );
      
    compute_masked_shifted_data_();
  }
  
  ~BitExtractor () = default;
  
public:
  
  const
  vec_of_data_type &
  get_results
  ()
  const
  {
    return vec_of_results_;
  }
  
  vec_of_data_type
  get_results_unshifted
  ()
  {
    vec_of_data_type res;
    res.reserve( vec_of_masks.size() );
    
    unsigned int cnt = 0;
    for ( const auto & item : vec_of_shift_values_ )
      res.push_back
        ( vec_of_results_[cnt++] << item );
    
    return res;
  }
  
private:
  
  const
  BitExtractor &
  compute_masked_shifted_data_
  ()
  {
    for ( const auto & item : vec_of_masks )
    {
      vec_of_shift_values_.push_back
        ( get_no_bits_to_shift
            <STREAM_LENGTH>
              ( item ) );
      vec_of_results_.push_back
        ( ( data_ & item ) >> vec_of_shift_values_.back() );
    }
    return *this;
  }
};

const
vec_of_data_type
  BitExtractor::vec_of_masks
    { data_type { 0x0380000 } ,
      data_type { 0x000000C } ,
    };
    
} } // namespace

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
      { data_type { 0x03  } ,
        data_type { 0x06  } ,
        data_type { 0x060 } ,
      } ;
      
  for ( const auto & item : masks )
  {
    bool flag_shift = false;
    unsigned int kk;
    for ( kk=0 ; kk<item.size() ; ++kk )
    {
      if ( item[kk] )
      {
        if ( !(kk==0) )
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