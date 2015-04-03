
#ifndef BOOST_CONTRACT_AUX_CLASS_HPP_
#define BOOST_CONTRACT_AUX_CLASS_HPP_

#include <boost/contract/aux_/code/params.hpp>
#include <boost/contract/aux_/eval.hpp>
#include <boost/contract/aux_/name.hpp>
#include <boost/contract/ext_/preprocessor/traits/class.hpp> // c
#include <boost/contract/ext_/preprocessor/traits/base.hpp> // b
#include <boost/contract/ext_/preprocessor/variadic/wrap_iif.hpp>
#include <boost/contract/ext_/preprocessor/utility/empty.hpp>
#include <boost/contract/ext_/preprocessor/parenthesize.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/tuple/rem.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/punctuation/comma.hpp>

/* PUBLIC */

// Type of class being declared.
#define BOOST_CONTRACT_AUX_CLASS_TYPE \
    BOOST_CONTRACT_AUX_NAME1(class_type)

// Type of extra evaluation base.
#define BOOST_CONTRACT_AUX_CLASS_EVAL_BASE_TYPE \
    BOOST_CONTRACT_AUX_NAME1(eval_base_type)

// Type of i-th base class, i in [0, number of base classes for this class).
#define BOOST_CONTRACT_AUX_CLASS_BASE_TYPE(i) \
    BOOST_CONTRACT_AUX_NAME2(base_type, i)

#define BOOST_CONTRACT_AUX_CLASS_D_R(d, r, id, tpl, c) \
    BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_EXPORT(c) \
    BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_TEMPLATE(c) \
    BOOST_CONTRACT_EXT_PP_VARIADIC_WRAP_IIF( \
        BOOST_PP_COMPL(BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
                BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_TEMPLATE(c))) \
    , \
        <, >, \
        BOOST_CONTRACT_AUX_PARAMS_WITH_DEFAULTS_D_R(d, r, id, tpl, \
            BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_TEMPLATE_PARAMS(c), \
            BOOST_PP_EMPTY() \
        ) \
    ) \
    BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_FRIEND(c) \
    BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_KEY(c) \
    BOOST_CONTRACT_EXT_PP_UNPARENTHESIZE( \
            BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_VERBATIM(c)) \
    BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_NAME(c) \
    BOOST_CONTRACT_EXT_PP_VARIADIC_WRAP_IIF( \
        BOOST_PP_COMPL(BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
                BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_SPECIALIZATION(c))) \
    , \
        <, >, \
        BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_SPECIALIZATION(c) \
    ) \
    BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_FINAL(c) \
    BOOST_PP_IIF(BOOST_CONTRACT_AUX_CLASS_HAS_EVAL_BASE_(c), \
        : private BOOST_CONTRACT_AUX_CLASS_EVAL_BASE_ \
    , \
        BOOST_PP_TUPLE_EAT(1) \
    )(c) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
            BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_BASES(c)), \
        BOOST_PP_TUPLE_EAT(4) \
    , \
        BOOST_PP_SEQ_FOR_EACH_I_R \
    )(r, \
        BOOST_CONTRACT_AUX_CLASS_BASE_, \
        BOOST_CONTRACT_AUX_CLASS_HAS_EVAL_BASE_(c), \
        BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_BASES(c) \
    ) \
    BOOST_PP_IIF(BOOST_CONTRACT_AUX_CLASS_HAS_TYPEDEFS_(c), \
        BOOST_CONTRACT_AUX_CLASS_TYPEDEFS_ \
    , \
        BOOST_PP_TUPLE_EAT(5) \
    )(d, r, id, tpl, c)

/* PRIVATE */

// TODO: Expand 0 if contracts disabled...
#define BOOST_CONTRACT_AUX_CLASS_HAS_EVAL_BASE_(c) 1

// TODO: Expand 0 if contracts disabled...
#define BOOST_CONTRACT_AUX_CLASS_HAS_TYPEDEFS_(c) 1

#define BOOST_CONTRACT_AUX_CLASS_EVAL_BASE_(c) \
    boost::contract::aux::eval<BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_NAME(c)>

#define BOOST_CONTRACT_AUX_CLASS_BASE_(r, has_extra_bases, i, b) \
    BOOST_PP_IIF(has_extra_bases, \
        BOOST_PP_COMMA \
    , BOOST_PP_IF(i, \
        BOOST_PP_COMMA \
    , \
        : BOOST_PP_EMPTY \
    ))() \
    BOOST_CONTRACT_EXT_PP_BASE_TRAITS_ACCESS(b) \
    BOOST_CONTRACT_EXT_PP_BASE_TRAITS_VIRTUAL(b) \
    BOOST_PP_TUPLE_REM_CTOR(BOOST_CONTRACT_EXT_PP_BASE_TRAITS_TYPE(b))

#define BOOST_CONTRACT_AUX_CLASS_BASE_TYPEDEF_(r, unused, i, b) \
    typedef BOOST_PP_TUPLE_REM_CTOR(BOOST_CONTRACT_EXT_PP_BASE_TRAITS_TYPE(b)) \
            BOOST_CONTRACT_AUX_CLASS_BASE_TYPE(i);

#define BOOST_CONTRACT_AUX_CLASS_TYPEDEFS_(d, r, id, tpl, c) \
    { \
        typedef BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_NAME(c) \
                BOOST_CONTRACT_AUX_CLASS_TYPE; \
        typedef BOOST_CONTRACT_AUX_CLASS_EVAL_BASE_(c) \
                BOOST_CONTRACT_AUX_CLASS_EVAL_BASE_TYPE; \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
                BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_BASES(c)), \
            BOOST_PP_TUPLE_EAT(2) \
        , \
            BOOST_PP_SEQ_FOR_EACH_I_R \
        )(r, BOOST_CONTRACT_AUX_CLASS_BASE_TYPEDEF_, ~, \
                BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_BASES(c)) \
    class BOOST_CONTRACT_AUX_NAME1(ERROR_missing_class_invariant)

#endif // #include guard

