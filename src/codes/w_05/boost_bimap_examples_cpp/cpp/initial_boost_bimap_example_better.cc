// Onder Suvak (C) 2020

#include <string>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <memory>
#include <sstream>
#include <map>
#include <type_traits>

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
    
    friend 
    std::ostream& operator<<(std::ostream & os, const Container & c);
    
  private:
    int number_;
  };
  
  std::ostream& operator<<
  (std::ostream & os, const Container & c)
  {
    os << c.number_;
    return os;
  }
  
  namespace common_typedefs {
    using bimap_type 
      = boost::bimap<std::string, os_test::Container*>;
    using value_type
      = bimap_type::value_type;
    using map_of_pointers_type 
      = std::map
        <os_test::Container*, std::shared_ptr<os_test::Container>>;
        
    using tuple_of_maps_type
      = std::tuple<bimap_type, map_of_pointers_type>;
  } // namespace
  
  namespace utilities {
    using namespace os_test::common_typedefs;

    template
    < typename T,
      typename 
        std::enable_if<
          std::is_pointer<T>{},
          int>::type = 0 >
    std::string
    printer_auxiliary
    (T item)
    {
      std::stringstream ss;
      ss << *item;
      return ss.str();
    }

    template
    < typename T,
      typename 
        std::enable_if<
          !std::is_pointer<T>{},
          int>::type = 0 >
    std::string
    printer_auxiliary
    (T item)
    {
      return item;
    }
    
    template
    <typename T>
    std::function<void(std::string, const T &)>
    get_printer_lambda
    ()
    {
      using namespace std;
      auto fh_print =
        []( std::string id,
            const T &   internal_map)->void
          {
            cout 
              << "*** Iterating through the Map with the "
              << setw(5) << id << " Key ***"
              << endl;
            for ( 
              auto 
              item  = internal_map.begin() ;
              item != internal_map.end() ;
              ++item
            )
            {
              cout 
                << "  " << setw(10) 
                << printer_auxiliary(item->first) << " -> "
                << setw(10) 
                << printer_auxiliary(item->second)
                << endl;
            }
          };
      return fh_print;
    }

    void
    print_map
    (
      const tuple_of_maps_type & current_tuple ,
      std::string                choice = "left"
    )
    {
      using namespace std;
      const auto & current_map = std::get<0>(current_tuple);
      
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
            using internal_map_type 
              = decltype(current_map.left);
            auto fh_print 
              = get_printer_lambda<internal_map_type>();
            fh_print("Left" , current_map.left );
          } // scope - end
          break;
        case choices::right:
          { // scope - begin
            using internal_map_type 
              = decltype(current_map.right);
            auto fh_print 
              = get_printer_lambda<internal_map_type>();
            fh_print("Right", current_map.right);
          } // scope - end
          break;
        default: // not necessary
          break;
      } // switch
    } // print_map
  } // namespace
} // namespace

namespace {
  using namespace std;
  using namespace os_test;
  using namespace os_test::common_typedefs;
  using namespace os_test::utilities;
  
  tuple_of_maps_type
  create_data
  ()
  {
    const int SZ = 5;
    bimap_type 
      container_map;
    map_of_pointers_type
      pointers_map;
  
    for ( int kk=0 ; kk<5 ; ++kk )
    {
      std::stringstream ss;
      char tmp_no[256];
    
      std::shared_ptr<Container> tmp_ptr
        = make_shared<Container>(10 * (SZ-kk));
    
      sprintf( tmp_no , "%02d" , 1+kk );
      ss << tmp_no;
      pointers_map[&(*tmp_ptr)] = tmp_ptr;
      container_map.insert
        ( value_type( "C" + ss.str() , 
                      &(*tmp_ptr)
        ) );
    }
    
    tuple_of_maps_type
      maps_tuple(container_map, pointers_map);
    return maps_tuple;
  }
} // namespace

int
main (void)
{
  using namespace std;
  using namespace os_test;
  using namespace os_test::common_typedefs;
  using namespace os_test::utilities;
    
  auto maps_tuple = create_data();
  
  print_map(maps_tuple);
  print_map(maps_tuple, "right");
  
  return 0;
}