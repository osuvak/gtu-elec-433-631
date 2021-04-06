// Onder Suvak (C) 2020

#include <string>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <memory>
#include <sstream>
#include <map>

#include <boost/bimap.hpp>

namespace os_test {
  
  class Container
  {
  public:
    Container
    (int number = 0)
    :
    number_(number)
    {}
    
    ~Container() = default;
    
    int
    get_number
    ()
    {
      return number_;
    }
    
  private:
    int number_;
  };
  
  namespace common_typedefs {
    using bimap_type 
      = boost::bimap<std::string, std::shared_ptr<os_test::Container>>;
    using value_type
      = bimap_type::value_type;
  } // namespace
  
  namespace utilities {
    using namespace os_test::common_typedefs;
    
    void
    print_map
    (
      const bimap_type & current_map ,
      std::string        choice = "left"
    )
    {
      using namespace std;
      enum choices
      {
        left  = 0 ,
        right
      };
      
      std::map<std::string, int> 
        choices_map =
          { {"left" , choices::left  } , 
            {"right", choices::right } };
      
      // NOTE: Necessary to check if "choice" is in "choices_map".
      // TODO: Can/Should throw an exception if key is not found.
      if ( choices_map.find(choice) == choices_map.end() ) 
        return;
      
      int choice_current = choices_map[choice];
      switch( choice_current )
      {
        case choices::left:
          { // scope - begin
            cout 
              << "*** Iterating through the Map with the Left  Key ***"
              << endl;
            for ( 
              auto 
              item  = current_map.left.begin() ;
              item != current_map.left.end() ;
              ++item
            )
            {
              cout 
                << "  " << setw(10) << item->first << " -> "
                << setw(10) << (item->second)->get_number()
                << endl;
            }
          } // scope - end
          break;
        case choices::right:
          { // scope - begin
            cout 
              << "*** Iterating through the Map with the Right Key ***"
              << endl;
            for ( 
              auto 
              item  = current_map.right.begin() ;
              item != current_map.right.end() ;
              ++item
            )
            {
              cout 
                << "  " << setw(10) << (item->first)->get_number() 
                << " -> "
                << setw(10) << item->second
                << endl;
            }
          } // scope - end
          break;
        default: // not necessary
          break;
      } // switch
    } // print_map
  } // namespace
} // namespace

int
main (void)
{
  using namespace std;
  using namespace os_test;
  using namespace os_test::common_typedefs;
  using namespace os_test::utilities;
    
  const int SZ = 5;
  bimap_type container_map;
  
  for ( int kk=0 ; kk<5 ; ++kk )
  {
    std::stringstream ss;
    char tmp_no[256];
    
    sprintf( tmp_no , "%02d" , 1+kk );
    ss << tmp_no;
    container_map.insert
      ( value_type( "C" 
//                       + std::string(tmp_no) ,
                      + ss.str() , 
                    make_shared<Container>(10 * (SZ-kk))
      ) );
  }
  
  print_map(container_map);
  print_map(container_map, "right");
  
  return 0;
}