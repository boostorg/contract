
#ifndef BOOST_CONTRACT_AUX_PARAMS_HPP_
#define BOOST_CONTRACT_AUX_PARAMS_HPP_

#include <boost/contract/aux_/name.hpp>
#include <boost/contract/ext_/preprocessor/traits/param.hpp> // p
#include <boost/contract/ext_/preprocessor/keyword/template.hpp>
#include <boost/contract/ext_/preprocessor/utility/empty.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/tuple/rem.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/control/expr_iif.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>

/* PUBLIC */

#define BOOST_CONTRACT_AUX_PP_PARAM_INDEXED_NAME(i) \
    BOOST_CONTRACT_AUX_NAME2(arg, i)

// Types, names, and default arguments (for usual declarations, etc.).
// If not EMPTY(), extra_params decl pp-tuple is appended at param list's end.
#define BOOST_CONTRACT_AUX_PARAMS_WITH_DEFAULTS_D_R(d, r, id, tpl, \
        params_traits, extra_params) \
    BOOST_CONTRACT_AUX_PARAMS_(d, r, id, tpl, params_traits, extra_params, \
            (1, 1, 0, 1))

// Names only (for invocations, etc.).
#define BOOST_CONTRACT_AUX_PARAMS_NAMES_D_R(d, r, id, tpl, \
        params_traits, extra_params) \
    BOOST_CONTRACT_AUX_PARAMS_(d, r, id, tpl, params_traits, extra_params, \
            (0, 1, 0, 0))

/* PRIVATE */

#define BOOST_CONTRACT_AUX_PARAMS_(d, r, id, tpl, params_traits, extras, \
        type_named_indexed_default) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY(params_traits), \
        BOOST_PP_TUPLE_EAT(3) \
    , \
        BOOST_PP_SEQ_FOR_EACH_I_R \
    )(r, BOOST_CONTRACT_AUX_PARAM_, type_named_indexed_default, params_traits) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY(extras), \
        BOOST_PP_TUPLE_EAT(1) \
    , \
        BOOST_CONTRACT_AUX_PARAMS_EXTRAS_ \
    )(extras)

#define BOOST_CONTRACT_AUX_PARAMS_EXTRAS_(extras) \
    , BOOST_PP_TUPLE_REM_CTOR(extras)

#define BOOST_CONTRACT_AUX_PARAM_(r, type_named_indexed_default, i, p) \
    BOOST_CONTRACT_AUX_PARAM_ARGS_(r, i, p, \
        BOOST_PP_TUPLE_ELEM(4, 0, type_named_indexed_default), \
        BOOST_PP_TUPLE_ELEM(4, 1, type_named_indexed_default), \
        BOOST_PP_TUPLE_ELEM(4, 2, type_named_indexed_default), \
        BOOST_PP_TUPLE_ELEM(4, 3, type_named_indexed_default) \
    )

#define BOOST_CONTRACT_AUX_PARAM_ARGS_(r, i, p, \
        has_type, has_name, has_index, has_default) \
    BOOST_PP_COMMA_IF(i) \
    BOOST_PP_IIF(has_type, \
        BOOST_CONTRACT_AUX_PARAM_TYPE_ \
    , \
        BOOST_PP_TUPLE_EAT(1) \
    )(p) \
    BOOST_PP_IIF(has_name, \
        BOOST_CONTRACT_AUX_PARAM_NAME_ \
    , BOOST_PP_IIF(has_index, \
        BOOST_CONTRACT_AUX_PARAM_INDEXED_NAME_ \
    , \
        BOOST_PP_TUPLE_EAT(1) \
    ))(p, i) \
    BOOST_PP_IIF(has_default, \
        BOOST_CONTRACT_AUX_PARAM_DEFAULT_ \
    , \
        BOOST_PP_TUPLE_EAT(1) \
    )(p)

#define BOOST_CONTRACT_AUX_PARAM_TYPE_(p) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TEMPLATE_FRONT( \
            BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_TYPE(p)), \
        BOOST_CONTRACT_AUX_TEMPLATE_PARAM_TEMPLATE_ \
    , \
        BOOST_CONTRACT_EXT_PP_UNPARENTHESIZE \
    )(BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_TYPE(p))

#define BOOST_CONTRACT_AUX_TEMPLATE_PARAM_TEMPLATE_(type) \
    template< BOOST_PP_TUPLE_REM_CTOR( \
        BOOST_CONTRACT_EXT_PP_TEMPLATE_PARAM_TRAITS_TYPE_TEMPLATE_PARAMS(type) \
    ) > BOOST_CONTRACT_EXT_PP_TEMPLATE_PARAM_TRAITS_TYPE_TEMPLATE_KEY(type)

#define BOOST_CONTRACT_AUX_PARAM_NAME_(p, i) \
    BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_NAME(p)

#define BOOST_CONTRACT_AUX_PARAM_INDEXED_NAME_(p, i) \
    BOOST_CONTRACT_AUX_PP_PARAM_INDEXED_NAME(i)

#define BOOST_CONTRACT_AUX_PARAM_DEFAULT_(p) \
    BOOST_PP_EXPR_IIF(BOOST_PP_COMPL(BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
            BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_DEFAULT(p))), \
        = BOOST_PP_TUPLE_REM(0) \
    ) BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_DEFAULT(p)
        
#endif // #include guard

