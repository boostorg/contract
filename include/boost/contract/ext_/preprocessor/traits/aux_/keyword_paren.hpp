
#ifndef BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD_PAREN_HPP_
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD_PAREN_HPP_

#include <boost/contract/ext_/preprocessor/paren/front.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/tuple/rem.hpp>

/* PRIVATE */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD_PAREN_( \
        tokens, remove_keyword_macro) \
    BOOST_CONTRACT_EXT_PP_PAREN_FRONT(remove_keyword_macro(tokens))

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD_PAREN_SKIP_( \
        tokens, remove_keyword_macro) \
    BOOST_PP_TUPLE_EAT(0) remove_keyword_macro(tokens)

/* PUBLIC */
    
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD_PAREN( \
        tokens, is_keyword_macro, remove_keyword_macro) \
    BOOST_PP_IIF(is_keyword_macro(tokens), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD_PAREN_ \
    , \
        BOOST_PP_TUPLE_EAT(2) \
    )(tokens, remove_keyword_macro)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD_PAREN_SKIP( \
        tokens, is_keyword_macro, remove_keyword_macro) \
    BOOST_PP_IIF(is_keyword_macro(tokens), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD_PAREN_SKIP_ \
    , \
        tokens BOOST_PP_TUPLE_EAT(2) \
    )(tokens, remove_keyword_macro)

#endif // #include guard

