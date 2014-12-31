
# Copyright (C) 2008-2015 Lorenzo Caminiti
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
            'alignas',
            'alignof',
            'and',
            'and_eq',
            'asm',
            'auto',
            'bitand',
            'bitor',
            'bool',
            'break',
            'case',
            'catch',
            'char',
            'char16_t',
            'char32_t',
            'class',
            'compl',
            'const',
            'constexpr',
            'const_cast',
            'continue',
            'decltype',
            'default',
            'delete',
            'do',
            'double',
            'dynamic_cast',
            'else',
            'enum',
            'explicit',
            'export',
            'extern',
            'false',
            'final',
            'float',
            'for',
            'friend',
            'goto',
            'if',
            'inline',
            'int',
            'long',
            'mutable',
            'namespace',
            'new',
            'noexcept',
            'not',
            'not_eq',
            'nullptr',
            'operator',
            'or',
            'or_eq',
            'override',
            'private',
            'protected',
            'public',
            'register',
            'reinterpret_cast',
            'return',
            'short',
            'signed',
            'sizeof',
            'static',
            'static_assert',
            'static_cast',
            'struct',
            'switch',
            'template',
            'this',
            'thread_local',
            'throw',
            'true',
            'try',
            'typedef',
            'typeid',
            'typename',
            'union',
            'unsigned',
            'using',
            'virtual',
            'void',
            'volatile',
            'wchar_t',
            'while',
            'xor',
            'xor_eq'
        ]
    },
    {
        'directory': 'contract',
        'keywords': [
            'invariant',
            'precondition',
            'postcondition',
            'extends',
            'verbatim'
        ]
    }
]

script = os.path.basename(sys.argv[0])
root = sys.argv[0].replace('-generate.py', '', 1)
for entry in entries:
    directory = os.path.join(root, entry['directory'])
    if not os.path.exists(directory): os.makedirs(directory)
    keywords = entry['keywords']
    for keyword in keywords:
        filename = keyword + ".hpp"
        path = os.path.join(directory, filename)
        file = open(path, 'w')

        file.write(
'''
#ifndef BOOST_CONTRACT_EXT_PP_KEYWORD_{1}_HPP_
#define BOOST_CONTRACT_EXT_PP_KEYWORD_{1}_HPP_

// WARNING: FILE AUTOMATICALLY GENERATED, DO NOT MODIFY IT!
// Instead, modify and run related generation script "{0}".

#include <boost/contract/ext_/preprocessor/keyword/utility/is.hpp>
#include <boost/contract/ext_/preprocessor/keyword/utility/remove.hpp>

/* PRIVATE */

// Must expand to a single comma `,` (not local macros, do not #undefine).
#define BOOST_CONTRACT_EXT_PP_KEYWORD_{1}_CAT_TO_COMMA{2} ,
#define {2}BOOST_CONTRACT_EXT_PP_KEYWORD_{1}_CAT_TO_COMMA ,

// Must expand to empty `` (not local macros, do not #undefine).
#define BOOST_CONTRACT_EXT_PP_KEYWORD_{1}_CAT_TO_EMPTY{2}
#define {2}BOOST_CONTRACT_EXT_PP_KEYWORD_{1}_CAT_TO_EMPTY

/* PUBLIC */

// Precondition: tokens must start with a token concatenable to a macro name
//               (e.g., a literal or integral token) or with parenthesis.
#define BOOST_CONTRACT_EXT_PP_KEYWORD_IS_{1}_FRONT(tokens) \\
    BOOST_CONTRACT_EXT_PP_KEYWORD_UTILITY_IS_FRONT( \\
            BOOST_CONTRACT_EXT_PP_KEYWORD_{1}_CAT_TO_COMMA, tokens)

// Precondition: tokens must end with a token concatenable to a macro name
//               (e.g., a literal or integral token) or with parenthesis.
#define BOOST_CONTRACT_EXT_PP_KEYWORD_IS_{1}_BACK(tokens) \\
    BOOST_CONTRACT_EXT_PP_KEYWORD_UTILITY_IS_BACK( \\
            BOOST_CONTRACT_EXT_PP_KEYWORD_{1}_CAT_TO_COMMA, tokens)

// Precondition: tokens must start with `{2}` (this can be
//               checked with `..._IS_{1}_FRONT` macro above).
#define BOOST_CONTRACT_EXT_PP_KEYWORD_{1}_REMOVE_FRONT(tokens) \\
    BOOST_CONTRACT_EXT_PP_KEYWORD_UTILITY_REMOVE_FRONT( \\
            BOOST_CONTRACT_EXT_PP_KEYWORD_{1}_CAT_TO_EMPTY, tokens)

// Precondition: tokens must end with `{2}` (this can be
//               checked with `..._IS_{1}_BACK` macro above).
#define BOOST_CONTRACT_EXT_PP_KEYWORD_{1}_REMOVE_BACK(tokens) \\
    BOOST_CONTRACT_EXT_PP_KEYWORD_UTILITY_REMOVE_BACK( \\
            BOOST_CONTRACT_EXT_PP_KEYWORD_{1}_CAT_TO_EMPTY, tokens)

#endif // #include guard

'''.format(script, keyword.upper(), keyword.lower()))

        file.close()
        print "Written:", path

