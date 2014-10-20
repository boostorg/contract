
# Copyright (C) 2008-2012 Lorenzo Caminiti
# Distributed under the Boost Software License, Version 1.0
# (see accompanying file LICENSE_1_0.txt or a copy at
# http://www.boost.org/LICENSE_1_0.txt)
# Home at http://sourceforge.net/projects/contractpp

import os
import sys

entries = [
    {
        'directory': '.',
        'keywords': [
'alignas', 'alignof', 'and', 'and_eq', 'asm', 'auto', 'bitand', 'bitor', 'bool', 'break', 'case', 'catch', 'char', 'char16_t', 'char32_t', 'class', 'compl', 'const', 'constexpr', 'const_cast', 'continue', 'decltype', 'default', 'delete', 'do', 'double', 'dynamic_cast', 'else', 'enum', 'explicit', 'export', 'extern', 'false', 'final', 'float', 'for', 'friend', 'goto', 'if', 'inline', 'int', 'long', 'mutable', 'namespace', 'new', 'noexcept', 'not', 'not_eq', 'nullptr', 'operator', 'or', 'or_eq', 'override', 'private', 'protected', 'public', 'register', 'reinterpret_cast', 'return', 'short', 'signed', 'sizeof', 'static', 'static_assert', 'static_cast', 'struct', 'switch', 'template', 'this', 'thread_local', 'throw', 'true', 'try', 'typedef', 'typeid', 'typename', 'union', 'unsigned', 'using', 'virtual', 'void', 'volatile', 'wchar_t', 'while', 'xor', 'xor_eq'
        ]
    },
    {
        'directory': 'contract',
        'keywords': [
'invariant', 'precondition', 'postcondition', 'extends', 'verbatim'
        ]
    }
]

script = os.path.basename(sys.argv[0])
for entry in entries:
    directory = entry['directory']
    keywords = entry['keywords']
    if not os.path.exists(directory): os.makedirs(directory)
    for keyword in keywords:
        filename = keyword + ".hpp"
        path = os.path.join(directory, filename)
        file = open(path, 'w')

        file.write(
'''
#ifndef BOOST_CONTRACT_EXT_PP_KEYWORD_{1}_HPP_
#define BOOST_CONTRACT_EXT_PP_KEYWORD_{1}_HPP_

// WARNING: FILE AUTOMATICALLY GENERATED, DO NOT MODIFY IT!
// Instead, modify and run the related generation script "{0}".

#include <boost/contract/ext_/preprocessor/keyword/utility/is.hpp>
#include <boost/preprocessor/cat.hpp>

// PRIVATE //

// NOTE: These are not local macros, do NOT #undefine them ('x' used to avoid
// concatenating to reserved symbols).
// The following macro must expand to a unary token (e.g., `(1)`).
#define BOOST_CONTRACT_EXT_PP_KEYWORD_{1}_ISx{2} (1)
#define {2}xBOOST_CONTRACT_EXT_PP_KEYWORD_{1}_IS (1)
// The following macro must expand to nothing.
#define BOOST_CONTRACT_EXT_PP_KEYWORD_{1}_REMOVEx{2}
#define {2}xBOOST_CONTRACT_EXT_PP_KEYWORD_{1}_REMOVE

// PUBLIC //

#define BOOST_CONTRACT_EXT_PP_KEYWORD_IS_{1}_FRONT(tokens) \\
    BOOST_CONTRACT_EXT_PP_KEYWORD_UTILITY_IS_FRONT(tokens, \\
            BOOST_CONTRACT_EXT_PP_KEYWORD_{1}_ISx)

#define BOOST_CONTRACT_EXT_PP_KEYWORD_IS_{1}_BACK(token) \\
    BOOST_CONTRACT_EXT_PP_KEYWORD_UTILITY_IS_BACK(token, \\
            xBOOST_CONTRACT_EXT_PP_KEYWORD_{1}_IS)

// Precondition: tokens start with keyword to remove (see `..._IS_{1}_FRONT`).
#define BOOST_CONTRACT_EXT_PP_KEYWORD_{1}_REMOVE_FRONT(tokens) \\
    BOOST_PP_CAT(BOOST_CONTRACT_EXT_PP_KEYWORD_{1}_REMOVEx, tokens)

// Precondition: token ends with keyword to remove (see `..._IS_{1}_BACK`).
#define BOOST_CONTRACT_EXT_PP_KEYWORD_{1}_REMOVE_BACK(token) \\
    BOOST_PP_CAT(token, xBOOST_CONTRACT_EXT_PP_KEYWORD_{1}_REMOVE)

#endif // #include guard

'''.format(script, keyword.upper(), keyword.lower()))

        file.close()
        print "Written:", path

