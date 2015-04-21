
#ifndef BOOST_CONTRACT_FREE_FUNCTION_HPP_
#define BOOST_CONTRACT_FREE_FUNCTION_HPP_

#include <boost/contract/type.hpp>
#include <boost/contract/aux_/free_function.hpp>
#include <boost/make_shared.hpp>

namespace boost { namespace contract {

boost::contract::type free_function() {
    return boost::contract::type(boost::make_shared<boost::contract::aux::
            free_function>());
}

} } // namespace

#endif // #include guard

