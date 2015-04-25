
#ifndef BOOST_CONTRACT_FREE_FUNCTION_HPP_
#define BOOST_CONTRACT_FREE_FUNCTION_HPP_

#include <boost/contract/set/precondition_postcondition.hpp>
#include <boost/contract/aux_/function/free_function.hpp>
#include <boost/make_shared.hpp>

namespace boost { namespace contract {

boost::contract::set::precondition_postcondition free_function() {
    return boost::contract::set::precondition_postcondition(boost::make_shared<
            boost::contract::aux::function::free_function>());
}

} } // namespace

#endif // #include guard

