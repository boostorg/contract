
# Copyright (C) 2008-2012 Lorenzo Caminiti
# Distributed under the Boost Software License, Version 1.0
# (see accompanying file LICENSE_1_0.txt or a copy at
# http://www.boost.org/LICENSE_1_0.txt)
# Home at http://sourceforge.net/projects/contractpp

import sys
import shutil

def data(max):
    s = ''
    for i in reversed(range(1, max)): # i == 0 handled separately (no `seq`).
        p = "_" + str(i)
        if i == max - 1:
            next_sign_macro = "ERROR_support_maximum_of_" + str(max) + \
                    "_old_value_declarations"
        else:
            next_sign_macro = \
                "CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITIONS_TRAIT_SIGN_" + \
                    str(i + 1) + "_"
        s = s + '''
#define CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITIONS_TRAIT_SIGN_NEXT{0}_( \\
        seq_sign) \\
    BOOST_PP_IIF(CONTRACT_DETAIL_PP_KEYWORD_IS_POSTCONDITION_FRONT( \\
            BOOST_PP_TUPLE_ELEM(2, 1, seq_sign)), \\
        {1} \\
    , BOOST_PP_IIF(CONTRACT_DETAIL_PP_HAS_PAREN( \\
            BOOST_PP_TUPLE_ELEM(2, 1, seq_sign)), \\
        {1} \\
    , \\
        seq_sign BOOST_PP_TUPLE_EAT(2) \\
    ))(BOOST_PP_TUPLE_ELEM(2, 0, seq_sign), BOOST_PP_TUPLE_ELEM(2, 1, seq_sign))
#define CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITIONS_TRAIT_SIGN{0}_( \\
        seq, sign) \\
    CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITIONS_TRAIT_SIGN_NEXT{0}_( ( \\
        seq \\
        BOOST_PP_IIF(CONTRACT_DETAIL_PP_HAS_PAREN(sign), \\
  CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITIONS_SPLIT_SEQ_postcondition \\
        , \\
            CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITIONS_SPLIT_SEQ_CAT_ \\
        )(sign) \\
    ) ) \
'''.format(p, next_sign_macro)
    return s

CONTRACT_LIMIT_OLDOFS = raw_input("CONTRACT_LIMIT_OLDOFS" +
        "from <contract/limits.hpp> [15] = ")
if CONTRACT_LIMIT_OLDOFS == "": CONTRACT_LIMIT_OLDOFS = 15
else: CONTRACT_LIMIT_OLDOFS = int(CONTRACT_LIMIT_OLDOFS)

header = sys.argv[0].replace("-generate.py", ".hpp", 1)
shutil.copyfile(header, header + ".bak")
h = open(header, 'w')

h.write('''
#ifndef CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITIONS_HPP_
#define CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITIONS_HPP_

// WARNING: FILE AUTOMATICALLY GENERATED, DO NOT MODIFY IT!
// Instead modify the generation script "<FILE>-generate.py" and run
// `$ python <FILE_NAME>-generate.py > FILE_NAME.hpp`.
// Used: #define CONTRACT_LIMIT_OLDOFS {0}

#include <contract/limits.hpp>
#if CONTRACT_LIMIT_OLDOFS != {0}
#error "Code generation used incorrect CONTRACT_LIMIT_OLDOFS"
#endif

// Old-of already parsed but header included here for user to access this trait.
#include <contract/detail/preprocessor/traits/oldof.hpp>

#include <contract/detail/preprocessor/traits/aux_/oldof.hpp>
#include <contract/detail/preprocessor/traits/aux_/type.hpp>
#include <contract/detail/preprocessor/traits/aux_/nil.hpp>
#include <contract/detail/preprocessor/traits/assertion.hpp>
#include <contract/detail/preprocessor/keyword/contract/postcondition.hpp>
#include <contract/detail/preprocessor/keyword/auto.hpp>
#include <contract/detail/preprocessor/variadic/to_seq.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/config/config.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/control/expr_iif.hpp>
#include <boost/preprocessor/logical/compl.hpp>
#include <boost/preprocessor/debug/assert.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/array/elem.hpp>
#include <boost/preprocessor/seq/fold_right.hpp>
#include <boost/preprocessor/list/append.hpp>
#include <boost/config.hpp>

// PRIVATE //

#define CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITIONS_OLDOF_TYPE_( \\
        oldof_typed_assignment) \\
    BOOST_PP_IIF(CONTRACT_DETAIL_PP_KEYWORD_IS_AUTO_FRONT( \\
            oldof_typed_assignment), \\
        /* 0-size array for no type (`auto` for typeof deduction) */ \\
        (0, ()) BOOST_PP_TUPLE_EAT(1) \\
    , \\
        CONTRACT_DETAIL_PP_TRAITS_AUX_TYPE \\
    )(oldof_typed_assignment)

#define CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITIONS_OLDOF_ASSIGNMENT_( \\
        oldof_typed_assignment) \\
    CONTRACT_DETAIL_PP_KEYWORD_AUTO_REMOVE_FRONT( \\
    CONTRACT_DETAIL_PP_TRAITS_AUX_AFTER_TYPE( \\
        oldof_typed_assignment \\
    ))
    
#define CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITIONS_OLDOF_TYPED_ASSIGNMENT_(\\
        s, result_oldofs_assertions_lastoldofexpr, oldof_typed_assignment) \\
    ( \\
        BOOST_PP_TUPLE_ELEM(4, 0, result_oldofs_assertions_lastoldofexpr) \\
    , \\
        BOOST_PP_LIST_APPEND( \\
            ( /* pp-list */ \\
                (3, ( /* oldof pp-array with `NIL type, var =, expr` */ \\
                    CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITIONS_OLDOF_TYPE_(\\
                            oldof_typed_assignment) \\
                , \\
            CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITIONS_OLDOF_ASSIGNMENT_( \\
                            oldof_typed_assignment) \\
                , \\
                    CONTRACT_DETAIL_PP_TRAITS_AUX_OLDOF_REMOVE_FRONT( \\
                            BOOST_PP_TUPLE_ELEM(4, 3, \\
                                    result_oldofs_assertions_lastoldofexpr)) \\
                ) ) \\
            , \\
                BOOST_PPNIL \\
            ) \\
            , BOOST_PP_TUPLE_ELEM(4, 1, \\
                    result_oldofs_assertions_lastoldofexpr)) \\
    , \\
        BOOST_PP_TUPLE_ELEM(4, 2, result_oldofs_assertions_lastoldofexpr) \\
    , \\
        CONTRACT_DETAIL_PP_TRAITS_AUX_NIL /* no open old-of expr */ \\
    )

#define CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITIONS_OLDOF_EXPR_( \\
        s, result_oldofs_assertions_lastoldofexpr, oldof_expr) \\
    ( \\
        BOOST_PP_TUPLE_ELEM(4, 0, result_oldofs_assertions_lastoldofexpr) \\
    , \\
        BOOST_PP_TUPLE_ELEM(4, 1, result_oldofs_assertions_lastoldofexpr) \\
    , \\
        BOOST_PP_TUPLE_ELEM(4, 2, result_oldofs_assertions_lastoldofexpr) \\
    , \\
        oldof_expr /* open an old-of expr (expect old-of assignment next) */ \\
    )

#define return_CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITIONS_STRIP_RETURN \\
    /* nothing */

#define CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITIONS_RESULT_ASSIGNMENT_( \\
        s, result_oldofs_assertions_lastoldofexpr, result_assignment) \\
    ( \\
        CONTRACT_DETAIL_PP_TRAITS_AUX_NIL /* optional trait */ \\
        /* LIMITATION: With this implementation, multiple result */ \\
        /* declarations override each other (instead of compiler error) */ \\
        CONTRACT_DETAIL_PP_KEYWORD_AUTO_REMOVE_FRONT(BOOST_PP_CAT( \\
                result_assignment, \\
                _CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITIONS_STRIP_RETURN)) \\
    , \\
        BOOST_PP_TUPLE_ELEM(4, 1, result_oldofs_assertions_lastoldofexpr) \\
    , \\
        BOOST_PP_TUPLE_ELEM(4, 2, result_oldofs_assertions_lastoldofexpr) \\
    , \\
        BOOST_PP_TUPLE_ELEM(4, 3, result_oldofs_assertions_lastoldofexpr) \\
    )

#define CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITIONS_ASSERTION_( \\
        s, result_oldofs_assertions_lastoldofexpr, assertion) \\
    ( \\
        BOOST_PP_TUPLE_ELEM(4, 0, result_oldofs_assertions_lastoldofexpr) \\
    , \\
        BOOST_PP_TUPLE_ELEM(4, 1, result_oldofs_assertions_lastoldofexpr) \\
    , \\
        BOOST_PP_LIST_APPEND( ( assertion, BOOST_PP_NIL ), \\
                BOOST_PP_TUPLE_ELEM(4, 2, \\
                result_oldofs_assertions_lastoldofexpr)) \\
    , \\
        BOOST_PP_TUPLE_ELEM(4, 3, result_oldofs_assertions_lastoldofexpr) \\
    )

#define CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITIONS_FROM_SEQ_OP_( \\
        s, result_oldofs_assertions_lastoldofexpr, elem) \\
    BOOST_PP_IIF(BOOST_PP_COMPL(CONTRACT_DETAIL_PP_TRAITS_AUX_IS_NIL( \\
            BOOST_PP_TUPLE_ELEM(4, 3, \\
            result_oldofs_assertions_lastoldofexpr))), \\
        /* prev there was an old-of expr so elem must be old-of assignment */\\
        CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITIONS_OLDOF_TYPED_ASSIGNMENT_ \\
    , BOOST_PP_IIF(CONTRACT_DETAIL_PP_TRAITS_AUX_IS_OLDOF_FRONT(elem), \\
        CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITIONS_OLDOF_EXPR_ \\
    , BOOST_PP_IIF(CONTRACT_DETAIL_PP_KEYWORD_IS_AUTO_FRONT(elem), \\
        CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITIONS_RESULT_ASSIGNMENT_ \\
    , /* else, it is an assertion */ \\
        CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITIONS_ASSERTION_ \\
    )))(s, result_oldofs_assertions_lastoldofexpr, elem)

#define CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITIONS_FROM_SEQ_3TUPLE_( \\
        result_oldofs_assertions_lastoldofexpr) \\
    ( /* after folding, ignore 4th elem `lastoldofexpr` */ \\
        BOOST_PP_TUPLE_ELEM(4, 0, result_oldofs_assertions_lastoldofexpr) \\
    , \\
        BOOST_PP_TUPLE_ELEM(4, 1, result_oldofs_assertions_lastoldofexpr) \\
    , \\
        BOOST_PP_TUPLE_ELEM(4, 2, result_oldofs_assertions_lastoldofexpr) \\
    )

#define CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITIONS_FROM_SEQ_(seq_sign) \\
    CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITIONS_FROM_SEQ_3TUPLE_( \\
        BOOST_PP_SEQ_FOLD_RIGHT( \\
            CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITIONS_FROM_SEQ_OP_, \\
            ( \\
                CONTRACT_DETAIL_PP_TRAITS_AUX_NIL /* no result */ \\
            , \\
                BOOST_PP_NIL /* no oldofs */ \\
            , \\
                BOOST_PP_NIL /* no assertions */ \\
            , \\
                CONTRACT_DETAIL_PP_TRAITS_AUX_NIL /* no last oldof expr */ \\
            ), \\
            BOOST_PP_TUPLE_ELEM(2, 0, seq_sign) \\
        ) \\
    )

// Adapted from PP_CAT (needed for reentrancy as CAT already used by VARIADIC).
#if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#   define CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITIONS_CAT_(a, b) \\
        CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITIONS_CAT_I_(a, b)
#else
#   define CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITIONS_CAT_(a, b) \\
        CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITIONS_CAT_OO_((a, b))
#   define CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITIONS_CAT_OO_(par) \\
        CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITIONS_CAT_I_ ## par
#endif
#if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MSVC()
#   define CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITIONS_CAT_I_(a, b) a ## b
#else
#   define CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITIONS_CAT_I_(a, b) \\
        CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITIONS_CAT_II_(a ## b)
#   define CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITIONS_CAT_II_(res) res
#endif

#define CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITIONS_SPLIT_SEQ_PAREN_(paren) \\
    CONTRACT_DETAIL_PP_TUPLE_SPLIT(1) paren
#ifndef BOOST_NO_VARIADIC_MACROS
#   include <contract/detail/preprocessor/variadic/to_seq.hpp>
#   define CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITIONS_SPLIT_SEQ_VARIADIC_( \\
            ...) \\
        CONTRACT_DETAIL_PP_VARIADIC_TO_SEQ(void, __VA_ARGS__) , /*comma split*/
#   define \\
    CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITIONS_SPLIT_SEQ_MAYBE_PAREN1_( \
            paren) \\
        BOOST_PP_IIF(CONTRACT_DETAIL_PP_KEYWORD_IS_POSTCONDITION_FRONT( \\
                CONTRACT_DETAIL_PP_VARIADIC_EAT paren), \\
            CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITIONS_SPLIT_SEQ_PAREN_ \\
        /* unfortunately this needs to know that initialize is next (needed */\\
        /* to handle typed old-of when no variadic macros) */ \\
        , BOOST_PP_IIF(CONTRACT_DETAIL_PP_KEYWORD_IS_INITIALIZE_FRONT( \\
                CONTRACT_DETAIL_PP_VARIADIC_EAT paren), \\
            CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITIONS_SPLIT_SEQ_PAREN_ \\
        , BOOST_PP_IIF(CONTRACT_DETAIL_PP_TRAITS_AUX_IS_NIL_FRONT( \\
                CONTRACT_DETAIL_PP_VARIADIC_EAT paren), \\
            CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITIONS_SPLIT_SEQ_PAREN_ \\
        , BOOST_PP_IIF(CONTRACT_DETAIL_PP_HAS_PAREN( \\
                CONTRACT_DETAIL_PP_VARIADIC_EAT paren), \\
            CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITIONS_SPLIT_SEQ_PAREN_ \\
        , \\
            CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITIONS_SPLIT_SEQ_VARIADIC_ \\
        ))))(paren)
#   define \\
    CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITIONS_SPLIT_SEQ_MAYBE_PAREN_( \\
            tokens) \\
        BOOST_PP_IIF(CONTRACT_DETAIL_PP_HAS_PAREN(tokens), \\
  CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITIONS_SPLIT_SEQ_MAYBE_PAREN1_ \\
        , \\
            CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITIONS_SPLIT_SEQ_VARIADIC_ \\
        )(tokens)
#   define \\
    CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITIONS_SPLIT_SEQ_postcondition(...)\\
        BOOST_PP_IIF(BOOST_PP_EQUAL(1, CONTRACT_DETAIL_PP_VARIADIC_SIZE( \\
                __VA_ARGS__)), \\
  CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITIONS_SPLIT_SEQ_MAYBE_PAREN_ \\
        , \\
            CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITIONS_SPLIT_SEQ_VARIADIC_ \\
        )(__VA_ARGS__)
#else
#   define CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITIONS_SPLIT_SEQ_TOKEN_( \\
            token) \\
        (token) , /* comma split */
#   define \\
    CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITIONS_SPLIT_SEQ_postcondition( \\
            tokens) \\
        BOOST_PP_IIF(CONTRACT_DETAIL_PP_HAS_PAREN(tokens), \\
            CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITIONS_SPLIT_SEQ_PAREN_ \\
        , \\
            CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITIONS_SPLIT_SEQ_TOKEN_ \\
        )(tokens)
#endif

// Precondition: sign is `postcondition(...)`.
#define CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITIONS_SPLIT_SEQ_CAT_(sign) \\
    CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITIONS_CAT_( \\
            CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITIONS_SPLIT_SEQ_, sign)
{1}

#define CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITIONS_TRAIT_SIGN_NEXT_( \\
        seq_sign) \\
    BOOST_PP_IIF(CONTRACT_DETAIL_PP_KEYWORD_IS_POSTCONDITION_FRONT( \\
            BOOST_PP_TUPLE_ELEM(2, 1, seq_sign)), \\
        CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITIONS_TRAIT_SIGN_1_ \\
    , BOOST_PP_IIF(CONTRACT_DETAIL_PP_HAS_PAREN( \\
            BOOST_PP_TUPLE_ELEM(2, 1, seq_sign)), \\
        CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITIONS_TRAIT_SIGN_1_ \\
    , \\
        seq_sign BOOST_PP_TUPLE_EAT(2) \\
    ))(BOOST_PP_TUPLE_ELEM(2, 0, seq_sign), BOOST_PP_TUPLE_ELEM(2, 1, seq_sign))
#define CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITIONS_TRAIT_SIGN_(sign) \\
    BOOST_PP_EXPAND( \\
    CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITIONS_TRAIT_SIGN_NEXT_( ( \\
        BOOST_PP_IIF(CONTRACT_DETAIL_PP_HAS_PAREN(sign), \\
  CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITIONS_SPLIT_SEQ_postcondition \\
        , \\
            CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITIONS_SPLIT_SEQ_CAT_ \\
        )(sign) \\
    ) ) )

#define CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITIONS_ASSERTION_LIST_( \\
        result_oldofs_assertions) \\
    ( \\
        BOOST_PP_TUPLE_ELEM(3, 0, result_oldofs_assertions) \\
    , \\
        BOOST_PP_TUPLE_ELEM(3, 1, result_oldofs_assertions) \\
    , \\
        CONTRACT_DETAIL_PP_ASSERTION_TRAITS(BOOST_PP_TUPLE_ELEM(3, 2, \\
                result_oldofs_assertions)) /* process assertion traits */ \\
    )

#define CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITIONS_LIST_(sign) \\
    CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITIONS_ASSERTION_LIST_( \\
    CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITIONS_FROM_SEQ_( \\
    CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITIONS_TRAIT_SIGN_( \\
        sign \\
    )))

#define CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITIONS_TRAIT_(sign) \\
    BOOST_PP_IIF(CONTRACT_DETAIL_PP_KEYWORD_IS_POSTCONDITION_FRONT(sign), \\
        CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITIONS_LIST_ \\
    , \\
        ( \\
            CONTRACT_DETAIL_PP_TRAITS_AUX_NIL /* no result */ \\
        , \\
            BOOST_PP_NIL /* no oldofs */ \\
        , \\
            BOOST_PP_NIL /* no assertions */ \\
        ) \\
        BOOST_PP_TUPLE_EAT(1) \\
    )(sign)

#define CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITIONS_REMOVE_(sign) \\
    BOOST_PP_TUPLE_ELEM(2, 1, BOOST_PP_EXPAND( \\
            CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITIONS_TRAIT_SIGN_(sign)))

#define CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITIONS_SIGN_(sign) \\
    BOOST_PP_IIF(CONTRACT_DETAIL_PP_KEYWORD_IS_POSTCONDITION_FRONT(sign), \\
        CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITIONS_REMOVE_ \\
    , \\
        sign BOOST_PP_TUPLE_EAT(1) \\
    )(sign)

// PROTECTED //

#define CONTRACT_DETAIL_PP_FUNC_TRAITS_AUX_POSTCONDITIONS(traits_sign) \\
    CONTRACT_DETAIL_PP_TRAITS_AUX_APPLY(traits_sign, \\
            CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITIONS_TRAIT_, \\
            CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITIONS_SIGN_)

// PUBLIC //

#define CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITION_RESULT_ASSIGNMENT( \\
        func_traits) \\
    BOOST_PP_CAT(CONTRACT_DETAIL_PP_TRAITS_AUX_NIL_REMOVE_, \\
            BOOST_PP_TUPLE_ELEM(3, 0, BOOST_PP_ARRAY_ELEM(21, func_traits)))

// Expand to pp-list of oldofs (see `OLDOF_TRAITS`).
#define CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITION_OLDOFS(func_traits) \\
    BOOST_PP_TUPLE_ELEM(3, 1, BOOST_PP_ARRAY_ELEM(21, func_traits))

// Expand to pp-list of postcondition assertions.
#define CONTRACT_DETAIL_PP_FUNC_TRAITS_POSTCONDITIONS(func_traits) \\
    BOOST_PP_TUPLE_ELEM(3, 2, BOOST_PP_ARRAY_ELEM(21, func_traits))

#endif // #include guard

'''.format(CONTRACT_LIMIT_OLDOFS, data(CONTRACT_LIMIT_OLDOFS)))

h.close()
print "Written:", header

