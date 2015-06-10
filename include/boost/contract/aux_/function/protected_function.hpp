
#ifndef BOOST_CONTRACT_AUX_PROTECTED_FUNCTION_HPP_
#define BOOST_CONTRACT_AUX_PROTECTED_FUNCTION_HPP_

#include <boost/contract/core/exception.hpp>
#include <boost/contract/aux_/function/free_function.hpp>

namespace boost { namespace contract { namespace aux {

// Non-public member functions (e.g., protected member functions) are allowed
// to fail class invariants (so no inv) and they do not participate in virtual
// function polymorphism according to substitution principle (so no
// subcontracting). Therefore, these contract like free functions.
typedef boost::contract::aux::basic_free_function<
        boost::contract::from_protected_function> protected_function;

} } } // namespace

#endif // #include guard

