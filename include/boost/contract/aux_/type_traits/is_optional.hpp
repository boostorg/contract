
#ifndef BOOST_CONTRACT_AUX_IS_OPTIONAL_HPP_
#define BOOST_CONTRACT_AUX_IS_OPTIONAL_HPP_

/** @cond */
#include <boost/optional.hpp>
#include <boost/type_traits/integral_constant.hpp>
/** @endcond */

namespace boost { namespace contract { namespace aux {

template<typename T>
struct is_optional : boost::false_type {};

template<typename T>
struct is_optional<boost::optional<T> > : boost::true_type {};

} } } // namespace

#endif // #include guard

