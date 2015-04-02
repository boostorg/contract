
#ifndef BOOST_CONTRACT_FUNCTION_HPP_
#define BOOST_CONTRACT_FUNCTION_HPP_

#include <boost/contract/aux_/code/func.hpp>
#include <boost/contract/aux_/code/invoke_or_error.hpp>
#include <boost/contract/aux_/name.hpp>
#include <boost/contract/ext_/preprocessor/traits/func.hpp> // f
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/preprocessor/control/expr_iif.hpp>
#include <boost/preprocessor/logical/compl.hpp>

/* PUBLIC */

#define BOOST_CONTRACT_FUNCTION_BODY(function_name) \
    BOOST_CONTRACT_AUX_NAME2(function_name, body)

#define BOOST_CONTRACT_FUNCTION(decl) \
    BOOST_CONTRACT_FUNCTION_D_R(1, 1, __LINE__, 0, decl)

#define BOOST_CONTRACT_FUNCTION_TPL(decl) \
    BOOST_CONTRACT_FUNCTION_D_R(1, 1, __LINE__, 1, decl)

#define BOOST_CONTRACT_FUNCTION_D_R(d, r, id, tpl, decl) \
    BOOST_CONTRACT_AUX_INVOKE_OR_ERROR(d, r, id, tpl, \
        decl, \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_PARSE_D(d, decl), \
        BOOST_CONTRACT_FUNCTION_ \
    )

/* PRIVATE */

// Access is handled here (outside all code/ macros) so it is used only once.
#define BOOST_CONTRACT_FUNCTION_(d, r, id, tpl, f) \
    BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_ACCESS(f) \
    BOOST_PP_EXPR_IIF(BOOST_PP_COMPL(BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
            BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_ACCESS(f))), \
        : \
    ) \
    BOOST_CONTRACT_AUX_FUNC_D_R(d, r, id, tpl, f)

#endif // #include guard

