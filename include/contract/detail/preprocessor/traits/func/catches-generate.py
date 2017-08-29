
# Copyright (C) 2008-2012 Lorenzo Caminiti
# Distributed under the Boost Software License, Version 1.0
# (see accompanying file LICENSE_1_0.txt or a copy at
# http://www.boost.org/LICENSE_1_0.txt)
# Home at http://sourceforge.net/projects/contractpp

import sys
import shutil

def data(max):
    s = ''
    for i in range(0, max):
        i = max - i - 1 # Reverse iteration order.
        if i == 0: p = ""
        else: p = "_" + str(i)
        if i == max - 1:
            next_sign_macro = "ERROR_support_maximum_of_" + str(max) + \
                    "_catch_statements"
        else:
            next_sign_macro = \
                    "CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES_TRAIT_SIGN_" + \
                    str(i + 1) + "_"
        s = s + '''
#define CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES_TRAIT_SIGN_NEXT{0}_(seq_sign) \\
    BOOST_PP_IIF(CONTRACT_DETAIL_PP_KEYWORD_IS_CATCH_FRONT( \\
            BOOST_PP_TUPLE_ELEM(2, 1, seq_sign)), \\
        {1} \\
    , \\
        seq_sign BOOST_PP_TUPLE_EAT(2) \\
    )(BOOST_PP_TUPLE_ELEM(2, 0, seq_sign), BOOST_PP_TUPLE_ELEM(2, 1, seq_sign))
#define CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES_TRAIT_SIGN{0}_(seq, sign) \\
    CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES_TRAIT_SIGN_NEXT{0}_( ( \\
        seq BOOST_PP_CAT( \\
                CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES_EXCEPTION_DECL_, sign) \\
    ) ) \
'''.format(p, next_sign_macro)
    return s

CONTRACT_LIMIT_CONSTRUCTOR_TRY_BLOCK_CATCHES = raw_input(
        "CONTRACT_LIMIT_CONSTRUCTOR_TRY_BLOCK_CATCHES" +
        " from <contract/limits.hpp> [10] = ")
if CONTRACT_LIMIT_CONSTRUCTOR_TRY_BLOCK_CATCHES == "":
    CONTRACT_LIMIT_CONSTRUCTOR_TRY_BLOCK_CATCHES = 10
else:
    CONTRACT_LIMIT_CONSTRUCTOR_TRY_BLOCK_CATCHES = int(
            CONTRACT_LIMIT_CONSTRUCTOR_TRY_BLOCK_CATCHES)

header = sys.argv[0].replace("-generate.py", ".hpp", 1)
shutil.copyfile(header, header + ".bak")
h = open(header, 'w')

h.write('''
#ifndef CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES_HPP_
#define CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES_HPP_

// WARNING: FILE AUTOMATICALLY GENERATED, DO NOT MODIFY IT!
// Instead modify the generation script "<FILE>-generate.py" and run
// `$ python <FILE_NAME>-generate.py > FILE_NAME.hpp`.
// Used: #define CONTRACT_LIMIT_CONSTRUCTOR_TRY_BLOCK_CATCHES {0}

#include <contract/limits.hpp>
#if CONTRACT_LIMIT_CONSTRUCTOR_TRY_BLOCK_CATCHES != {0}
#error "Code generation used incorrect CONTRACT_LIMIT_CONSTRUCTOR_TRY_BLOCK_CATCHES"
#endif

#include <contract/detail/preprocessor/traits/aux_/apply.hpp>
#include <contract/detail/preprocessor/keyword/catch.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/array/elem.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/tuple/eat.hpp>

// PRIVATE //

#define CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES_STATEMENTS_(statements) \\
    /* beginning of seq elem of 3-tuple from DECL_catch here */ \\
    statements)), /* this comma splits */

#define CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES_EXCEPTION_DECL_catch( \\
        exception_decl) \\
    ((exception_decl, CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES_STATEMENTS_ \\
    /* end of seq elem of 3-tuple from STATEMENTS_ here */
{1}

#define CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES_LIST_(sign) \\
    CONTRACT_DETAIL_PP_SEQ_TO_LIST_NEVER_EMPTY(BOOST_PP_TUPLE_ELEM(2, 0, \\
            CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES_TRAIT_SIGN_( \\
                    BOOST_PP_EMPTY(), sign)))

#define CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES_TRAIT_(sign) \\
    BOOST_PP_IIF(CONTRACT_DETAIL_PP_KEYWORD_IS_CATCH_FRONT(sign), \\
        CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES_LIST_ \\
    , \\
        BOOST_PP_NIL BOOST_PP_TUPLE_EAT(1) /* empty catch list */ \\
    )(sign)
        
#define CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES_REMOVE_(sign) \\
    BOOST_PP_TUPLE_ELEM(2, 1, \\
            CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES_TRAIT_SIGN_( \\
                    BOOST_PP_EMPTY(), sign))

#define CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES_SIGN_(sign) \\
    BOOST_PP_IIF(CONTRACT_DETAIL_PP_KEYWORD_IS_CATCH_FRONT(sign), \\
        CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES_REMOVE_ \\
    , \\
        sign BOOST_PP_TUPLE_EAT(1) \\
    )(sign)

// PROTECTED //

#define CONTRACT_DETAIL_PP_FUNC_TRAITS_AUX_CATCHES(traits_sign) \\
    CONTRACT_DETAIL_PP_TRAITS_AUX_APPLY(traits_sign, \\
            CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES_TRAIT_, \\
            CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES_SIGN_)

// PUBLIC //

// Expand to pp-list of catch traits `(exception_decl, statements)`.
#define CONTRACT_DETAIL_PP_FUNC_TRAITS_CATCHES(func_traits) \\
    BOOST_PP_ARRAY_ELEM(23, func_traits)

// Expand to either `exception_type exception_var` or `...`.
#define CONTRACT_DETAIL_PP_CATCH_TRAITS_EXCEPTION_DECL(catch_traits) \\
    BOOST_PP_TUPLE_ELEM(2, 0, catch_traits)

// Expand to `instruction; instruction; ...` (all instructions optional).
#define CONTRACT_DETAIL_PP_CATCH_TRAITS_STATEMENTS(catch_traits) \\
    BOOST_PP_TUPLE_ELEM(2, 1, catch_traits)

#endif // #include guard

'''.format(CONTRACT_LIMIT_CONSTRUCTOR_TRY_BLOCK_CATCHES,
        data(CONTRACT_LIMIT_CONSTRUCTOR_TRY_BLOCK_CATCHES)))

h.close()
print "Written:", header

