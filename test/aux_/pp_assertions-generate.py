
import os
import sys

LIMIT = 64

def code():
    result = ''
    for n in range(1, LIMIT + 1):
        result = result + '''
/* PUBLIC ({0}) */

#define BOOST_CONTRACT_TEST_AUX_PP_ASSERTIONS_S_{0}( \\
        s, assertions, assertion_traits) \\
    BOOST_CONTRACT_TEST_AUX_PP_ASSERTIONS_S_{0}_(s, assertions, \\
        BOOST_CONTRACT_TEST_AUX_PP_ASSERTION_S_{0}_, assertion_traits)
    
#define BOOST_CONTRACT_TEST_AUX_PP_POST_ASSERTIONS_S_{0}( \\
        s, assertions, assertion_traits) \\
    BOOST_CONTRACT_TEST_AUX_PP_ASSERTIONS_S_{0}_(s, assertions, \\
        BOOST_CONTRACT_TEST_AUX_PP_POST_ASSERTION_S_{0}_, assertion_traits)

/* PRIVATE ({0}) */

#define BOOST_CONTRACT_TEST_AUX_PP_ASSERTIONS_S_{0}_( \\
        s, assertions, assertion_macro, assertion_traits) \\
    ( \\
        BOOST_PP_TUPLE_REM_CTOR(assertions) \\
        assertion_macro(s, assertion_traits) \\
    )

#define BOOST_CONTRACT_TEST_AUX_PP_ASSERTION_S_{0}_(s, traits) \\
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT( \\
            BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_KIND(traits)), \\
        BOOST_CONTRACT_TEST_AUX_PP_NAMESPACE_ASSERTION_S_{0}_ \\
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_USING_FRONT( \\
            BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_KIND(traits)), \\
        BOOST_CONTRACT_TEST_AUX_PP_USING_ASSERTION_S_{0}_ \\
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT( \\
            BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_KIND(traits)), \\
        BOOST_CONTRACT_TEST_AUX_PP_TYPEDEF_ASSERTION_S_{0}_ \\
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT( \\
            BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_KIND(traits)), \\
        BOOST_CONTRACT_TEST_AUX_PP_CONST_ASSERTION_S_{0}_ \\
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT( \\
            BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_KIND(traits)), \\
        BOOST_CONTRACT_TEST_AUX_PP_IF_ASSERTION_S_{0}_ \\
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS( \\
            BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_KIND(traits)), \\
        BOOST_CONTRACT_TEST_AUX_PP_STATIC_IF_ASSERTION_S_{0}_ \\
    , \\
        BOOST_CONTRACT_TEST_AUX_PP_BOOL_ASSERTION_S_{0}_ \\
    ))))))(s, traits)

#define BOOST_CONTRACT_TEST_AUX_PP_POST_ASSERTION_S_{0}_(s, traits) \\
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_RETURN_FRONT( \\
            BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_KIND(traits)), \\
        BOOST_CONTRACT_TEST_AUX_PP_RETURN_ASSERTION_S_{0}_ \\
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_IS( \\
            BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_KIND(traits)), \\
        BOOST_CONTRACT_TEST_AUX_PP_OLDOF_ASSERTION_S_{0}_ \\
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT( \\
            BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_KIND(traits)), \\
        BOOST_CONTRACT_TEST_AUX_PP_POST_IF_ASSERTION_S_{0}_ \\
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS( \\
            BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_KIND(traits)), \\
        BOOST_CONTRACT_TEST_AUX_PP_POST_STATIC_IF_ASSERTION_S_{0}_ \\
    , \\
        BOOST_CONTRACT_TEST_AUX_PP_ASSERTION_S_{0}_ \\
    ))))(s, traits)

#define BOOST_CONTRACT_TEST_AUX_PP_NAMESPACE_ASSERTION_S_{0}_(s, traits) \\
    namespace \\
    (BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_NEW_NAME(traits)) \\
    as BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_NAME(traits) \\
    ,

#define BOOST_CONTRACT_TEST_AUX_PP_USING_ASSERTION_S_{0}_(s, traits) \\
    BOOST_PP_EXPR_IIF( \\
        BOOST_PP_COMPL(BOOST_CONTRACT_EXT_PP_IS_EMPTY( \\
            BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_TEMPLATE_PARAMS( \\
                traits \\
            ) \\
        )) \\
    , \\
        template \\
    ) \\
    BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_TEMPLATE_PARAMS(traits) \\
    using \\
    BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_NAMESPACE(traits) \\
    BOOST_PP_EXPR_IIF(BOOST_PP_COMPL(BOOST_CONTRACT_EXT_PP_IS_EMPTY( \\
            BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_NEW_NAME(traits))), \\
        (BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_NEW_NAME(traits)) as \\
    ) \\
    BOOST_CONTRACT_TEST_AUX_PP_1TUPLE_REM( \\
            BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_NAME(traits)) \\
    ,

#define BOOST_CONTRACT_TEST_AUX_PP_TYPEDEF_ASSERTION_S_{0}_(s, traits) \\
    typedef \\
    BOOST_CONTRACT_TEST_AUX_PP_1TUPLE_REM( \\
            BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_NAME(traits)) \\
    BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_NEW_NAME(traits) \\
    ,
        
#define BOOST_CONTRACT_TEST_AUX_PP_CONST_ASSERTION_S_{0}_(s, traits) \\
    BOOST_CONTRACT_TEST_AUX_PP_CONST_ASSERTION_IMPL_S_{0}_(s, traits, 1)

#define BOOST_CONTRACT_TEST_AUX_PP_CONST_ASSERTION_IMPL_S_{0}_(s, traits, \\
        has_trailing_comma) \\
    const \\
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY( \\
            BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_CAPTURES(traits)), \\
        () BOOST_PP_TUPLE_EAT(3) \\
    , \\
        BOOST_PP_SEQ_FOLD_LEFT_ ## s \\
    )(BOOST_CONTRACT_TEST_AUX_PP_CAPTURE_S_, (), \\
            BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_CAPTURES(traits)) \\
    BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_EXPR(traits) \\
    BOOST_PP_COMMA_IF(has_trailing_comma)

#define BOOST_CONTRACT_TEST_AUX_PP_BOOL_ASSERTION_S_{0}_(s, traits) \\
    BOOST_CONTRACT_TEST_AUX_PP_BOOL_ASSERTION_IMPL_S_{0}_(s, traits, 1)

#define BOOST_CONTRACT_TEST_AUX_PP_BOOL_ASSERTION_IMPL_S_{0}_(s, traits, \\
        has_trailing_comma) \\
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_EXPR(traits) \\
    BOOST_PP_COMMA_IF(has_trailing_comma)

#define BOOST_CONTRACT_TEST_AUX_PP_IF_ASSERTION_S_{0}_(s, traits) \\
    BOOST_CONTRACT_TEST_AUX_PP_IF_ASSERTION_IMPL_S_{0}_(s, traits, 0, \\
            BOOST_CONTRACT_TEST_AUX_PP_ASSERTIONS_S_{1})

#define BOOST_CONTRACT_TEST_AUX_PP_POST_IF_ASSERTION_S_{0}_(s, traits) \\
    BOOST_CONTRACT_TEST_AUX_PP_IF_ASSERTION_IMPL_S_{0}_(s, traits, 0, \\
            BOOST_CONTRACT_TEST_AUX_PP_POST_ASSERTIONS_S_{1})

#define BOOST_CONTRACT_TEST_AUX_PP_STATIC_IF_ASSERTION_S_{0}_(s, traits) \\
    BOOST_CONTRACT_TEST_AUX_PP_IF_ASSERTION_IMPL_S_{0}_(s, traits, 1, \\
            BOOST_CONTRACT_TEST_AUX_PP_ASSERTIONS_S_{1})

#define BOOST_CONTRACT_TEST_AUX_PP_POST_STATIC_IF_ASSERTION_S_{0}_(s, traits) \\
    BOOST_CONTRACT_TEST_AUX_PP_IF_ASSERTION_IMPL_S_{0}_(s, traits, 1, \\
            BOOST_CONTRACT_TEST_AUX_PP_POST_ASSERTIONS_S_{1})

#define BOOST_CONTRACT_TEST_AUX_PP_IF_ASSERTION_IMPL_S_{0}_(s, traits, \\
        is_static, next_assertion_macro) \\
    BOOST_PP_EXPR_IIF(is_static, static) \\
    if( \\
        BOOST_PP_IIF( \\
            BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT( \\
            BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_KIND( \\
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND( \\
                traits \\
            ))) \\
        , \\
            BOOST_CONTRACT_TEST_AUX_PP_CONST_ASSERTION_IMPL_S_{1}_ \\
        , \\
            BOOST_CONTRACT_TEST_AUX_PP_IF_ASSERTION_BOOL_COND_S_{1}_ \\
        )(s, BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_COND(traits), 0) \\
    ) \\
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY( \\
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS(traits)), \\
        ( ) BOOST_PP_TUPLE_EAT(3) \\
    , \\
        BOOST_PP_SEQ_FOLD_LEFT_ ## s \\
    )(next_assertion_macro, (), \\
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_THENS(traits)) \\
    else \\
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY( \\
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES(traits)), \\
        ( ) BOOST_PP_TUPLE_EAT(3) \\
    , \\
        BOOST_PP_SEQ_FOLD_LEFT_ ## s \\
    )(next_assertion_macro, (), \\
            BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_ELSES(traits))

// Extra parenthesis always internally added for if bool cond (so remove them).
#define BOOST_CONTRACT_TEST_AUX_PP_IF_ASSERTION_BOOL_COND_S_{0}_(s, \\
        cond_traits, has_trailing_comma) \\
    BOOST_PP_TUPLE_REM_CTOR( \
        BOOST_CONTRACT_TEST_AUX_PP_BOOL_ASSERTION_IMPL_S_{0}_( \\
                s, cond_traits, has_trailing_comma) \
    )

#define BOOST_CONTRACT_TEST_AUX_PP_RETURN_ASSERTION_S_{0}_(s, traits) \\
    BOOST_CONTRACT_TEST_AUX_PP_1TUPLE_REM( \\
            BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_TRAITS_TYPE(traits)) \\
    BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_TRAITS_ASSIGN(traits) \\
    return \\
    ,

// Implementation: OLDOF_..._OPERATOR internally splits tokens into a 2-tuple.
#define BOOST_CONTRACT_TEST_AUX_PP_OLDOF_ASSERTION_S_{0}_(s, traits) \\
    BOOST_CONTRACT_TEST_AUX_PP_1TUPLE_REM( \\
            BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_TYPE(traits)) \\
    BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_ASSIGN(traits) \\
    BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_OPERATOR \\
    BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_EXPR(traits) \\
    ,
'''.format(n, n + 1)
    return result

script = os.path.basename(sys.argv[0])
path = sys.argv[0].replace('-generate.py', '', 1) + ".hpp"
file = open(path, 'w')

file.write('''
#ifndef BOOST_CONTRACT_TEST_AUX_PP_ASSERTION_HPP_
#define BOOST_CONTRACT_TEST_AUX_PP_ASSERTION_HPP_

// WARNING: FILE AUTOMATICALLY GENERATED, DO NOT MODIFY IT!
// Instead, modify and run related generation script "{0}".

#include "pp_1tuple_rem.hpp"
#include <boost/contract/ext_/preprocessor/traits/assertion.hpp>
#include <boost/contract/ext_/preprocessor/keyword/namespace.hpp>
#include <boost/contract/ext_/preprocessor/keyword/using.hpp>
#include <boost/contract/ext_/preprocessor/keyword/typedef.hpp>
#include <boost/contract/ext_/preprocessor/keyword/const.hpp>
#include <boost/contract/ext_/preprocessor/keyword/return.hpp>
#include <boost/contract/ext_/preprocessor/utility/empty.hpp>
#include <boost/preprocessor/seq/fold_left.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/tuple/rem.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/control/expr_iif.hpp>
#include <boost/preprocessor/logical/compl.hpp>
#include <boost/preprocessor/facilities/expand.hpp>

/* PIBLIC */

// Maximum number of nested assertions that can be processed (before pp errors).
#define BOOST_CONTRACT_TEST_AUX_PP_ASSERTION_LIMIT {1}

/* PRIVATE */

#define BOOST_CONTRACT_TEST_AUX_PP_CAPTURE_S_(s, captures, traits) \\
    BOOST_CONTRACT_TEST_AUX_PP_CAPTURE_PUSH_BACK_( \\
        captures, \\
        ( \\
            BOOST_CONTRACT_TEST_AUX_PP_1TUPLE_REM( \\
                    BOOST_CONTRACT_EXT_PP_CAPTURE_TRAITS_TYPE(traits)) \\
            BOOST_CONTRACT_EXT_PP_CAPTURE_TRAITS_NAME(traits) \\
        ) \\
    )

#define BOOST_CONTRACT_TEST_AUX_PP_CAPTURE_PUSH_BACK_(captures, capture) \
    ( \
        BOOST_PP_TUPLE_REM_CTOR(captures) \
        BOOST_PP_COMMA_IF(BOOST_PP_COMPL( \
                BOOST_PP_EXPAND(BOOST_CONTRACT_EXT_PP_IS_EMPTY captures))) \
        BOOST_PP_TUPLE_REM_CTOR(capture) \
    )
{2}
#endif // #include guard
'''.format(script, LIMIT, code()))

file.close()
print "Written:", path


