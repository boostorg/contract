
#ifndef BOOST_CONTRACT_BASE_TYPES_HPP_
#define BOOST_CONTRACT_BASE_TYPES_HPP_

#include <boost/preprocessor/config/config.hpp>
#if !BOOST_PP_VARIADICS
#   define BOOST_CONTRACT_BASE_TYPES ERROR_variadic_macros_required_by_BOOST_CONTRACT_BASE_TYPES_consider_programming_base_typedef_manually_without_this_macro
#else

#include <boost/contract/ext_/preprocessor/keyword/virtual.hpp>
#include <boost/contract/ext_/preprocessor/keyword/public.hpp>
#include <boost/contract/ext_/preprocessor/keyword/protected.hpp>
#include <boost/contract/ext_/preprocessor/keyword/private.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/preprocessor/variadic/to_seq.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>

/* PUBLIC */

// If no variadics macros, users have to manually program
// `typedef boost::mpl::vector<...> BOOST_CONTRACT_BASES`.
#define BOOST_CONTRACT_BASE_TYPES(...) \
    boost::mpl::vector< \
        BOOST_PP_SEQ_FOR_EACH_I(BOOST_CONTRACT_BASE_TYPES_, ~, \
                BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__)) \
    >

/* PRIVATE */

#define BOOST_CONTRACT_BASE_TYPES_(r, unused, i, base) \
    BOOST_PP_COMMA_IF(i) \
    BOOST_CONTRACT_BASE_TYPES_REMOVE_( \
            BOOST_CONTRACT_EXT_PP_KEYWORD_IS_VIRTUAL_FRONT, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_VIRTUAL_REMOVE_FRONT, \
    BOOST_CONTRACT_BASE_TYPES_REMOVE_( \
            BOOST_CONTRACT_EXT_PP_KEYWORD_IS_PUBLIC_FRONT, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_PUBLIC_REMOVE_FRONT, \
    BOOST_CONTRACT_BASE_TYPES_REMOVE_( \
            BOOST_CONTRACT_EXT_PP_KEYWORD_IS_PROTECTED_FRONT, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_PROTECTED_REMOVE_FRONT, \
    BOOST_CONTRACT_BASE_TYPES_REMOVE_( \
            BOOST_CONTRACT_EXT_PP_KEYWORD_IS_PRIVATE_FRONT, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_PRIVATE_REMOVE_FRONT, \
    BOOST_CONTRACT_BASE_TYPES_REMOVE_( \
            BOOST_CONTRACT_EXT_PP_KEYWORD_IS_VIRTUAL_FRONT, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_VIRTUAL_REMOVE_FRONT, \
        base \
    )))))

#define BOOST_CONTRACT_BASE_TYPES_REMOVE_(is_macro, remove_macro, tokens) \
    BOOST_PP_IIF(is_macro(tokens), remove_macro, BOOST_PP_TUPLE_REM(1))(tokens)

#endif // BOOST_PP_VARIADICS

#endif // #include guard

