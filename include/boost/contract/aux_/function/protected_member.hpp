
#ifndef BOOST_CONTRACT_AUX_PROTECTED_MEMBER_HPP_
#define BOOST_CONTRACT_AUX_PROTECTED_MEMBER_HPP_

#include <boost/contract/core/exception.hpp>
#include <boost/contract/aux_/function/free_function.hpp>

namespace boost { namespace contract { namespace aux {

// Not public members (i.e., protected members) are allowed to fail class
// invariants (so no inv) and they do not participate in virtual function
// polymorphism according to substitution principle (so no subcontracting).
// Therefore, their contracts behave like contracts of free functions.
typedef boost::contract::aux::basic_free_function<
        boost::contract::from_protected_member> protected_member;

} } } // namespace

#endif // #include guard

