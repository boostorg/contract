
import os
import sys

LIMIT = 64

def code():
    result = ''
    for n in range(1, LIMIT + 1):
        result = result + '''
/* PUBLIC ({0}) */

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_PARSE_D_L_{0}(d, l, decl) \\
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_{0}_ \\
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_{0}_ \\
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_{0}_ \\
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \\
        BOOST_CONTRACT_EXT_PP_IF_ASSERTION_TRAITS_PARSE_D_L_{0} \\
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \\
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \\
        BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_{0} \\
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \\
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \\
    , \\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_{0}_ \\
    ))))))(d, l, decl)

// Implementation: EXPAND needed for proper macro expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_PARSE_D_L_{0}(d, l, decl) \\
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_NAMESPACE_FRONT(decl), \\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_{0}_ \\
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl),\\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_{0}_ \\
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TYPEDEF_FRONT(decl), \\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_{0}_ \\
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_IF_FRONT(decl), \\
        BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_PARSE_D_L_{0} \\
    , BOOST_PP_IIF(BOOST_PP_EXPAND( \\
            BOOST_CONTRACT_EXT_PP_STATIC_IF_ASSERTION_TRAITS_IS(decl)), \\
        BOOST_CONTRACT_EXT_PP_POST_STATIC_IF_ASSERTION_TRAITS_PARSE_D_L_{0} \\
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_CONST_FRONT(decl), \\
        BOOST_CONTRACT_EXT_PP_CONST_ASSERTION_TRAITS_PARSE_D_L \\
    , \\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_{0}_ \\
    ))))))(d, l, decl)
    
// Implementation: Else statements are first parsed and then replaced when
// parsed as empty and they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_{0}( \\
        d, l, decl) \\
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \\
            decl), \\
        1 \\
    , \\
        0 \\
    ))

// Implementation: old-of assertions are first parsed as boolean assertions and
// then replaced as old-of assertions by the overall assertions parsing alg.
// Else statements are first parsed and then replaced when parsed as empty and
// they appear after a comma following if statements.
// EXPAND and IIF (instead of BITOR, etc.) for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_IS_REPLACEMENT_D_L_{0}( \\
        d, l, decl) \\
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \\
            decl), \\
        1 \\
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_IS(decl), \\
        1 \\
    , \\
        0 \\
    )))

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_PARSE_D_L_{0}( \\
        d, l, decl_traits) \\
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_{0}( \\
            d, l, decl_traits)

// Implementation: Same ELSE macro below used by both if and static-if.
#define BOOST_CONTRACT_EXT_PP_POST_ASSERTION_TRAITS_REPLACE_PARSE_D_L_{0}( \\
        d, l, decl_traits) \\
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_ELSE_FRONT( \\
            BOOST_PP_TUPLE_ELEM(2, 0, decl_traits)), \\
  BOOST_CONTRACT_EXT_PP_POST_IF_ASSERTION_TRAITS_REPLACE_ELSES_PARSE_D_L_{0}\\
    , \\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_{0}_ \\
    )(d, l, decl_traits)

/* PRIVATE ({0}) */

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_REPLACE_OLDOF_PARSE_D_L_{0}_( \\
        d, l, decl_traits) \\
    BOOST_CONTRACT_EXT_PP_OLDOF_ASSERTION_TRAITS_REPLACE_PARSE_D(d, decl_traits)
        
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_NAMESPACE_PARSE_{0}_( \\
        d, l, decl) \\
    BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_USING_PARSE_{0}_(d, l, decl) \\
    BOOST_CONTRACT_EXT_PP_USING_ASSERTION_TRAITS_PARSE(decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_TYPEDEF_PARSE_{0}_(d, l, decl) \\
    BOOST_CONTRACT_EXT_PP_TYPEDEF_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_{0}_(d, l, decl) \\
    BOOST_CONTRACT_EXT_PP_RETURN_ASSERTION_TRAITS_PARSE_D(d, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_{0}_(d, l, decl) \\
    BOOST_CONTRACT_EXT_PP_BOOL_ASSERTION_TRAITS_PARSE(decl)

// This is needed because it has to eventually use IS_RETURN_BACK which does
// not allow decl to end with parenthesis `... (...)` (so type is first parsed
// to make sure this is a valid return assertion with a type (possibly auto),
// a not-nil assignment, etc.). Only after that, IS_RETURN_BACK is safely used.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_{0}_(d, l, decl) \\
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_{0}_(d, l, \\
        decl, \\
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_AUTO_TYPE_PARSE_D( \\
                d, decl BOOST_PP_NIL) \\
    )

// decl = `auto-type something-but-not-paren ...` is passed to RETURN_MAYBE.
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_CHECK_{0}_( \\
        d, l, decl, decl_type) \\
    BOOST_PP_IIF(BOOST_PP_EXPAND( \\
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_AUTO_FRONT( \\
                BOOST_PP_TUPLE_ELEM(2, 1, decl_type)), \\
            0 \\
        , \\
            BOOST_CONTRACT_EXT_PP_IS_EMPTY( \\
                    BOOST_PP_TUPLE_ELEM(2, 1, decl_type)()) \\
        ) \\
    ) , \\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_{0}_ \\
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_NIL_FRONT( \\
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_{0}_ \\
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN( \\
            BOOST_PP_TUPLE_ELEM(2, 0, decl_type)), \\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_{0}_ \\
    , \\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_{0}_ \\
    )))(d, l, decl)

#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HANDLE_RETURN_MAYBE_{0}_( \\
        d, l, decl) \\
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_RETURN_BACK(decl), \\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_RETURN_PARSE_{0}_ \\
    , \\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_BOOL_PARSE_{0}_ \\
    )(d, l, decl)

'''.format(n, n + 1)
    return result

script = os.path.basename(sys.argv[0])
path = sys.argv[0].replace('-generate.py', '', 1) + ".hpp"
file = open(path, 'w')

file.write('''
#ifndef BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HPP_
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_HPP_

// WARNING: FILE AUTOMATICALLY GENERATED, DO NOT MODIFY IT!
// Instead, modify and run related generation script "{0}".

#include <boost/contract/ext_/preprocessor/traits/assertion/bool.hpp>
#include <boost/contract/ext_/preprocessor/traits/assertion/const.hpp>
#include <boost/contract/ext_/preprocessor/traits/assertion/if.hpp>
#include <boost/contract/ext_/preprocessor/traits/assertion/oldof.hpp>
#include <boost/contract/ext_/preprocessor/traits/assertion/return.hpp>
#include <boost/contract/ext_/preprocessor/traits/assertion/typedef.hpp>
#include <boost/contract/ext_/preprocessor/traits/assertion/using.hpp>
#include <boost/contract/ext_/preprocessor/traits/assertion/namespace.hpp>
#include <boost/contract/ext_/preprocessor/traits/aux_/type.hpp>
#include <boost/contract/ext_/preprocessor/keyword/namespace.hpp>
#include <boost/contract/ext_/preprocessor/keyword/using.hpp>
#include <boost/contract/ext_/preprocessor/keyword/template.hpp>
#include <boost/contract/ext_/preprocessor/keyword/typedef.hpp>
#include <boost/contract/ext_/preprocessor/keyword/return.hpp>
#include <boost/contract/ext_/preprocessor/keyword/const.hpp>
#include <boost/contract/ext_/preprocessor/keyword/if.hpp>
#include <boost/contract/ext_/preprocessor/keyword/else.hpp>
#include <boost/contract/ext_/preprocessor/paren/has.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/control/iif.hpp>

/* PUBLIC */

// Maximum number of nested assertions that can be parsed (before pp errors).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_LIMIT {1}

/* PRIVATE */

// Expand to 1 if decl = `[template(,,,)] using ...`, otherwise to 0.
// EXPAND for proper expansion (on MSVC).
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_(decl) \\
    BOOST_PP_EXPAND(BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_USING_FRONT(\\
            decl), \\
        1 BOOST_PP_TUPLE_EAT(1) \\
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TEMPLATE_FRONT(decl), \\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_TEMPLATE_ \\
    , \\
        0 BOOST_PP_TUPLE_EAT(1) \\
    ))(decl))

// Precondition: decl = `template ...`
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_TEMPLATE_(decl) \\
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_HAS_PAREN( \\
            BOOST_CONTRACT_EXT_PP_KEYWORD_TEMPLATE_REMOVE_FRONT(decl)), \\
        BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_TEMPLATE_PAREN_ \\
    , \\
        0 BOOST_PP_TUPLE_EAT(1) \\
    )(BOOST_CONTRACT_EXT_PP_KEYWORD_TEMPLATE_REMOVE_FRONT(decl))

// Precondition: decl = `(,,,) ...`
#define BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_IS_USING_TEMPLATE_PAREN_( \\
        decl) \\
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_USING_FRONT( \\
            BOOST_PP_TUPLE_EAT(0) decl), 1, 0)
{2}
#endif // #include guard
'''.format(script, LIMIT, code()))

file.close()
print "Written:", path

