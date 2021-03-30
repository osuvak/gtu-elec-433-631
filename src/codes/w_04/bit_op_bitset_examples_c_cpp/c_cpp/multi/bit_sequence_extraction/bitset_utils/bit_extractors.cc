// Onder Suvak (C) 2020
 
#include "bitset_utils/bit_extractors.hh"
#include "bitset_utils/utilities.hh"

namespace os_test {
  namespace bitset_utils {
    
  const
  vec_of_data_type
    BitExtractor::vec_of_masks
      { data_type { 0x0380000 } ,
        data_type { 0x000000C } ,
      };
    
  const
  BitExtractor &
  BitExtractor::compute_masked_shifted_data_
  ()
  {
    for ( const auto & item : vec_of_masks )
    {
      vec_of_shift_values_.push_back
        ( get_no_bits_to_shift<STREAM_LENGTH>( item ) );
      vec_of_results_.push_back
        ( ( data_ & item ) >> vec_of_shift_values_.back() );
    }
    return *this;
  }
  
} } // namespace
