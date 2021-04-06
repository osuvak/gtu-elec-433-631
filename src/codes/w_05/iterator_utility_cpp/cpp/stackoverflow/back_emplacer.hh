#pragma once

#include <iterator>
#include <type_traits>

namespace stack_overflow_stuff
{
/* 
 * NOTE (Onder Suvak):
 *   I got the following much necessary "back_inserter" implementation
 *   from stackoverflow. Here is the URL:
 *     https://stackoverflow.com/questions/18724999/why-no-emplacement-iterators-in-c11-or-c14
 * */
  
template<class Container>
class back_emplace_iterator 
: 
public std::iterator< std::output_iterator_tag,
                      void, void, void, void >
{
protected:
    Container* container;
public:
    typedef Container container_type;

    explicit back_emplace_iterator(Container& x) : container(&x) {}

    template<class T>
    back_emplace_iterator<Container>&
    operator=(T&& t)
    {
        container->emplace_back(std::forward<T>(t));
        return *this;
    }

    back_emplace_iterator& operator*() { return *this; }
    back_emplace_iterator& operator++() { return *this; }
    back_emplace_iterator& operator++(int) { return *this; }
};

template< class Container >
inline back_emplace_iterator<Container>
back_emplacer( Container& c )
{
    return back_emplace_iterator<Container>(c);
}

} // namespace
