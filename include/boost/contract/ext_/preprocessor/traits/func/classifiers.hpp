
#ifndef BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_CLASSIFIERS_HPP_
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_CLASSIFIERS_HPP_

#include <boost/contract/ext_/preprocessor/traits/adt.hpp>
#include <boost/contract/ext_/preprocessor/keyword/inline.hpp>
#include <boost/contract/ext_/preprocessor/keyword/static.hpp>
#include <boost/contract/ext_/preprocessor/keyword/extern.hpp>
#include <boost/contract/ext_/preprocessor/keyword/explicit.hpp>
#include <boost/contract/ext_/preprocessor/keyword/virtual.hpp>
#include <boost/contract/ext_/preprocessor/keyword/friend.hpp>
#include <boost/contract/ext_/preprocessor/keyword/inline.hpp>
#include <boost/contract/ext_/preprocessor/utility/expand.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/control/while.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/control/expr_iif.hpp>
#include <boost/preprocessor/logical/bitand.hpp>
#include <boost/preprocessor/logical/compl.hpp>
#include <boost/preprocessor/facilities/empty.hpp>

// Function classifiers `inline static extern explicit virtual friend` can in
// general appear in any order (so they are parsed together here).

/* PRIVATE */

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_CLASSIFIERS_SIGN_( \
        continue_, sign_macro, sign, inline_, static_, extern_, explicit_, \
        virtual_, friend_) \
    (continue_, sign_macro(sign), inline_, static_, extern_, explicit_, \
            virtual_, friend_)

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_CLASSIFIERS_OP_ARGS_(continue_, \
        sign, inline_, static_, extern_, explicit_, virtual_, friend_) \
    BOOST_CONTRACT_EXT_PP_EXPAND1( \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_CLASSIFIERS_SIGN_ \
        BOOST_PP_IIF(BOOST_PP_BITAND(BOOST_PP_COMPL(inline_), \
                BOOST_CONTRACT_EXT_PP_KEYWORD_IS_INLINE_FRONT(sign)), \
            (1, BOOST_CONTRACT_EXT_PP_KEYWORD_INLINE_REMOVE_FRONT, sign, \
            1, static_, extern_, explicit_, virtual_, friend_) \
        , BOOST_PP_IIF(BOOST_PP_BITAND(BOOST_PP_COMPL(static_), \
                BOOST_CONTRACT_EXT_PP_KEYWORD_IS_STATIC_FRONT(sign)), \
            (1, BOOST_CONTRACT_EXT_PP_KEYWORD_STATIC_REMOVE_FRONT, sign, \
            inline_, 1, extern_, explicit_, virtual_, friend_) \
        , BOOST_PP_IIF(BOOST_PP_BITAND(BOOST_PP_COMPL(extern_), \
                BOOST_CONTRACT_EXT_PP_KEYWORD_IS_EXTERN_FRONT(sign)), \
            (1, BOOST_CONTRACT_EXT_PP_KEYWORD_EXTERN_REMOVE_FRONT, sign, \
            inline_, static_, 1, explicit_, virtual_, friend_) \
        , BOOST_PP_IIF(BOOST_PP_BITAND(BOOST_PP_COMPL(explicit_), \
                BOOST_CONTRACT_EXT_PP_KEYWORD_IS_EXPLICIT_FRONT(sign)), \
            (1, BOOST_CONTRACT_EXT_PP_KEYWORD_EXPLICIT_REMOVE_FRONT, sign, \
            inline_, static_, extern_, 1, virtual_, friend_) \
        , BOOST_PP_IIF(BOOST_PP_BITAND(BOOST_PP_COMPL(virtual_), \
                BOOST_CONTRACT_EXT_PP_KEYWORD_IS_VIRTUAL_FRONT(sign)), \
            (1, BOOST_CONTRACT_EXT_PP_KEYWORD_VIRTUAL_REMOVE_FRONT, sign, \
            inline_, static_, extern_, explicit_, 1, friend_) \
        , BOOST_PP_IIF(BOOST_PP_BITAND(BOOST_PP_COMPL(friend_), \
                BOOST_CONTRACT_EXT_PP_KEYWORD_IS_FRIEND_FRONT(sign)), \
            (1, BOOST_CONTRACT_EXT_PP_KEYWORD_FRIEND_REMOVE_FRONT, sign, \
            inline_, static_, extern_, explicit_, virtual_, 1) \
        , \
            (0, BOOST_CONTRACT_EXT_PP_EXPAND1, sign, \
            inline_, static_, extern_, explicit_, virtual_, friend_) \
        )))))) \
    )
        
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_CLASSIFIERS_OP_( \
        d, continue_sign_inline_static_extern_explicit_virtual_friend) \
    BOOST_CONTRACT_EXT_PP_EXPAND1( \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_CLASSIFIERS_OP_ARGS_ \
        continue_sign_inline_static_extern_explicit_virtual_friend \
    )

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_CLASSIFIERS_PRED_( \
        d, continue_sign_inline_static_extern_explicit_virtual_friend) \
    BOOST_PP_TUPLE_ELEM(8, 0, \
            continue_sign_inline_static_extern_explicit_virtual_friend)

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_CLASSIFIERS_RETURN_ARGS_( \
        sign, traits, inline_, static_, extern_, explicit_, virtual_, friend_) \
    ( \
        sign \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            traits, \
            BOOST_PP_EXPR_IIF(inline_, inline) BOOST_PP_EMPTY), \
            BOOST_PP_EXPR_IIF(static_, static) BOOST_PP_EMPTY), \
            BOOST_PP_EXPR_IIF(extern_, extern) BOOST_PP_EMPTY), \
            BOOST_PP_EXPR_IIF(explicit_, explicit) BOOST_PP_EMPTY), \
            BOOST_PP_EXPR_IIF(virtual_, virtual) BOOST_PP_EMPTY), \
            BOOST_PP_EXPR_IIF(friend_, friend) BOOST_PP_EMPTY \
        ) \
    )

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_CLASSIFIERS_RETURN_( \
        traits, continue_sign_inline_static_extern_explicit_virtual_friend) \
    BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_CLASSIFIERS_RETURN_ARGS_( \
        BOOST_PP_TUPLE_ELEM(8, 1, \
                continue_sign_inline_static_extern_explicit_virtual_friend), \
        traits, \
        BOOST_PP_TUPLE_ELEM(8, 2, \
                continue_sign_inline_static_extern_explicit_virtual_friend), \
        BOOST_PP_TUPLE_ELEM(8, 3, \
                continue_sign_inline_static_extern_explicit_virtual_friend), \
        BOOST_PP_TUPLE_ELEM(8, 4, \
                continue_sign_inline_static_extern_explicit_virtual_friend), \
        BOOST_PP_TUPLE_ELEM(8, 5, \
                continue_sign_inline_static_extern_explicit_virtual_friend), \
        BOOST_PP_TUPLE_ELEM(8, 6, \
                continue_sign_inline_static_extern_explicit_virtual_friend), \
        BOOST_PP_TUPLE_ELEM(8, 7, \
                continue_sign_inline_static_extern_explicit_virtual_friend) \
    )

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_CLASSIFIERS_PRASE_(d, sign, traits) \
    BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_CLASSIFIERS_RETURN_( \
        traits, \
        BOOST_PP_WHILE_ ## d( \
            BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_CLASSIFIERS_PRED_, \
            BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_CLASSIFIERS_OP_, \
            (1, sign, 0, 0, 0, 0, 0, 0) \
        ) \
    )

/* PUBLIC */

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_CLASSIFIERS_PARSE_D(d, sign_traits) \
    BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_CLASSIFIERS_PRASE_( \
        d, \
        BOOST_PP_TUPLE_ELEM(2, 0, sign_traits), \
        BOOST_PP_TUPLE_ELEM(2, 1, sign_traits) \
    )

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_CLASSIFIERS_PARSE(sign_traits) \
    BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_CLASSIFIERS_PARSE_D(1, sign_traits)

// Expand to `inline | EMPTY()`.
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_INLINE(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_ELEM( \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_INLINE_INDEX, \
        traits \
    )()

// Expand to `static | EMPTY()`.
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_STATIC(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_ELEM( \
            BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_STATIC_INDEX, traits)()

// Expand to `extern | EMPTY()`.
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_EXTERN(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_ELEM( \
            BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_EXTERN_INDEX, traits)()

// Expand to `explicit | EMPTY()`.
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_EXPLICIT(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_ELEM( \
            BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_EXPLICIT_INDEX, traits)()

// Expand to `virtual | EMPTY()`.
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_VIRTUAL(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_ELEM( \
            BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_VIRTUAL_INDEX, traits)()

// Expand to `friend | EMPTY()`.
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_FRIEND(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_ELEM( \
            BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_FRIEND_INDEX, traits)()

#endif // #include guard

