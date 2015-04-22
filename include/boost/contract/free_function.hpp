
#ifndef BOOST_CONTRACT_FREE_FUNCTION_HPP_
#define BOOST_CONTRACT_FREE_FUNCTION_HPP_

#include <boost/contract/type.hpp>
#include <boost/contract/aux_/function/free_function.hpp>
#include <boost/make_shared.hpp>

namespace boost { namespace contract {

boost::contract::type free_function() {
    return boost::contract::type(boost::make_shared<boost::contract::aux::
            function::free_function>());
}

} } // namespace

#endif // #include guard

