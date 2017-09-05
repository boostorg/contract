
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_AUX_CODE_BASE_HPP_
#define CONTRACT_AUX_CODE_BASE_HPP_

#include <boost/mpl/identity.hpp>

// Bases.

// Expand to void_base if should not subcontract from base n-th.
// Precondition: n < size(bases).
#define CONTRACT_AUX_CODE_BASE_SUBCONTRACT_(z, n, c) \
    /* subcontract from all specified bases (valid n) as per [N1962] policy */ \
    /* (A++ policy would instead be to not subcontract from private bases */ \
    /* and subcontract pre and post but not inv from protected bases) */ \
    BOOST_PP_ARRAY_ENUM(CONTRACT_DETAIL_PP_BASE_TRAITS_TYPE(BOOST_PP_LIST_AT( \
            CONTRACT_DETAIL_PP_CLASS_TRAITS_BASES(c), n)))

#define CONTRACT_AUX_CODE_BASE_SELECT_(z, n, c) \
    BOOST_PP_IIF(BOOST_PP_LESS(n, BOOST_PP_LIST_SIZE( \
            CONTRACT_DETAIL_PP_CLASS_TRAITS_BASES(c))), \
        CONTRACT_AUX_CODE_BASE_SUBCONTRACT_ \
    , \
        CONTRACT_AUX_CODE_CLASS_TYPE \
        BOOST_PP_TUPLE_EAT(3) \
    )(z, n, c)

// PUBLIC //

#define CONTRACT_AUX_CODE_BASE_TYPE(n) \
    CONTRACT_AUX_SYMBOL( (base)(n) )

#define CONTRACT_AUX_CODE_BASE_SEQ_R(r, typename_keyword, b) \
    ( /* seq elem */ \
        CONTRACT_DETAIL_PP_BASE_TRAITS_ACCESS(b) \
        CONTRACT_DETAIL_PP_BASE_TRAITS_VIRTUAL(b) \
        /* no outer typename here because base list requires no typename */ \
        /* (bases known to be types), IDENTITY with add/remove reference */ \
        /* to handle unwrapped commas */ \
        ::boost::remove_reference< \
            typename_keyword \
            BOOST_IDENTITY_TYPE(( \
                typename_keyword \
                ::boost::add_reference< \
                    BOOST_PP_ARRAY_ENUM( \
                            CONTRACT_DETAIL_PP_BASE_TRAITS_TYPE(b)) \
                >::type \
            )) \
        >::type \
    )

#define CONTRACT_AUX_CODE_BASE_TYPEDEF_Z(z, n, c) \
    typedef \
        CONTRACT_AUX_CODE_BASE_SELECT_(z, n, c) \
        CONTRACT_AUX_CODE_BASE_TYPE(n) \
    ;

#endif // #include 


