
#ifndef BOOST_CONTRACT_FUNCTION_HPP_
#define BOOST_CONTRACT_FUNCTION_HPP_

#include <boost/contract/aux_/code/func.hpp>
#include <boost/contract/aux_/code/invoke_or_error.hpp>
#include <boost/contract/ext_/preprocessor/traits/func.hpp> // f

/* PUBLIC */

#define BOOST_CONTRACT_FUNCTION(decl) \
    BOOST_CONTRACT_FUNCTION_D_R(1, 1, __LINE__, 0, decl)

#define BOOST_CONTRACT_FUNCTION_TPL(decl) \
    BOOST_CONTRACT_FUNCTION_D_R(1, 1, __LINE__, 1, decl)

#define BOOST_CONTRACT_FUNCTION_D_R(d, r, id, tpl, decl) \
    BOOST_CONTRACT_AUX_INVOKE_OR_ERROR(d, r, id, tpl, \
        decl, \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_PARSE_D(d, decl), \
        BOOST_CONTRACT_AUX_FUNC_D_R \
    )

#endif // #include guard

