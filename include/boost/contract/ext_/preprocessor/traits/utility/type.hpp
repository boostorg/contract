
#ifndef BOOST_CONTRACT_EXT_PP_TYPE_TRAITS_HPP_
#define BOOST_CONTRACT_EXT_PP_TYPE_TRAITS_HPP_

#include <boost/contract/ext_/preprocessor/traits/utility/traits.hpp>
#include <boost/contract/ext_/preprocessor/keyword/auto.hpp>
#include <boost/contract/ext_/preprocessor/keyword/register.hpp>
#include <boost/contract/ext_/preprocessor/keyword/const.hpp>
#include <boost/contract/ext_/preprocessor/keyword/volatile.hpp>
#include <boost/contract/ext_/preprocessor/keyword/long.hpp>
#include <boost/contract/ext_/preprocessor/keyword/short.hpp>
#include <boost/contract/ext_/preprocessor/keyword/signed.hpp>
#include <boost/contract/ext_/preprocessor/keyword/unsigned.hpp>
#include <boost/contract/ext_/preprocessor/keyword/void.hpp>
#include <boost/contract/ext_/preprocessor/keyword/bool.hpp>
#include <boost/contract/ext_/preprocessor/keyword/char.hpp>
#include <boost/contract/ext_/preprocessor/keyword/char16_t.hpp>
#include <boost/contract/ext_/preprocessor/keyword/char32_t.hpp>
#include <boost/contract/ext_/preprocessor/keyword/int.hpp>
#include <boost/contract/ext_/preprocessor/keyword/wchar_t.hpp>
#include <boost/contract/ext_/preprocessor/keyword/float.hpp>
#include <boost/contract/ext_/preprocessor/keyword/double.hpp>
#include <boost/contract/ext_/preprocessor/keyword/decltype.hpp>
#include <boost/contract/ext_/preprocessor/paren/has.hpp>
#include <boost/contract/ext_/preprocessor/paren/front.hpp>
#include <boost/contract/ext_/preprocessor/utility/nil.hpp>
#include <boost/contract/ext_/preprocessor/utility/nil.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/control/while.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/facilities/expand.hpp>

/* PUBLIC */

// Expand decl = `[type | (type)] ...` (type can also be `void`) to
// `(..., (type) | ())`.
// For example, `int const ...` to `(..., (int const))`.
// Precondition: `...` in decl cannot be EMPTY() (so expanded 2-tuple is valid).
#define BOOST_CONTRACT_EXT_PP_TYPE_TRAITS_PARSE_D(d, decl) \
    BOOST_CONTRACT_EXT_PP_TYPE_TRAITS_D_(d, decl, \
            BOOST_CONTRACT_EXT_PP_TYPE_TRAITS_SPACED_PUSH_BACK_)

// Expand decl = `[auto | type | (type)] ...` (type can also be `void`) to
// `(..., auto | (type) | ())` (note that auto is not wrapped in parenthesis).
// For example, `auto ...` to `(..., auto)`.
// Precondition: `...` in decl cannot be EMPTY() (so expanded 2-tuple is valid).
// NOTE: So far, there is no need of a SEQ version of this macro.
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUTO_TYPE_PARSE_D(d, decl) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_AUTO_FRONT( \
            decl), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUTO_TYPE_ \
    , \
        BOOST_CONTRACT_EXT_PP_TYPE_TRAITS_PARSE_D \
    )(d, decl)

// Expand decl = `[type | (type)] ...` (type can also be `void`) to
// `(..., ((keyword1))...((keyword-n)) | (()))`.
// For example, `int const ...` to `(..., ((int)) ((const)))` (useful to access
// single type keywords `int`, `const`, etc.).
// Precondition: `...` in decl cannot be EMPTY() (so expanded 2-tuple is valid).
#define BOOST_CONTRACT_EXT_PP_TYPE_TRAITS_SEQ_PARSE_D(d, decl) \
    BOOST_CONTRACT_EXT_PP_TYPE_TRAITS_SEQ_RETURN_( \
        BOOST_CONTRACT_EXT_PP_TYPE_TRAITS_D_(d, decl, \
                BOOST_CONTRACT_EXT_PP_TYPE_TRAITS_SEQ_PUSH_BACK_) \
    )

/* PRIVATE */

#define BOOST_CONTRACT_EXT_PP_TYPE_TRAITS_SPACED_PUSH_BACK_( \
        spaced_type, trait) \
    spaced_type trait

#define BOOST_CONTRACT_EXT_PP_TYPE_TRAITS_SEQ_PUSH_BACK_( \
        type_seq, trait) \
    type_seq ((trait))

// Precondition: decl = `auto ...`.
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUTO_TYPE_(unused, decl) \
    (BOOST_CONTRACT_EXT_PP_KEYWORD_AUTO_REMOVE_FRONT(decl), auto)

// Extra level of indirection needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_TYPE_TRAITS_SEQ_RETURN_(decl_type) \
    BOOST_PP_EXPAND(BOOST_CONTRACT_EXT_PP_TYPE_TRAITS_SEQ_RETURN_ARGS_ \
            decl_type)

// Remove an extra set of parenthesis around sequence (originally added to
// handle commas by algorithms in common with spaced type traits).
// Implementation: Always return `(())` (double paren seq with 1 empty elem) in
// case no type was parsed.
#define BOOST_CONTRACT_EXT_PP_TYPE_TRAITS_SEQ_RETURN_ARGS_( \
        decl, type) \
    ( \
        decl, \
        BOOST_PP_EXPR_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY type, \
            (()) \
        ) \
        BOOST_PP_TUPLE_REM_CTOR(1, type) \
    )

#define BOOST_CONTRACT_EXT_PP_TYPE_TRAITS_D_( \
        d, decl, push_back_macro) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(decl), \
        BOOST_CONTRACT_EXT_PP_TYPE_TRAITS_PAREN_D_ \
    , \
        BOOST_CONTRACT_EXT_PP_TYPE_TRAITS_KEYWORD_D_ \
    )(d, decl, push_back_macro)

// Precondition: decl = `(...) ...`.
#define BOOST_CONTRACT_EXT_PP_TYPE_TRAITS_PAREN_D_(d, decl, push_back_macro) \
    ( \
        BOOST_PP_TUPLE_EAT(0) decl, \
        push_back_macro(BOOST_PP_EMPTY(), \
                BOOST_CONTRACT_EXT_PP_PAREN_FRONT(decl)) \
    )

// Precondition: decl does not start with paren (it's formed by keywords).
#define BOOST_CONTRACT_EXT_PP_TYPE_TRAITS_KEYWORD_D_( \
        d, decl, push_back_macro) \
    BOOST_CONTRACT_EXT_PP_TYPE_TRAITS_KEYWORD_RETURN_( \
        BOOST_PP_WHILE_ ## d( \
            BOOST_CONTRACT_EXT_PP_TYPE_TRAITS_KEYWORD_PRED_, \
            BOOST_CONTRACT_EXT_PP_TYPE_TRAITS_KEYWORD_OP_, \
            (1, decl, BOOST_PP_NIL, push_back_macro) \
        ) \
    )

// Do not return continue_ and wrap type in paren (so same as paren type).
#define BOOST_CONTRACT_EXT_PP_TYPE_TRAITS_KEYWORD_RETURN_( \
        continue_decl_type_push) \
    ( \
        BOOST_PP_TUPLE_ELEM(4, 1, continue_decl_type_push), \
        ( BOOST_CONTRACT_EXT_PP_NIL_REMOVE_FRONT( \
                BOOST_PP_TUPLE_ELEM(4, 2, continue_decl_type_push)) ) \
    )

#define BOOST_CONTRACT_EXT_PP_TYPE_TRAITS_KEYWORD_PRED_( \
        d, continue_decl_type_push) \
    BOOST_PP_TUPLE_ELEM(4, 0, continue_decl_type_push)

#define BOOST_CONTRACT_EXT_PP_TYPE_TRAITS_KEYWORD_OP_( \
        d, continue_decl_type_push) \
    BOOST_CONTRACT_EXT_PP_TYPE_TRAITS_KEYWORD_OP_ARGS_(d, \
        BOOST_PP_TUPLE_ELEM(4, 1, continue_decl_type_push), \
        BOOST_PP_TUPLE_ELEM(4, 2, continue_decl_type_push), \
        BOOST_PP_TUPLE_ELEM(4, 3, continue_decl_type_push) \
    )

#define BOOST_CONTRACT_EXT_PP_TYPE_TRAITS_KEYWORD_OP_ARGS_( \
        d, decl, type, push_back_macro) \
    BOOST_CONTRACT_EXT_PP_TYPE_TRAITS_KEYWORD_( \
        d, \
        decl, \
        type, \
        push_back_macro, \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_AUTO_FRONT(decl), \
            (BOOST_CONTRACT_EXT_PP_TYPE_TRAITS_KEYWORD_TRAIT_, \
            auto, BOOST_CONTRACT_EXT_PP_KEYWORD_AUTO_REMOVE_FRONT) \
        , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_REGISTER_FRONT(decl), \
            (BOOST_CONTRACT_EXT_PP_TYPE_TRAITS_KEYWORD_TRAIT_, \
            register, BOOST_CONTRACT_EXT_PP_KEYWORD_REGISTER_REMOVE_FRONT) \
        , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \
            (BOOST_CONTRACT_EXT_PP_TYPE_TRAITS_KEYWORD_TRAIT_, \
            const, BOOST_CONTRACT_EXT_PP_KEYWORD_CONST_REMOVE_FRONT) \
        , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_VOLATILE_FRONT(decl), \
            (BOOST_CONTRACT_EXT_PP_TYPE_TRAITS_KEYWORD_TRAIT_, \
            volatile, BOOST_CONTRACT_EXT_PP_KEYWORD_VOLATILE_REMOVE_FRONT) \
        , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_LONG_FRONT(decl), \
            (BOOST_CONTRACT_EXT_PP_TYPE_TRAITS_KEYWORD_TRAIT_, \
            long, BOOST_CONTRACT_EXT_PP_KEYWORD_LONG_REMOVE_FRONT) \
        , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_SHORT_FRONT(decl), \
            (BOOST_CONTRACT_EXT_PP_TYPE_TRAITS_KEYWORD_TRAIT_, \
            short, BOOST_CONTRACT_EXT_PP_KEYWORD_SHORT_REMOVE_FRONT) \
        , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_SIGNED_FRONT(decl), \
            (BOOST_CONTRACT_EXT_PP_TYPE_TRAITS_KEYWORD_TRAIT_, \
            signed, BOOST_CONTRACT_EXT_PP_KEYWORD_SIGNED_REMOVE_FRONT) \
        , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_UNSIGNED_FRONT(decl), \
            (BOOST_CONTRACT_EXT_PP_TYPE_TRAITS_KEYWORD_TRAIT_, \
            unsigned, BOOST_CONTRACT_EXT_PP_KEYWORD_UNSIGNED_REMOVE_FRONT) \
        , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_VOID_FRONT(decl), \
            (BOOST_CONTRACT_EXT_PP_TYPE_TRAITS_KEYWORD_TRAIT_, \
            void, BOOST_CONTRACT_EXT_PP_KEYWORD_VOID_REMOVE_FRONT) \
        , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_BOOL_FRONT(decl), \
            (BOOST_CONTRACT_EXT_PP_TYPE_TRAITS_KEYWORD_TRAIT_, \
            bool, BOOST_CONTRACT_EXT_PP_KEYWORD_BOOL_REMOVE_FRONT) \
        , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CHAR_FRONT(decl), \
            (BOOST_CONTRACT_EXT_PP_TYPE_TRAITS_KEYWORD_TRAIT_, \
            char, BOOST_CONTRACT_EXT_PP_KEYWORD_CHAR_REMOVE_FRONT) \
        , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CHAR16_T_FRONT(decl), \
            (BOOST_CONTRACT_EXT_PP_TYPE_TRAITS_KEYWORD_TRAIT_, \
            char16_t, BOOST_CONTRACT_EXT_PP_KEYWORD_CHAR16_T_REMOVE_FRONT) \
        , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CHAR32_T_FRONT(decl), \
            (BOOST_CONTRACT_EXT_PP_TYPE_TRAITS_KEYWORD_TRAIT_, \
            char32_t, BOOST_CONTRACT_EXT_PP_KEYWORD_CHAR32_T_REMOVE_FRONT) \
        , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_WCHAR_T_FRONT(decl), \
            (BOOST_CONTRACT_EXT_PP_TYPE_TRAITS_KEYWORD_TRAIT_, \
            wchar_t, BOOST_CONTRACT_EXT_PP_KEYWORD_WCHAR_T_REMOVE_FRONT) \
        , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_INT_FRONT(decl), \
            (BOOST_CONTRACT_EXT_PP_TYPE_TRAITS_KEYWORD_TRAIT_, \
            int, BOOST_CONTRACT_EXT_PP_KEYWORD_INT_REMOVE_FRONT) \
        , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_FLOAT_FRONT(decl), \
            (BOOST_CONTRACT_EXT_PP_TYPE_TRAITS_KEYWORD_TRAIT_, \
            float, BOOST_CONTRACT_EXT_PP_KEYWORD_FLOAT_REMOVE_FRONT) \
        , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_DOUBLE_FRONT(decl), \
            (BOOST_CONTRACT_EXT_PP_TYPE_TRAITS_KEYWORD_TRAIT_, \
            double, BOOST_CONTRACT_EXT_PP_KEYWORD_DOUBLE_REMOVE_FRONT) \
        , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_DECLTYPE_FRONT(decl), \
            (BOOST_CONTRACT_EXT_PP_TYPE_TRAITS_KEYWORD_PAREN_, \
            decltype, BOOST_CONTRACT_EXT_PP_KEYWORD_DECLTYPE_REMOVE_FRONT) \
        , \
            (BOOST_CONTRACT_EXT_PP_TYPE_TRAITS_KEYWORD_DONE_, ~, ~) \
        )))))))))))))))))) \
    )

#define BOOST_CONTRACT_EXT_PP_TYPE_TRAITS_KEYWORD_( \
        d, decl, type, push_back_macro, invoke_trait_remove) \
    BOOST_PP_TUPLE_ELEM(3, 0, invoke_trait_remove)(d, \
        decl, \
        type, \
        push_back_macro, \
        BOOST_PP_TUPLE_ELEM(3, 1, invoke_trait_remove), \
        BOOST_PP_TUPLE_ELEM(3, 2, invoke_trait_remove) \
    )

// Expand to (continue_ = 0, decl, type, push_back_macro).
#define BOOST_CONTRACT_EXT_PP_TYPE_TRAITS_KEYWORD_DONE_( \
        d, decl, type, push_back_macro, unused1, unused2) \
    (0, decl, type, push_back_macro)
    
// Expand to (continue_ = 1, remaining_decl, parsed_type, push_back_macro).
#define BOOST_CONTRACT_EXT_PP_TYPE_TRAITS_KEYWORD_TRAIT_( \
        d, decl, type, push_back_macro, trait, remove_macro) \
    (1, remove_macro(decl), push_back_macro(type, trait), push_back_macro)

// Expand to (continue_ = 1, remaining_decl, parsed_type, push_back_macro).
// Precondition: decl = `trait(...) ...` (e.g., for `decltype(...) ...`).
#define BOOST_CONTRACT_EXT_PP_TYPE_TRAITS_KEYWORD_PAREN_( \
        d, decl, type, push_back_macro, trait, remove_macro) \
    ( \
        1, \
        BOOST_PP_TUPLE_EAT(0) remove_macro(decl), \
        push_back_macro(type, trait \
                BOOST_CONTRACT_EXT_PP_PAREN_FRONT(remove_macro(decl))), \
        push_back_macro \
    )

// TODO: Consider returning EMPTY in case no type is parsed...

#endif // #include guard

