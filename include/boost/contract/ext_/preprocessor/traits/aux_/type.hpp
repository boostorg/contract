
#ifndef BOOST_CONTRACT_EXT_PP_TRAITS_AUX_TYPE_HPP_
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_TYPE_HPP_

#include <boost/contract/ext_/preprocessor/traits/adt.hpp>
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

/* PRIVATE */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_TYPE_SEQ_PUSH_BACK_( \
        type_seq, trait) \
    type_seq ((trait))

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_TYPE_SPACED_PUSH_BACK_( \
        spaced_type, trait) \
    spaced_type trait

// Expand to (continue_ = 1, remaining_tokens, parsed_type, push_back_macro).
// Precondition: tokens = `trait(...) ...` (e.g., for `decltype(...) ...`).
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_TYPE_KEYWORD_PAREN_( \
        d, tokens, type, push_back_macro, trait, remove_macro) \
    ( \
        1 \
    , \
        BOOST_PP_TUPLE_EAT(0) remove_macro(tokens) \
    , \
        push_back_macro(type, \
                trait BOOST_CONTRACT_EXT_PP_PAREN_FRONT(remove_macro(tokens))) \
    , \
        push_back_macro \
    )

// Expand to (continue_ = 1, remaining-tokens, parsed-type, push_back_macro).
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_TYPE_KEYWORD_TRAIT_( \
        d, tokens, type, push_back_macro, trait, remove_macro) \
    (1, remove_macro(tokens), push_back_macro(type, trait), push_back_macro)

// Expand to (continue_ = 0, tokens, type, push_back_macro).
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_TYPE_KEYWORD_DONE_( \
        d, tokens, type, push_back_macro, unused1, unused2) \
    (0, tokens, type, push_back_macro)
    
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_TYPE_KEYWORD_INVOKE_( \
        d, tokens, type, push_back_macro, invoke_trait_remove) \
    BOOST_PP_TUPLE_ELEM(3, 0, invoke_trait_remove)( \
        d, \
        tokens, \
        type, \
        push_back_macro, \
        BOOST_PP_TUPLE_ELEM(3, 1, invoke_trait_remove), \
        BOOST_PP_TUPLE_ELEM(3, 2, invoke_trait_remove) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_TYPE_KEYWORD_OP_ARGS_( \
        d, tokens, type, push_back_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_TYPE_KEYWORD_INVOKE_( \
        d, \
        tokens, \
        type, \
        push_back_macro, \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_AUTO_FRONT(tokens), \
            (BOOST_CONTRACT_EXT_PP_TRAITS_AUX_TYPE_KEYWORD_TRAIT_, \
            auto, BOOST_CONTRACT_EXT_PP_KEYWORD_AUTO_REMOVE_FRONT) \
        , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_REGISTER_FRONT(tokens),\
            (BOOST_CONTRACT_EXT_PP_TRAITS_AUX_TYPE_KEYWORD_TRAIT_, \
            register, BOOST_CONTRACT_EXT_PP_KEYWORD_REGISTER_REMOVE_FRONT) \
        , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(tokens), \
            (BOOST_CONTRACT_EXT_PP_TRAITS_AUX_TYPE_KEYWORD_TRAIT_, \
            const, BOOST_CONTRACT_EXT_PP_KEYWORD_CONST_REMOVE_FRONT) \
        , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_VOLATILE_FRONT(tokens),\
            (BOOST_CONTRACT_EXT_PP_TRAITS_AUX_TYPE_KEYWORD_TRAIT_, \
            volatile, BOOST_CONTRACT_EXT_PP_KEYWORD_VOLATILE_REMOVE_FRONT) \
        , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_LONG_FRONT(tokens), \
            (BOOST_CONTRACT_EXT_PP_TRAITS_AUX_TYPE_KEYWORD_TRAIT_, \
            long, BOOST_CONTRACT_EXT_PP_KEYWORD_LONG_REMOVE_FRONT) \
        , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_SHORT_FRONT(tokens), \
            (BOOST_CONTRACT_EXT_PP_TRAITS_AUX_TYPE_KEYWORD_TRAIT_, \
            short, BOOST_CONTRACT_EXT_PP_KEYWORD_SHORT_REMOVE_FRONT) \
        , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_SIGNED_FRONT(tokens), \
            (BOOST_CONTRACT_EXT_PP_TRAITS_AUX_TYPE_KEYWORD_TRAIT_, \
            signed, BOOST_CONTRACT_EXT_PP_KEYWORD_SIGNED_REMOVE_FRONT) \
        , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_UNSIGNED_FRONT(tokens),\
            (BOOST_CONTRACT_EXT_PP_TRAITS_AUX_TYPE_KEYWORD_TRAIT_, \
            unsigned, BOOST_CONTRACT_EXT_PP_KEYWORD_UNSIGNED_REMOVE_FRONT) \
        , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_VOID_FRONT(tokens), \
            (BOOST_CONTRACT_EXT_PP_TRAITS_AUX_TYPE_KEYWORD_TRAIT_, \
            void, BOOST_CONTRACT_EXT_PP_KEYWORD_VOID_REMOVE_FRONT) \
        , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_BOOL_FRONT(tokens), \
            (BOOST_CONTRACT_EXT_PP_TRAITS_AUX_TYPE_KEYWORD_TRAIT_, \
            bool, BOOST_CONTRACT_EXT_PP_KEYWORD_BOOL_REMOVE_FRONT) \
        , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CHAR_FRONT(tokens), \
            (BOOST_CONTRACT_EXT_PP_TRAITS_AUX_TYPE_KEYWORD_TRAIT_, \
            char, BOOST_CONTRACT_EXT_PP_KEYWORD_CHAR_REMOVE_FRONT) \
        , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CHAR16_T_FRONT(tokens),\
            (BOOST_CONTRACT_EXT_PP_TRAITS_AUX_TYPE_KEYWORD_TRAIT_, \
            char16_t, BOOST_CONTRACT_EXT_PP_KEYWORD_CHAR16_T_REMOVE_FRONT) \
        , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CHAR32_T_FRONT(tokens),\
            (BOOST_CONTRACT_EXT_PP_TRAITS_AUX_TYPE_KEYWORD_TRAIT_, \
            char32_t, BOOST_CONTRACT_EXT_PP_KEYWORD_CHAR32_T_REMOVE_FRONT) \
        , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_WCHAR_T_FRONT(tokens), \
            (BOOST_CONTRACT_EXT_PP_TRAITS_AUX_TYPE_KEYWORD_TRAIT_, \
            wchar_t, BOOST_CONTRACT_EXT_PP_KEYWORD_WCHAR_T_REMOVE_FRONT) \
        , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_INT_FRONT(tokens), \
            (BOOST_CONTRACT_EXT_PP_TRAITS_AUX_TYPE_KEYWORD_TRAIT_, \
            int, BOOST_CONTRACT_EXT_PP_KEYWORD_INT_REMOVE_FRONT) \
        , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_FLOAT_FRONT(tokens), \
            (BOOST_CONTRACT_EXT_PP_TRAITS_AUX_TYPE_KEYWORD_TRAIT_, \
            float, BOOST_CONTRACT_EXT_PP_KEYWORD_FLOAT_REMOVE_FRONT) \
        , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_DOUBLE_FRONT(tokens), \
            (BOOST_CONTRACT_EXT_PP_TRAITS_AUX_TYPE_KEYWORD_TRAIT_, \
            double, BOOST_CONTRACT_EXT_PP_KEYWORD_DOUBLE_REMOVE_FRONT) \
        , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_DECLTYPE_FRONT(tokens),\
            (BOOST_CONTRACT_EXT_PP_TRAITS_AUX_TYPE_KEYWORD_PAREN_, \
            decltype, BOOST_CONTRACT_EXT_PP_KEYWORD_DECLTYPE_REMOVE_FRONT) \
        , \
            (BOOST_CONTRACT_EXT_PP_TRAITS_AUX_TYPE_KEYWORD_DONE_, ~, ~) \
        )))))))))))))))))) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_TYPE_KEYWORD_OP_( \
        d, continue_tokens_type_push) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_TYPE_KEYWORD_OP_ARGS_( \
        d, \
        BOOST_PP_TUPLE_ELEM(4, 1, continue_tokens_type_push), \
        BOOST_PP_TUPLE_ELEM(4, 2, continue_tokens_type_push), \
        BOOST_PP_TUPLE_ELEM(4, 3, continue_tokens_type_push) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_TYPE_KEYWORD_PRED_( \
        d, continue_tokens_type_push) \
    BOOST_PP_TUPLE_ELEM(4, 0, continue_tokens_type_push)

// Do not return continue_ and wrap type in paren (so same as paren type).
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_TYPE_KEYWORD_RETURN_( \
        continue_tokens_type_push) \
    ( \
        BOOST_PP_TUPLE_ELEM(4, 1, continue_tokens_type_push), \
        ( BOOST_CONTRACT_EXT_PP_NIL_REMOVE_FRONT( \
                BOOST_PP_TUPLE_ELEM(4, 2, continue_tokens_type_push)) ) \
    )

// Precondition: tokens does not start with paren (it's formed by keywords).
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_TYPE_KEYWORD_D_( \
        d, tokens, push_back_macro) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_TYPE_KEYWORD_RETURN_( \
        BOOST_PP_WHILE_ ## d( \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_TYPE_KEYWORD_PRED_, \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_TYPE_KEYWORD_OP_, \
            (1, tokens, BOOST_PP_NIL, push_back_macro) \
        ) \
    )

// Precondition: tokens = `(...) ...`.
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_TYPE_PAREN_D_( \
        d, tokens, push_back_macro) \
    ( \
        BOOST_PP_TUPLE_EAT(0) tokens, \
        push_back_macro(BOOST_PP_EMPTY(), \
                BOOST_CONTRACT_EXT_PP_PAREN_FRONT(tokens)) \
    )

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_TYPE_PARSE_D_( \
        d, tokens, push_back_macro) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN(tokens), \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_TYPE_PAREN_D_ \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_TYPE_KEYWORD_D_ \
    )(d, tokens, push_back_macro)

// Remove an extra set of parenthesis around sequence (originally added to
// handle commas by algorithms in common with spaced tokens).
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_TYPE_PARSE_SEQ_RETURN_( \
        tokens, type) \
    (tokens, BOOST_PP_TUPLE_REM_CTOR(1, type))

/* PUBLIC */

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_TYPE_PARSE_D(d, tokens) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_TYPE_PARSE_D_(d, tokens, \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_TYPE_SPACED_PUSH_BACK_)

// Expand to 2-tuple `(remaining_tokens, parsed_type_spaced)`.
// Where parsed_type_spaced are space-separated type tokens (e.g.,
// `(int const)`, extra parenthesis to handle possible commas).
// NOTE: Use ..._SEQ macro below to access single tokens instead.
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_TYPE_PARSE(tokens) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_TYPE_PARSE_D(1, tokens)

#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_TYPE_PARSE_SEQ_D(d, tokens) \
    BOOST_CONTRACT_EXT_PP_EXPAND_ONCE( \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_TYPE_PARSE_SEQ_RETURN_ \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_TYPE_PARSE_D_(d, tokens, \
                BOOST_CONTRACT_EXT_PP_TRAITS_AUX_TYPE_SEQ_PUSH_BACK_) \
    )

// Expand to 2-tuple `(remaining_tokens, parsed_type_seq)`.
// Where parsed_type_seq is a double parenthesized sequence of type tokens
// (e.g., `((int)) ((const))`, extra parenthesis to handle possible commas).
// NOTE: It is more efficient to use the non-..._SEQ macros above when only a
// space-separated concatenation of the type tokes is needed.
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_TYPE_PARSE_SEQ(tokens) \
    BOOST_CONTRACT_EXT_PP_TRAITS_AUX_TYPE_PARSE_SEQ_D(1, tokens)

// TODO: Consider changing all/most tokens arg names to sign in pp/traits.

// TODO: Consider renaming all sign to decl.

// TODO: Should all _SKIP macros be removed and replaced by PARSE macros
// that work on both sign and traits at the same time for efficiency and
// consistency? Then maybe just remove the two macros below...

// NOTE: If possible, use the single "parse" macro above instead of this macro
// (so to avoid executing the implementation while-loop twice).
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_TYPE(tokens) \
    BOOST_CONTRACT_EXT_PP_SIGN_TRAITS_SECOND( \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_TYPE_PARSE(tokens))

// NOTE: If possible, use the single "parse" macro above instead of this macro
// (so to avoid executing the implementation while-loop twice).
#define BOOST_CONTRACT_EXT_PP_TRAITS_AUX_TYPE_SKIP(tokens) \
    BOOST_CONTRACT_EXT_PP_SIGN_TRAITS_FIRST( \
            BOOST_CONTRACT_EXT_PP_TRAITS_AUX_TYPE_PARSE(tokens))

#endif // #include guard

