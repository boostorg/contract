
#ifndef BOOST_CONTRACT_AUX_OPTIONAL_HPP_
#define BOOST_CONTRACT_AUX_OPTIONAL_HPP_

/** @cond */
#include <boost/optional.hpp>
#include <boost/type_traits/integral_constant.hpp>
/** @endcond */

namespace boost { namespace contract { namespace aux {

template<typename T>
struct is_optional : boost::false_type {};

template<typename T>
struct is_optional<boost::optional<T> > : boost::true_type {};

template<typename T>
struct optional_value_type { typedef T type; };

template<typename T>
struct optional_value_type<boost::optional<T> > { typedef T type; };

} } } // namespace

#endif // #include guard

