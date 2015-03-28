
#ifndef BOOST_CONTRACT_CLASS_HPP_
#define BOOST_CONTRACT_CLASS_HPP_

#include <boost/contract/aux_/code/class.hpp>
#include <boost/contract/aux_/code/invoke_or_error.hpp>
#include <boost/contract/ext_/preprocessor/traits/class.hpp> // c

/* PUBLIC */

#define BOOST_CONTRACT_CLASS(decl) \
    BOOST_CONTRACT_CLASS_D_R(1, 1, __LINE__, 0, decl)

#define BOOST_CONTRACT_CLASS_D_R(d, r, id, tpl, decl) \
    BOOST_CONTRACT_AUX_INVOKE_OR_ERROR(d, r, id, tpl, \
        decl, \
        BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_PARSE_D(d, decl), \
        BOOST_CONTRACT_AUX_CLASS_D_R \
    )

#endif // #include guard

