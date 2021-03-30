// Onder Suvak (C) 2020

#pragma once

#include <bitset>

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

