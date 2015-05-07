
#ifndef BOOST_CONTRACT_AUX_FUNCTION_PRIVATE_MEMBER_HPP_
#define BOOST_CONTRACT_AUX_FUNCTION_PRIVATE_MEMBER_HPP_

#include <boost/contract/core/exception.hpp>
#include <boost/contract/aux_/function/free_function.hpp>

namespace boost { namespace contract { namespace aux { namespace function {

// Not public members (i.e., private members) are allowed to fail class
// invariants (so no inv) and they do not participate in virtual function
// polymorphism according to substitution principle (so no subcontracting).
// Therefore, their contracts behave like contracts of free functions.
class private_member : public free_function {
public:
    explicit private_member() :
            free_function(boost::contract::from_private_member) {}
};

} } } } // namespace

#endif // #include guard

