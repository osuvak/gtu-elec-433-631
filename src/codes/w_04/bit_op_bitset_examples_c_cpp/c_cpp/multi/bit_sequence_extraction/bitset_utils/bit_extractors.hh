// Onder Suvak (C) 2020

#pragma once

#include <bitset>
#include <vector>
 
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
  ();
};
    
} } // namespace
