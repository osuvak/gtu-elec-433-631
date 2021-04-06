// Onder Suvak (C) 2020

#include <iostream>
#include <iomanip>
#include <vector>
#include <tuple>
#include <memory>
#include <algorithm>

namespace os_test {
  class NumberContainer
  {
  private:
    int number_;
    
  public:
    NumberContainer
    (int number = 0)
    :
    number_(number)
    {}
    
    ~NumberContainer() = default;
  };
  
} // namespace

void
test_copy_range_of_shared_ptr();

int
main (void)
{
  test_copy_range_of_shared_ptr();
  return 0;
}

void
test_copy_range_of_shared_ptr()
{
  using namespace os_test;
  using namespace std;
  
  using vector_type 
    = std::vector<std::shared_ptr<NumberContainer>>;
  
  const int NO_ITEMS = 10;
  
  vector_type  vec_original, vec_copied;
  
  vec_original.reserve(NO_ITEMS);
  for ( int kk=0 ; kk<NO_ITEMS ; ++kk )
    vec_original.emplace_back( 
      std::make_shared<NumberContainer>(kk) );
    
  vec_copied.reserve(NO_ITEMS);
  std::copy( 
    vec_original.begin() ,
    vec_original.end() ,
    back_inserter(vec_copied)
  );
  
  for ( unsigned int kk=0 ; kk<vec_original.size() ; ++kk )
  {
    cout 
      << "Items with index " 
      << setw(4) << kk << " are "
      << ( ( vec_original[kk].get() 
               == vec_copied[kk].get() )
           ? "identical" : "not identical" )
      << "." << endl;
  }
  
  using iterator_type
    = decltype(vec_original.begin());
  using tuple_type
    = std::tuple< iterator_type , iterator_type >;
  using vector_of_tuples_type
    = std::vector< tuple_type >;
  
  vector_of_tuples_type vec_it_tuples;
  for ( unsigned int kk=0 ; kk<vec_original.size() ; ++kk )
  {
    vec_it_tuples.emplace_back
      ( kk + vec_original.begin() , 
        kk + vec_copied.begin() );
  }
  
  auto lval 
    = std::all_of( 
        vec_it_tuples.begin() ,
        vec_it_tuples.end() ,
        [](tuple_type item)->bool 
          { return 
              (*(std::get<0>(item))).get() 
              == 
              (*(std::get<1>(item))).get(); }
      );
  cout << endl;
  cout 
    << (lval ? "All" : "Not all")
    << " items are identical."
    << endl;
}