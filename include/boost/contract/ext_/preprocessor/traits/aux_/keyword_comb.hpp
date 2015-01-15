
#ifndef BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD_COMB_HPP_
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD_COMB_HPP_

#include <boost/preprocessor/control/iif.hpp>

/* PRIVATE */

// Precondition: decl = `keyword1 ...`.
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD2_COMB_1_( \
    decl,  \
    is_keyword1_macro, remove_keyword1_macro, \
    is_keyword2_macro, remove_keyword2_macro \
) \
    (remove_keyword1_macro(decl), (1, 0))

// Precondition: decl = `keyword2 ...`.
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD2_COMB_2_( \
    decl,  \
    is_keyword1_macro, remove_keyword1_macro, \
    is_keyword2_macro, remove_keyword2_macro \
) \
    (remove_keyword2_macro(decl), (0, 1))

// Precondition: decl = `keyword1 keyword2 ...`.
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD2_COMB_1_2_( \
    decl,  \
    is_keyword1_macro, remove_keyword1_macro, \
    is_keyword2_macro, remove_keyword2_macro \
) \
    (remove_keyword2_macro(remove_keyword1_macro(decl)), (1, 1))

// Precondition: decl = `keyword2 keyword1 ...`.
// This produces `(1, 1)` as case above (so it cannot be diff. from case above).
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD2_COMB_2_1_( \
    decl,  \
    is_keyword1_macro, remove_keyword1_macro, \
    is_keyword2_macro, remove_keyword2_macro \
) \
    (remove_keyword1_macro(remove_keyword2_macro(decl)), (1, 1))

// Precondition: decl = `...`.
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD2_COMB_NONE_( \
    decl,  \
    is_keyword1_macro, remove_keyword1_macro, \
    is_keyword2_macro, remove_keyword2_macro \
) \
    (decl, (0, 0))
        
// Precondition: decl = `keyword2 ...`
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD2_COMB_2_YES_( \
    decl,  \
    is_keyword1_macro, remove_keyword1_macro, \
    is_keyword2_macro, remove_keyword2_macro \
) \
    BOOST_PP_IIF(is_keyword1_macro(remove_keyword2_macro(decl)), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD2_COMB_2_1_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD2_COMB_2_ \
    )( \
        decl, \
        is_keyword1_macro, remove_keyword1_macro, \
        is_keyword2_macro, remove_keyword2_macro \
    )
        
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD2_COMB_1_NO_( \
    decl,  \
    is_keyword1_macro, remove_keyword1_macro, \
    is_keyword2_macro, remove_keyword2_macro \
) \
    BOOST_PP_IIF(is_keyword2_macro(decl), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD2_COMB_2_YES_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD2_COMB_NONE_ \
    )( \
        decl, \
        is_keyword1_macro, remove_keyword1_macro, \
        is_keyword2_macro, remove_keyword2_macro \
    )
    
// Precondition: decl = `keyword1 ...`.
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD2_COMB_1_YES_( \
    decl,  \
    is_keyword1_macro, remove_keyword1_macro, \
    is_keyword2_macro, remove_keyword2_macro \
) \
    BOOST_PP_IIF(is_keyword2_macro(remove_keyword1_macro(decl)), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD2_COMB_1_2_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD2_COMB_1_ \
    )( \
        decl, \
        is_keyword1_macro, remove_keyword1_macro, \
        is_keyword2_macro, remove_keyword2_macro \
    )

/* PUBLIC */

// Expand:
//  decl = `keyword1 ...`           to `(..., (1, 0))`.
//  decl = `keyword2 ...`           to `(..., (0, 1))`.
//  decl = `keyword1 keyword2 ...`  to `(..., (1, 1))`.
//  decl = `keyword2 keyword1 ...`  to `(..., (1, 1))`.
//  decl = `...`                    to `(..., (0, 0))`.
// NOTE: There is no distinction between decl = `keyword1 keyword2 ...` and
// decl = `keyword2 keyword1 ...` as they both expand to trait `(1, 1)` (e.g.,
// this is OK because in C++ `const volatile` and `volatile const` are both
// allowed syntactically but they represent the same thing semantically so
// there is no need to differentiate them).
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD2_COMB( \
    decl,  \
    is_keyword1_macro, remove_keyword1_macro, \
    is_keyword2_macro, remove_keyword2_macro \
) \
    BOOST_PP_IIF(is_keyword1_macro(decl), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD2_COMB_1_YES_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD2_COMB_1_NO_ \
    )( \
        decl, \
        is_keyword1_macro, remove_keyword1_macro, \
        is_keyword2_macro, remove_keyword2_macro \
    )

#endif // #include guard

