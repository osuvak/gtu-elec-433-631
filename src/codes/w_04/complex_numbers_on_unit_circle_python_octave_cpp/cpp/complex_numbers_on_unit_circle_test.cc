// Onder Suvak (C) 2020

#include <iostream>
#include <iomanip>
#include <string>
#include <complex>
#include <algorithm>
#include <tuple>
#include <vector>
#include <cmath>

namespace os_test {
  namespace complex_utils {

using vec_of_complex_type
  = std::vector< std::complex<double> >;
  
using tuple_of_vectors_type
  = std::tuple
      < 
        std::vector<double> , 
        vec_of_complex_type
      >;
    
std::vector<double>
linspace_minus_pi_to_plus_pi
(
  unsigned int no_values
)
{
  using namespace std;
  
  std::vector<double>  seq;
  seq.reserve( no_values );
  for ( unsigned int kk=0 ; kk<no_values ; ++kk )
    seq.push_back( - M_PI + ((double) kk) / no_values * 2. * M_PI );
  
  return seq;
}

tuple_of_vectors_type
get_angles_values_on_complex_unit_circle
(
  unsigned int no_values
)
{
  using namespace std;
  
  auto radian_val 
    = linspace_minus_pi_to_plus_pi(no_values);
  vec_of_complex_type  result
    ( radian_val.size() , std::complex<double>(0., 0.) );
  std::transform
    (
      radian_val.begin() ,
      radian_val.end() ,
      result.begin() ,
      []
      (const double value)->std::complex<double>
      {
        return
          std::complex<double>
            (
              cos( value ) , sin( value )
            );
      }
    );
    
  return tuple_of_vectors_type(radian_val, result);
}

} } // namespace

int
main (void)
{
  using namespace std;
  using namespace os_test::complex_utils;
  
  using tuple_of_angles_points_type 
    =
    std::tuple< const double & , 
                const std::complex<double> & >;
  
  using vector_of_tuple_of_angles_points_type 
    =
    std::vector< tuple_of_angles_points_type >;
    
  const unsigned int  no_values = 100;
  const double        rel_tol   = 1.0E-6;
  const double        abs_tol   = 1.0E-10;
  
  auto values 
    = get_angles_values_on_complex_unit_circle
        ( no_values );
  const auto & angles_vec 
    = std::get<0>( values );
  const auto & complex_points_vec
    = std::get<1>( values );
  
  vector_of_tuple_of_angles_points_type
    corresponding_values_vec;
  for ( unsigned int 
          kk = 0 ; 
        kk < angles_vec.size() ;
        ++kk
      )
  {
    corresponding_values_vec.emplace_back
      (
        std::forward_as_tuple
          ( 
            angles_vec[kk] ,
            complex_points_vec[kk]
          )
      );
  }
    
  auto & vec_alias = corresponding_values_vec;
  bool flag_check_norm
    =
    std::all_of
    (
      vec_alias.begin() ,
      vec_alias.end() ,
      [rel_tol]
      (const tuple_of_angles_points_type & item)->bool
      {
        return 
          ( fabs( std::norm( std::get<1>(item) ) - 1.0 ) <= rel_tol );
      }
    );
    
  cout 
    << "Check for unity norm of all values on the complex unit circle :"
    << endl
    << "  " << ( flag_check_norm ? "YES" : "NO" )
    << endl;
  
  auto fh_check_relative
    =
    [rel_tol, abs_tol]
    ( const double  computed ,
      const double  desired  )->bool
    {
      return
        ( fabs( computed - desired ) 
            <= abs_tol + rel_tol * fabs( desired ) );
    };
  
  bool flag_check_angles
    =
    std::all_of
    (
      vec_alias.begin() ,
      vec_alias.end() ,
      [fh_check_relative]
      (const tuple_of_angles_points_type & item)->bool
      {
        return
          fh_check_relative
            ( std::arg( std::get<1>(item) ) ,
              std::get<0>(item) );
      }
    );
  
  cout 
    << "Check for compliance of each returned arg and original angle tuples :"
    << endl
    << "  " << ( flag_check_angles ? "YES" : "NO" )
    << endl;
    
  return 0;
}