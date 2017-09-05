
# Copyright (C) 2008-2012 Lorenzo Caminiti
# Distributed under the Boost Software License, Version 1.0
# (see accompanying file LICENSE_1_0.txt or a copy at
# http://www.boost.org/LICENSE_1_0.txt)
# Home at http://sourceforge.net/projects/contractpp

import sys
import shutil

def data(max_size):
    s = ''
    for i in range(0, max_size + 1): # 0 and max_size included in range.
        s = s + '''
#define CONTRACT_DETAIL_PP_IS_DIGIT_{0} (1) /* unary */ \
'''.format(i)
    return s

BOOST_PP_LIMIT_MAG = raw_input("BOOST_PP_LIMIT_MAG" +
        " from <boost/preprocessor/limits.hpp> [256] = ")
if BOOST_PP_LIMIT_MAG == "": BOOST_PP_LIMIT_MAG = 256
else: BOOST_PP_LIMIT_MAG = int(BOOST_PP_LIMIT_MAG)

header = sys.argv[0].replace("-generate.py", ".hpp", 1)
shutil.copyfile(header, header + ".bak")
h = open(header, 'w')

h.write('''
#ifndef CONTRACT_DETAIL_PP_IS_DIGIT_HPP_
#define CONTRACT_DETAIL_PP_IS_DIGIT_HPP_

// WARNING: FILE AUTOMATICALLY GENERATED, DO NOT MODIFY IT!
// Instead modify the generation script "<FILE>-generate.py" and run
// `$ python <FILE_NAME>-generate.py > FILE_NAME.hpp`.
// Used: #define BOOST_PP_LIMIT_MAG {0}

#include <contract/detail/preprocessor/keyword/facilities/is.hpp>

// PUBLIC //

#define CONTRACT_DETAIL_PP_IS_DIGIT(tokens) \\
    CONTRACT_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT(tokens, \\
            CONTRACT_DETAIL_PP_IS_DIGIT_)

// DATA //
{1}

#endif // #include guard

'''.format(BOOST_PP_LIMIT_MAG, data(BOOST_PP_LIMIT_MAG)))

h.close()
print "Written", header

