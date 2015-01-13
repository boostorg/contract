
#ifndef BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD_COMB_HPP_
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD_COMB_HPP_

#include <boost/preprocessor/control/iif.hpp>

/* PRIVATE */

// Precondition: sign = `keyword1 ...`.
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD2_COMB_1_( \
    sign,  \
    is_keyword1_macro, remove_keyword1_macro, \
    is_keyword2_macro, remove_keyword2_macro \
) \
    (remove_keyword1_macro(sign), (1, 0))

// Precondition: sign = `keyword2 ...`.
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD2_COMB_2_( \
    sign,  \
    is_keyword1_macro, remove_keyword1_macro, \
    is_keyword2_macro, remove_keyword2_macro \
) \
    (remove_keyword2_macro(sign), (0, 1))

// Precondition: sign = `keyword1 keyword2 ...`.
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD2_COMB_1_2_( \
    sign,  \
    is_keyword1_macro, remove_keyword1_macro, \
    is_keyword2_macro, remove_keyword2_macro \
) \
    (remove_keyword2_macro(remove_keyword1_macro(sign)), (1, 1))

// Precondition: sign = `keyword2 keyword1 ...`.
// NOTE: When both keywords are present `(1, 1)` is returned regardless of which
// keyword came first (e.g., this is OK because `const volatile` and
// `volatile const` are completely equivalent declarations in C++).
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD2_COMB_2_1_( \
    sign,  \
    is_keyword1_macro, remove_keyword1_macro, \
    is_keyword2_macro, remove_keyword2_macro \
) \
    (remove_keyword1_macro(remove_keyword2_macro(sign)), (1, 1))

// Precondition: sign = `...`.
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD2_COMB_NONE_( \
    sign,  \
    is_keyword1_macro, remove_keyword1_macro, \
    is_keyword2_macro, remove_keyword2_macro \
) \
    (sign, (0, 0))
        
// Precondition: sign = `keyword2 ...`
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD2_COMB_2_YES_( \
    sign,  \
    is_keyword1_macro, remove_keyword1_macro, \
    is_keyword2_macro, remove_keyword2_macro \
) \
    BOOST_PP_IIF(is_keyword1_macro(remove_keyword2_macro(sign)), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD2_COMB_2_1_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD2_COMB_2_ \
    )( \
        sign, \
        is_keyword1_macro, remove_keyword1_macro, \
        is_keyword2_macro, remove_keyword2_macro \
    )
        
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD2_COMB_1_NO_( \
    sign,  \
    is_keyword1_macro, remove_keyword1_macro, \
    is_keyword2_macro, remove_keyword2_macro \
) \
    BOOST_PP_IIF(is_keyword2_macro(sign), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD2_COMB_2_YES_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD2_COMB_NONE_ \
    )( \
        sign, \
        is_keyword1_macro, remove_keyword1_macro, \
        is_keyword2_macro, remove_keyword2_macro \
    )
    
// Precondition: sign = `keyword1 ...`.
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD2_COMB_1_YES_( \
    sign,  \
    is_keyword1_macro, remove_keyword1_macro, \
    is_keyword2_macro, remove_keyword2_macro \
) \
    BOOST_PP_IIF(is_keyword2_macro(remove_keyword1_macro(sign)), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD2_COMB_1_2_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD2_COMB_1_ \
    )( \
        sign, \
        is_keyword1_macro, remove_keyword1_macro, \
        is_keyword2_macro, remove_keyword2_macro \
    )

/* PUBLIC */

// TODO: Maybe the trais/aux_ macro should not say PARSE, SKIP, etc and they
// should always be implemented to parse both sign and traits together (because
// this is in general more efficient).

// Expand to `(remaining-sign, (k1, k2))` based on following combinations:
//  k1 = 1 and k2 = 0 when sign = `keyword1 ...`.
//  k1 = 0 and k2 = 1 when sign = `keyword2 ...`.
//  k1 = 1 and k2 = 1 when sign = `keyword1 keyword2 ...`
//                      or sign = `keyword2 keyword1 ...`.
//  k1 = 0 and k2 = 0 when sign = `...`.
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD2_COMB_PARSE( \
    sign,  \
    is_keyword1_macro, remove_keyword1_macro, \
    is_keyword2_macro, remove_keyword2_macro \
) \
    BOOST_PP_IIF(is_keyword1_macro(sign), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD2_COMB_1_YES_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD2_COMB_1_NO_ \
    )( \
        sign, \
        is_keyword1_macro, remove_keyword1_macro, \
        is_keyword2_macro, remove_keyword2_macro \
    )

#endif // #include guard

