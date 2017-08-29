
# Copyright (C) 2008-2012 Lorenzo Caminiti
# Distributed under the Boost Software License, Version 1.0
# (see accompanying file LICENSE_1_0.txt or a copy at
# http://www.boost.org/LICENSE_1_0.txt)
# Home at http://sourceforge.net/projects/contractpp

import sys
import shutil

def placeholders(start, stop):
    (s, comma) = ('', '')
    for i in range(start, stop):
        (s, comma) = (s + comma + '_' + str(i + 1), ', ')
    return s

def data(max_size):
    s = ''
    for size in range(1, max_size + 1):
        s = s + '''
#define CONTRACT_DETAIL_PP_TUPLE_SPLIT_{0}({1}) \\
    ({1}) , /* comma splits */ \
'''.format(size, placeholders(0, size))
    return s

BOOST_PP_LIMIT_TUPLE = raw_input("BOOST_PP_LIMIT_TUPLE" +
        " from <boost/preprocessor/limit.hpp> [64] = ")
if BOOST_PP_LIMIT_TUPLE == "": BOOST_PP_LIMIT_TUPLE = 64
else: BOOST_PP_LIMIT_TUPLE = int(BOOST_PP_LIMIT_TUPLE)

header = sys.argv[0].replace("-generate.py", ".hpp", 1)
shutil.copyfile(header, header + ".bak")
h = open(header, 'w')

h.write('''
#ifndef CONTRACT_DETAIL_PP_TUPLE_SPLIT_HPP_
#define CONTRACT_DETAIL_PP_TUPLE_SPLIT_HPP_

// WARNING: FILE AUTOMATICALLY GENERATED, DO NOT MODIFY IT!
// Instead modify the generation script "<FILE>-generate.py" and run
// `$ python <FILE_NAME>-generate.py > FILE_NAME.hpp`.
// Used: #define BOOST_PP_LIMIT_TUPLE {0}

#include <boost/preprocessor/limits.hpp>
#if BOOST_PP_LIMIT_TUPLE != {0}
#error "Code generation used incorrect BOOST_PP_LIMIT_TUPLE"
#endif

// PRIVATE //

// Own version of PP_CAT for reentrancy.
#if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#   define CONTRACT_DETAIL_PP_TUPLE_SPLIT_CAT_(a, b) \\
        CONTRACT_DETAIL_PP_TUPLE_SPLIT_CAT_I_(a, b)
#else
#   define CONTRACT_DETAIL_PP_TUPLE_SPLIT_CAT_(a, b) \\
        CONTRACT_DETAIL_PP_TUPLE_SPLIT_CAT_OO_((a, b))
#   define CONTRACT_DETAIL_PP_TUPLE_SPLIT_CAT_OO_(par) \\
        CONTRACT_DETAIL_PP_TUPLE_SPLIT_CAT_I_ ## par
#endif
#if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MSVC()
#   define CONTRACT_DETAIL_PP_TUPLE_SPLIT_CAT_I_(a, b) \\
        a ## b
#else
#   define CONTRACT_DETAIL_PP_TUPLE_SPLIT_CAT_I_(a, b) \\
        CONTRACT_DETAIL_PP_TUPLE_SPLIT_CAT_II_(~, a ## b)
#   define CONTRACT_DETAIL_PP_TUPLE_SPLIT_CAT_II_(p, res) \\
        res
#endif

// PUBLIC //

#define CONTRACT_DETAIL_PP_TUPLE_SPLIT(size) \\
    CONTRACT_DETAIL_PP_TUPLE_SPLIT_CAT_(CONTRACT_DETAIL_PP_TUPLE_SPLIT_, size)

// DATA //
{1}

#endif // #include guard

'''.format(BOOST_PP_LIMIT_TUPLE, data(BOOST_PP_LIMIT_TUPLE)))

h.close()
print "Written", header

