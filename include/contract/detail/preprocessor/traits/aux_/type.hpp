
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_DETAIL_PP_TRAITS_AUX_TYPE_HPP_
#define CONTRACT_DETAIL_PP_TRAITS_AUX_TYPE_HPP_

#include <contract/detail/preprocessor/traits/aux_/comma.hpp>
#include <contract/detail/preprocessor/punctuation/has_paren.hpp>
#include <contract/detail/preprocessor/keyword/void.hpp>
#include <contract/detail/preprocessor/keyword/bool.hpp>
#include <contract/detail/preprocessor/keyword/char.hpp>
#include <contract/detail/preprocessor/keyword/double.hpp>
#include <contract/detail/preprocessor/keyword/float.hpp>
#include <contract/detail/preprocessor/keyword/int.hpp>
#include <contract/detail/preprocessor/keyword/wchar_t.hpp>
#include <contract/detail/preprocessor/keyword/cstddef/size_t.hpp>
#include <contract/detail/preprocessor/keyword/cstddef/ptrdiff_t.hpp>
#include <contract/detail/preprocessor/keyword/const.hpp>
#include <contract/detail/preprocessor/keyword/volatile.hpp>
#include <contract/detail/preprocessor/keyword/long.hpp>
#include <contract/detail/preprocessor/keyword/short.hpp>
#include <contract/detail/preprocessor/keyword/signed.hpp>
#include <contract/detail/preprocessor/keyword/unsigned.hpp>
#include <contract/detail/preprocessor/keyword/int.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/control/while.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/facilities/expand.hpp>
#include <boost/preprocessor/seq/for_each.hpp>

// PRIVATE //

#define CONTRACT_DETAIL_PP_TRAITS_AUX_TYPE_KEYWORD_NEXT_(type_tokens, \
        type_elem, next_macro) \
    ( \
        BOOST_PP_TUPLE_ELEM(2, 0, type_tokens) (type_elem) /* make a seq */ \
    , \
        next_macro(BOOST_PP_TUPLE_ELEM(2, 1, type_tokens)) \
    )

#define CONTRACT_DETAIL_PP_TRAITS_AUX_TYPE_KEYWORD_SKIP_(type_tokens, \
        unused0, unused1) \
    type_tokens

#define CONTRACT_DETAIL_PP_TRAITS_AUX_TYPE_KEYWORD_APPLY3_(macro, \
        arg0, arg1, arg2) \
    macro(arg0, arg1, arg2)

#define CONTRACT_DETAIL_PP_TRAITS_AUX_TYPE_KEYWORD_IS_(is_macro, tokens) \
    /* allows any paren (), (a), (a, b), etc to be within tokens (variadics) */\
    BOOST_PP_IIF(CONTRACT_DETAIL_PP_HAS_PAREN(tokens), \
        0 BOOST_PP_TUPLE_EAT(1) \
    , \
        is_macro \
    )(tokens)

#define CONTRACT_DETAIL_PP_TRAITS_AUX_TYPE_KEYWORD_FUNDAMENTAL_TYPE_( \
        type_tokens) \
    CONTRACT_DETAIL_PP_TRAITS_AUX_TYPE_KEYWORD_APPLY3_ \
    BOOST_PP_IIF(CONTRACT_DETAIL_PP_TRAITS_AUX_TYPE_KEYWORD_IS_( \
            CONTRACT_DETAIL_PP_KEYWORD_IS_VOID_FRONT, \
            BOOST_PP_TUPLE_ELEM(2, 1, type_tokens)), \
        (CONTRACT_DETAIL_PP_TRAITS_AUX_TYPE_KEYWORD_NEXT_, type_tokens, \
         void, CONTRACT_DETAIL_PP_KEYWORD_VOID_REMOVE_FRONT) \
    , BOOST_PP_IIF(CONTRACT_DETAIL_PP_TRAITS_AUX_TYPE_KEYWORD_IS_( \
            CONTRACT_DETAIL_PP_KEYWORD_IS_BOOL_FRONT, \
            BOOST_PP_TUPLE_ELEM(2, 1, type_tokens)), \
        (CONTRACT_DETAIL_PP_TRAITS_AUX_TYPE_KEYWORD_NEXT_, type_tokens, \
         bool, CONTRACT_DETAIL_PP_KEYWORD_BOOL_REMOVE_FRONT) \
    , BOOST_PP_IIF(CONTRACT_DETAIL_PP_TRAITS_AUX_TYPE_KEYWORD_IS_( \
            CONTRACT_DETAIL_PP_KEYWORD_IS_CHAR_FRONT, \
            BOOST_PP_TUPLE_ELEM(2, 1, type_tokens)), \
        (CONTRACT_DETAIL_PP_TRAITS_AUX_TYPE_KEYWORD_NEXT_, type_tokens, \
         char, CONTRACT_DETAIL_PP_KEYWORD_CHAR_REMOVE_FRONT) \
    , BOOST_PP_IIF(CONTRACT_DETAIL_PP_TRAITS_AUX_TYPE_KEYWORD_IS_( \
            CONTRACT_DETAIL_PP_KEYWORD_IS_DOUBLE_FRONT, \
            BOOST_PP_TUPLE_ELEM(2, 1, type_tokens)), \
        (CONTRACT_DETAIL_PP_TRAITS_AUX_TYPE_KEYWORD_NEXT_, type_tokens, \
         double, CONTRACT_DETAIL_PP_KEYWORD_DOUBLE_REMOVE_FRONT) \
    , BOOST_PP_IIF(CONTRACT_DETAIL_PP_TRAITS_AUX_TYPE_KEYWORD_IS_( \
            CONTRACT_DETAIL_PP_KEYWORD_IS_FLOAT_FRONT, \
            BOOST_PP_TUPLE_ELEM(2, 1, type_tokens)), \
        (CONTRACT_DETAIL_PP_TRAITS_AUX_TYPE_KEYWORD_NEXT_, type_tokens, \
         float, CONTRACT_DETAIL_PP_KEYWORD_FLOAT_REMOVE_FRONT) \
    , BOOST_PP_IIF(CONTRACT_DETAIL_PP_TRAITS_AUX_TYPE_KEYWORD_IS_( \
            CONTRACT_DETAIL_PP_KEYWORD_IS_INT_FRONT, \
            BOOST_PP_TUPLE_ELEM(2, 1, type_tokens)), \
        (CONTRACT_DETAIL_PP_TRAITS_AUX_TYPE_KEYWORD_NEXT_, type_tokens, \
         int, CONTRACT_DETAIL_PP_KEYWORD_INT_REMOVE_FRONT) \
    , BOOST_PP_IIF(CONTRACT_DETAIL_PP_TRAITS_AUX_TYPE_KEYWORD_IS_( \
            CONTRACT_DETAIL_PP_KEYWORD_IS_WCHAR_T_FRONT, \
            BOOST_PP_TUPLE_ELEM(2, 1, type_tokens)), \
        (CONTRACT_DETAIL_PP_TRAITS_AUX_TYPE_KEYWORD_NEXT_, type_tokens, \
         wchar_t, CONTRACT_DETAIL_PP_KEYWORD_WCHAR_T_REMOVE_FRONT) \
    , BOOST_PP_IIF(CONTRACT_DETAIL_PP_TRAITS_AUX_TYPE_KEYWORD_IS_( \
            CONTRACT_DETAIL_PP_KEYWORD_IS_SIZE_T_FRONT, \
            BOOST_PP_TUPLE_ELEM(2, 1, type_tokens)), \
        (CONTRACT_DETAIL_PP_TRAITS_AUX_TYPE_KEYWORD_NEXT_, type_tokens, \
         size_t, CONTRACT_DETAIL_PP_KEYWORD_SIZE_T_REMOVE_FRONT) \
    , BOOST_PP_IIF(CONTRACT_DETAIL_PP_TRAITS_AUX_TYPE_KEYWORD_IS_( \
            CONTRACT_DETAIL_PP_KEYWORD_IS_PTRDIFF_T_FRONT, \
            BOOST_PP_TUPLE_ELEM(2, 1, type_tokens)), \
        (CONTRACT_DETAIL_PP_TRAITS_AUX_TYPE_KEYWORD_NEXT_, type_tokens, \
         ptrdiff_t, CONTRACT_DETAIL_PP_KEYWORD_PTRDIFF_T_REMOVE_FRONT) \
    , \
        (CONTRACT_DETAIL_PP_TRAITS_AUX_TYPE_KEYWORD_SKIP_, type_tokens, ~, ~) \
    )))))))))

#define CONTRACT_DETAIL_PP_TRAITS_AUX_TYPE_KEYWORD_QUALIFIER_OP_( \
        d, type_tokens) \
    CONTRACT_DETAIL_PP_TRAITS_AUX_TYPE_KEYWORD_APPLY3_ \
    BOOST_PP_IIF(CONTRACT_DETAIL_PP_TRAITS_AUX_TYPE_KEYWORD_IS_( \
            CONTRACT_DETAIL_PP_KEYWORD_IS_CONST_FRONT, \
            BOOST_PP_TUPLE_ELEM(2, 1, type_tokens)), \
        (CONTRACT_DETAIL_PP_TRAITS_AUX_TYPE_KEYWORD_NEXT_, type_tokens, \
         const, CONTRACT_DETAIL_PP_KEYWORD_CONST_REMOVE_FRONT) \
    , BOOST_PP_IIF(CONTRACT_DETAIL_PP_TRAITS_AUX_TYPE_KEYWORD_IS_( \
            CONTRACT_DETAIL_PP_KEYWORD_IS_VOLATILE_FRONT, \
            BOOST_PP_TUPLE_ELEM(2, 1, type_tokens)), \
        (CONTRACT_DETAIL_PP_TRAITS_AUX_TYPE_KEYWORD_NEXT_, type_tokens, \
         volatile, CONTRACT_DETAIL_PP_KEYWORD_VOLATILE_REMOVE_FRONT) \
    , BOOST_PP_IIF(CONTRACT_DETAIL_PP_TRAITS_AUX_TYPE_KEYWORD_IS_( \
            CONTRACT_DETAIL_PP_KEYWORD_IS_LONG_FRONT, \
            BOOST_PP_TUPLE_ELEM(2, 1, type_tokens)), \
        (CONTRACT_DETAIL_PP_TRAITS_AUX_TYPE_KEYWORD_NEXT_, type_tokens, \
         long, CONTRACT_DETAIL_PP_KEYWORD_LONG_REMOVE_FRONT) \
    , BOOST_PP_IIF(CONTRACT_DETAIL_PP_TRAITS_AUX_TYPE_KEYWORD_IS_( \
            CONTRACT_DETAIL_PP_KEYWORD_IS_SHORT_FRONT, \
            BOOST_PP_TUPLE_ELEM(2, 1, type_tokens)), \
        (CONTRACT_DETAIL_PP_TRAITS_AUX_TYPE_KEYWORD_NEXT_, type_tokens, \
         short, CONTRACT_DETAIL_PP_KEYWORD_SHORT_REMOVE_FRONT) \
    , BOOST_PP_IIF(CONTRACT_DETAIL_PP_TRAITS_AUX_TYPE_KEYWORD_IS_( \
            CONTRACT_DETAIL_PP_KEYWORD_IS_SIGNED_FRONT, \
            BOOST_PP_TUPLE_ELEM(2, 1, type_tokens)), \
        (CONTRACT_DETAIL_PP_TRAITS_AUX_TYPE_KEYWORD_NEXT_, type_tokens, \
         signed, CONTRACT_DETAIL_PP_KEYWORD_SIGNED_REMOVE_FRONT) \
    , BOOST_PP_IIF(CONTRACT_DETAIL_PP_TRAITS_AUX_TYPE_KEYWORD_IS_( \
            CONTRACT_DETAIL_PP_KEYWORD_IS_UNSIGNED_FRONT, \
            BOOST_PP_TUPLE_ELEM(2, 1, type_tokens)), \
        (CONTRACT_DETAIL_PP_TRAITS_AUX_TYPE_KEYWORD_NEXT_, type_tokens, \
         unsigned, CONTRACT_DETAIL_PP_KEYWORD_UNSIGNED_REMOVE_FRONT) \
    , \
        (CONTRACT_DETAIL_PP_TRAITS_AUX_TYPE_KEYWORD_SKIP_, type_tokens, ~, ~) \
    ))))))

#define CONTRACT_DETAIL_PP_TRAITS_AUX_TYPE_KEYWORD_QUALIFIER_PRED_( \
        d, type_tokens) \
    BOOST_PP_IIF(CONTRACT_DETAIL_PP_TRAITS_AUX_TYPE_KEYWORD_IS_( \
            CONTRACT_DETAIL_PP_KEYWORD_IS_CONST_FRONT, \
            BOOST_PP_TUPLE_ELEM(2, 1, type_tokens)), \
        1 \
    , BOOST_PP_IIF(CONTRACT_DETAIL_PP_TRAITS_AUX_TYPE_KEYWORD_IS_( \
            CONTRACT_DETAIL_PP_KEYWORD_IS_VOLATILE_FRONT, \
            BOOST_PP_TUPLE_ELEM(2, 1, type_tokens)), \
        1 \
    , BOOST_PP_IIF(CONTRACT_DETAIL_PP_TRAITS_AUX_TYPE_KEYWORD_IS_( \
            CONTRACT_DETAIL_PP_KEYWORD_IS_LONG_FRONT, \
            BOOST_PP_TUPLE_ELEM(2, 1, type_tokens)), \
        1 \
    , BOOST_PP_IIF(CONTRACT_DETAIL_PP_TRAITS_AUX_TYPE_KEYWORD_IS_( \
            CONTRACT_DETAIL_PP_KEYWORD_IS_SHORT_FRONT, \
            BOOST_PP_TUPLE_ELEM(2, 1, type_tokens)), \
        1 \
    , BOOST_PP_IIF(CONTRACT_DETAIL_PP_TRAITS_AUX_TYPE_KEYWORD_IS_( \
            CONTRACT_DETAIL_PP_KEYWORD_IS_SIGNED_FRONT, \
            BOOST_PP_TUPLE_ELEM(2, 1, type_tokens)), \
        1 \
    , BOOST_PP_IIF(CONTRACT_DETAIL_PP_TRAITS_AUX_TYPE_KEYWORD_IS_( \
            CONTRACT_DETAIL_PP_KEYWORD_IS_UNSIGNED_FRONT, \
            BOOST_PP_TUPLE_ELEM(2, 1, type_tokens)), \
        1 \
    , \
        0 \
    ))))))

#define CONTRACT_DETAIL_PP_TRAITS_AUX_TYPE_KEYWORD_QUALIFIER_(type_tokens) \
    BOOST_PP_WHILE(CONTRACT_DETAIL_PP_TRAITS_AUX_TYPE_KEYWORD_QUALIFIER_PRED_, \
            CONTRACT_DETAIL_PP_TRAITS_AUX_TYPE_KEYWORD_QUALIFIER_OP_, \
            type_tokens)

#define CONTRACT_DETAIL_PP_TRAITS_AUX_TYPE_KEYWORD_(tokens, after01) \
    BOOST_PP_TUPLE_ELEM(2, after01, \
    CONTRACT_DETAIL_PP_TRAITS_AUX_TYPE_KEYWORD_QUALIFIER_( \
    CONTRACT_DETAIL_PP_TRAITS_AUX_TYPE_KEYWORD_FUNDAMENTAL_TYPE_( \
    CONTRACT_DETAIL_PP_TRAITS_AUX_TYPE_KEYWORD_QUALIFIER_( \
        (BOOST_PP_EMPTY(), tokens) \
    ))))

#define CONTRACT_DETAIL_PP_TRAITS_AUX_TYPE_SEQ_UNWRAP_(r, unused, type_bit) \
    type_bit /* remove seq paren */

#define CONTRACT_DETAIL_PP_TRAITS_AUX_TYPE_(tokens) \
    BOOST_PP_SEQ_FOR_EACH(CONTRACT_DETAIL_PP_TRAITS_AUX_TYPE_SEQ_UNWRAP_, ~, \
            CONTRACT_DETAIL_PP_TRAITS_AUX_TYPE_SEQ(tokens))

// Expand `(type) ...` or `keyword_type ...` to their remaining tokens `...`.
#define CONTRACT_DETAIL_PP_TRAITS_AUX_AFTER_TYPE_(tokens) \
    CONTRACT_DETAIL_PP_TRAITS_AUX_TYPE_KEYWORD_( \
            tokens, 1 /* after, not current */)

// PROTECTED //

// Expand `(type) ...` to `type` (any set of tokens in `type` also `void`) or
// `keyword_type ...` to `keyword_type` (no extra parenthesis) where:
//  qualifiers_:
//      [const] [volatile] [long] [short] [signed] [unsigned]
//  fundamental_type_:
//      void | bool | char | double | float | int | wchar_t | size_t | ptrdiff_t
//  keyword_type_:
//      qualifiers_ fundamental_type_ qualifiers_
// (Note that both `(void)` and `void` are also allowed.)
#define CONTRACT_DETAIL_PP_TRAITS_AUX_TYPE_SEQ(tokens) \
    CONTRACT_DETAIL_PP_TRAITS_AUX_TYPE_KEYWORD_( \
            tokens, 0 /* current, not after */)

#define CONTRACT_DETAIL_PP_TRAITS_AUX_TYPE(tokens) \
    CONTRACT_DETAIL_PP_TRAITS_AUX_COMMA( \
            CONTRACT_DETAIL_PP_TRAITS_AUX_TYPE_, tokens)

#define CONTRACT_DETAIL_PP_TRAITS_AUX_AFTER_TYPE(tokens) \
    CONTRACT_DETAIL_PP_TRAITS_AUX_AFTER_COMMA( \
            CONTRACT_DETAIL_PP_TRAITS_AUX_AFTER_TYPE_, tokens)

#endif // #include guard

