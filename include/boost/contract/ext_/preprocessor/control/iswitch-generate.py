
# Copyright (C) 2008-2012 Lorenzo Caminiti
# Distributed under the Boost Software License, Version 1.0
# (see accompanying file LICENSE_1_0.txt or a copy at
# http://www.boost.org/LICENSE_1_0.txt)
# Home at http://sourceforge.net/projects/contractpp

import os
import sys

def rest_args(n):
    s = ""
    for i in range(2, n + 1): s = s + "case" + str(i) + ", op" + str(i) + ", "
    s = s + "default_, data"
    return s

def data(size):
    s = ""
    for n in range(2, size):
        s = s + '''
/* ISWITCH{0} */

#define BOOST_CONTRACT_EXT_PP_ISWITCH{0}_YES_(cond, case1, op1, {2}) op1 data

#define BOOST_CONTRACT_EXT_PP_ISWITCH{0}_NO_(cond, case1, op1, {2}) \\
    BOOST_CONTRACT_EXT_PP_ISWITCH{1}(cond, {2})

#define BOOST_CONTRACT_EXT_PP_ISWITCH{0}_EXPAND_ONCE_(x) x

#define BOOST_CONTRACT_EXT_PP_ISWITCH{0}_EXPAND_(x) \\
    BOOST_CONTRACT_EXT_PP_ISWITCH{0}_EXPAND_ONCE_(x)

#define BOOST_CONTRACT_EXT_PP_ISWITCH{0}(cond, case1, op1, {2}) \\
    BOOST_CONTRACT_EXT_PP_ISWITCH{0}_EXPAND_(BOOST_PP_IIF(case1 cond, \\
        BOOST_CONTRACT_EXT_PP_ISWITCH{0}_YES_ \\
    , \\
        BOOST_CONTRACT_EXT_PP_ISWITCH{0}_NO_ \\
    )(cond, case1, op1, {2}))

#define BOOST_CONTRACT_EXT_PP_ISWITCH_{3} BOOST_CONTRACT_EXT_PP_ISWITCH{0}
'''.format(n, n - 1, rest_args(n), n * 2 + 3)
    return s

BOOST_PP_LIMIT_TUPLE = raw_input("BOOST_PP_LIMIT_TUPLE" +
        " from <boost/preprocessor/limits.hpp> [64] = ")
if BOOST_PP_LIMIT_TUPLE == "": BOOST_PP_LIMIT_TUPLE = 64
else: BOOST_PP_LIMIT_TUPLE = int(BOOST_PP_LIMIT_TUPLE)

script = os.path.basename(sys.argv[0])
path = sys.argv[0].replace('-generate.py', '', 1) + ".hpp"
file = open(path, 'w')

file.write('''
#ifndef BOOST_CONTRACT_EXT_PP_ISWITCH_HPP_
#define BOOST_CONTRACT_EXT_PP_ISWITCH_HPP_

// WARNING: FILE AUTOMATICALLY GENERATED, DO NOT MODIFY IT!
// Instead, modify and run related generation script "{0}".

#include <boost/preprocessor/limits.hpp>
#if BOOST_PP_LIMIT_TUPLE != {1}
#   error "code generation used incorrect BOOST_PP_LIMIT_TUPLE"
#endif

#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/facilities/expand.hpp>

// Usage:
//  ISWITCH-n(cond, case1, op1, ..., case-n, op-n, default_, data)
//
// Parameters (for each i in [1, n]):
// * Parameter `data` must be a pp-tuple `(x, y, ...)` that can be used as
// argument list for the op-i macros `op-i data` expands to `op-i(x, y, ...)`.
// * Parameter `cond` must be a pp-tuple `(a, b, ...)` that can be used as
// argument list for case-i macros `case-i cond` expands to `case-i(a, b, ...)`.
// * All case-i macros must expand `case-i cond` to 0 or 1.
//
// Result:
// * Let k be the first index in [1, n] for which `case-k cond` expands to 1
// then ISWITCH-n expands to `op-k data` and all `case-i cond` for i in
// (k, n] are not evaluated. Therefore, it is possible to put last case-i macros
// expensive to evaluate (or even incorrect to evaluate unless previous case
// macros expand 0, similar to C++ short-circuit optimizations).
// * ISWITHC-n expands to `default_ data` iff `case-i data` expands to 0 for
// all i in [1, n].
//
// Notes:
// * There is also a variadics version of this macro that determines n
// automatically (but to avoid a couple of extra macro expansions, it is best
// to not use the variadics version when n is known a priori).

/* ISWITCH (variadics) */

#include <boost/preprocessor/config/config.hpp>
#if BOOST_PP_VARIADICS
#   include <boost/preprocessor/facilities/overload.hpp>
#   define BOOST_CONTRACT_EXT_PP_ISWITCH_EXPAND_ONCE_(x) x
#   define BOOST_CONTRACT_EXT_PP_ISWITCH_EXPAND_(x) \\
        BOOST_CONTRACT_EXT_PP_ISWITCH_EXPAND_ONCE_(x)
#   define BOOST_CONTRACT_EXT_PP_ISWITCH(...) \\
        BOOST_CONTRACT_EXT_PP_ISWITCH_EXPAND_( \\
            BOOST_PP_OVERLOAD(BOOST_CONTRACT_EXT_PP_ISWITCH_, __VA_ARGS__) \\
            (__VA_ARGS__) \\
        )
#endif

/* ISWITCH1 */

#define BOOST_CONTRACT_EXT_PP_ISWITCH1_EXPAND_ONCE_(x) x

#define BOOST_CONTRACT_EXT_PP_ISWITCH1_EXPAND_(x) \\
    BOOST_CONTRACT_EXT_PP_ISWITCH1_EXPAND_ONCE_(x)

#define BOOST_CONTRACT_EXT_PP_ISWITCH1_I(cond, case1, op1, default_, data) \\
    BOOST_CONTRACT_EXT_PP_ISWITCH1_EXPAND_(BOOST_PP_IIF(case1 cond, \\
        op1 \\
    , \\
        default_ \\
    ) data)

#define BOOST_CONTRACT_EXT_PP_ISWITCH1(cond, case1, op1, default_, data) \\
    BOOST_CONTRACT_EXT_PP_ISWITCH1_I(cond, case1, op1, default_, data)

#define BOOST_CONTRACT_EXT_PP_ISWITCH_5 BOOST_CONTRACT_EXT_PP_ISWITCH1
{2}
#endif // #include guard

'''.format(script, BOOST_PP_LIMIT_TUPLE, data((BOOST_PP_LIMIT_TUPLE - 2) / 2)))

file.close()
print "Written", path

