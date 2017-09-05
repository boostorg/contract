
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_AUX_RESULT_CONST_HPP_
#define CONTRACT_AUX_RESULT_CONST_HPP_

#include <contract/aux_/arg_const.hpp>
#include <boost/type_traits/is_void.hpp>
#include <boost/mpl/if.hpp>

namespace contract { namespace aux {

class void_result {}; // Must be copyable so to be returned.

template< typename Result >
struct result_const {
    typedef typename arg_const <
        typename boost::mpl::if_<boost::is_void<Result>,
              void_result
            , Result
        >::type
    >::type type;
};

}} // namespace contract::aux

#endif // #include guard

