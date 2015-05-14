
#ifndef BOOST_CONTRACT_AUX_INVARIANT_HPP_
#define BOOST_CONTRACT_AUX_INVARIANT_HPP_

#include <boost/contract/core/config.hpp>
#include <boost/contract/aux_/type_traits/introspection.hpp>
/** @cond */
#include <boost/function_types/property_tags.hpp>
#include <boost/mpl/vector.hpp>
/** @endcond */

namespace boost { namespace contract { namespace aux {

namespace invariant_ {
    BOOST_CONTRACT_AUX_INTROSPECTION_HAS_MEMBER_FUNCTION(
            has_invariant, BOOST_CONTRACT_CONFIG_INVARIANT)
    
    BOOST_CONTRACT_AUX_INTROSPECTION_HAS_MEMBER_FUNCTION(
            has_non_static_invariant, BOOST_CONTRACT_CONFIG_STATIC_INVARIANT)

    BOOST_CONTRACT_AUX_INTROSPECTION_HAS_STATIC_MEMBER_FUNCTION(
            has_static_invariant, BOOST_CONTRACT_CONFIG_STATIC_INVARIANT)
}

// TODO: Unless PERMISSIVE, enforce: !has_invariant<C> ||
// has_const_invariant<C> || has_const_volatile_invariant<C> 

template<typename T>
struct has_const_invariant : invariant_::has_invariant<T, void,
        boost::mpl::vector<>, boost::function_types::const_non_volatile> {};

template<typename T>
struct has_const_volatile_invariant : invariant_::has_invariant<T, void,
        boost::mpl::vector<>, boost::function_types::cv_qualified> {};

template<typename T>
struct has_invariant : invariant_::has_invariant<T, void,
        boost::mpl::vector<> > {};

// TODO: Unless PERMISSIVE, enforce: !has_non_static_invariant<Class>

template<typename T>
struct has_static_invariant : invariant_::has_static_invariant<T, void,
        boost::mpl::vector<> > {};

template<typename T>
struct has_non_static_invariant : invariant_::has_non_static_invariant<T, void,
        boost::mpl::vector<> > {};

} } } // namespace

#endif // #include guard

