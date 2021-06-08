/*
 * This file is part of the "dev-in-place" repository located at:
 * https://github.com/osuvak/dev-in-place
 * 
 * Copyright (C) 2020  Onder Suvak
 * 
 * For licensing information check the above url.
 * Please do not remove this header.
 * */

#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <tuple>
#include <cassert>
#include <cstdio>

#include <itpp/itstat.h>

namespace os_test {
  
  namespace itpp_ext {
    template
    <class T>
    itpp::Vec<T>
    get_diag_square
    (
      const itpp::Mat<T> & in_mat ,
      int                  K = 0
    )
    {
      assert( in_mat.rows() == in_mat.cols() );
      assert( 
        ( K < +in_mat.rows() ) && 
        ( K > -in_mat.rows() ) );
      
      using namespace itpp;
      if ( K == 0 )
        return diag(in_mat);
      if ( K>0 )
        return diag( in_mat.get(
          0, -1-K+in_mat.rows(), K, -1+in_mat.cols()) );
      if ( K<0 )
        return diag( in_mat.get(
          -K, -1+in_mat.rows(), 0, -1+K+in_mat.cols()) );
    }
    
    template
    <class T>
    itpp::Mat<T>
    triu_square
    (
      const itpp::Mat<T> & in_mat,
      int                  K = 0
    )
    {
      assert( in_mat.rows() == in_mat.cols() );
      using namespace itpp;
      
      auto out_mat 
        = zeros(in_mat.rows(), in_mat.cols());
      if ( K >=  0 + in_mat.rows() )
        return out_mat;
      if ( K <= +1 - in_mat.rows() )
        return in_mat;
      
      for ( int jj=K ; jj<in_mat.rows() ; ++jj )
        out_mat +=
          itpp::diag( 
            itpp_ext::get_diag_square(in_mat, jj) , 
            jj );
      
      return out_mat;
    }
    
    void
    print_matrix
    (
      const itpp::mat & in_mat
    )
    {
      for ( int ii=0 ; ii<in_mat.rows() ; ++ii )
      {
        for ( int jj=0 ; jj<in_mat.cols() ; ++jj )
          printf( "  %11.6f" , in_mat(ii, jj) );
        printf( "\n" );
      }
    }
    
    void
    print_ivec
    (
      const itpp::ivec & in_ivec
    )
    {
      for ( int ii=0 ; ii<in_ivec.size() ; ++ii )
      {
        printf( "  %4d" , in_ivec(ii) );
      }
      printf( "\n" );
    }
  } // namespace
  
  class MatrixDecomposer
  {
  public:
    using lup_tuple_type
      = std::tuple
          <itpp::mat, itpp::mat, itpp::mat, itpp::ivec>;
    using vec_of_lup_tuples_type
      = std::vector<lup_tuple_type>;
    
  private:
    int  no_entries_;
    bool flag_symmetric_;
    
    itpp::mat matrix_;
    
    std::vector<itpp::mat> 
      vec_triu_matrices_;
    vec_of_lup_tuples_type
      vec_lup_;
    
  public:
    MatrixDecomposer
    (
      int  no_entries,
      bool flag_symmetric = true
    )
    :
    no_entries_(no_entries) ,
    flag_symmetric_(flag_symmetric)
    {
      using namespace itpp;
      matrix_ = itpp::randu(no_entries_, no_entries_);
      if (flag_symmetric_)
        matrix_ = (matrix_ + transpose(matrix_)) / 2.;
      
      vec_triu_matrices_.clear();
      vec_lup_.clear();
      for (int kk=0 ; kk>-matrix_.rows() ; --kk)
      {
        vec_triu_matrices_
          .push_back(
            itpp_ext::triu_square(matrix_, kk) );
        
        mat  L, U;
        ivec p;
        itpp::lu(vec_triu_matrices_.back(), L, U, p);
        vec_lup_
          .emplace_back(vec_triu_matrices_.back(), L, U, p);
      }
    }
    
    ~MatrixDecomposer() {}
    
    const
    std::vector<itpp::mat> &
    get_vector_of_matrices
    ()
    const
    {
      return vec_triu_matrices_;
    }
    
    const
    vec_of_lup_tuples_type &
    get_vector_of_lup
    ()
    const
    {
      return vec_lup_;
    }
  };
  
} // namespace

int
main (void)
{
  using namespace os_test;
  using namespace std;
  
  MatrixDecomposer oa(5);
  int cnt;
  
  const auto & vec = oa.get_vector_of_matrices();
  cnt = 0;
  for ( const auto & item : vec )
  {
    cout << "Matrix " << ++cnt << ":" << endl;
    itpp_ext::print_matrix(item);
  }
  cout << endl;
  
  const auto & vec_lup = oa.get_vector_of_lup();
  cnt = 0;
  for ( const auto & item : vec_lup )
  {
    ++cnt;
    std::stringstream ss;
    ss << "Matrix " << cnt;
    
    cout << ss.str() << ":" << endl;
    itpp_ext::print_matrix( std::get<0>(item) );
    cout << ss.str() << " (L factor):" << endl;
    itpp_ext::print_matrix( std::get<1>(item) );
    cout << ss.str() << " (U factor):" << endl;
    itpp_ext::print_matrix( std::get<2>(item) );
    cout << ss.str() << " (p factor):" << endl;
    itpp_ext::print_ivec( std::get<3>(item) );
    
    auto P = 
      itpp::to_mat( 
        itpp::permutation_matrix( std::get<3>(item) ) );
    cout << ss.str() << " (relative error):" << endl;
    printf( "  %.6e\n" ,
      itpp::norm(
        std::get<0>(item) 
        - itpp::transpose(P) 
        * std::get<1>(item) * std::get<2>(item) )
      /
      itpp::norm(
        std::get<0>(item) )
    );
  }
  
  return 0;
}