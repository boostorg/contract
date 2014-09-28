
# Copyright (C) 2008-2012 Lorenzo Caminiti
# Distributed under the Boost Software License, Version 1.0
# (see accompanying file LICENSE_1_0.txt or a copy at
# http://www.boost.org/LICENSE_1_0.txt)
# Home at http://sourceforge.net/projects/contractpp

import os
import sys
import shutil

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
        try: 
            shutil.copyfile(path, path + ".bak")
        except:
            pass
        file = open(path, 'w')

        file.write('''
// WARNING: FILE AUTOMATICALLY GENERATED, DO NOT MODIFY IT!
// Instead, modify and run the related generation script "{0}".

#ifndef BOOST_CONTRACT_EXT_PP_KEYWORD_{1}_HPP_
#define BOOST_CONTRACT_EXT_PP_KEYWORD_{1}_HPP_

#include <boost/contract/ext_/preprocessor/keyword/utility/is.hpp>
#include <boost/contract/ext_/preprocessor/keyword/utility/rem.hpp>

// PRIVATE //

// NOTE: These are not local macros, do NOT #undefine them.
// The following macro must expand to a unary token: `(1)`, etc.
#define BOOST_CONTRACT_EXT_PP_KEYWORD_{1}_IS_{2} (1)
// The following macro must expand to nothing.
#define BOOST_CONTRACT_EXT_PP_KEYWORD_{1}_REM_{2}

// PUBLIC //

#define BOOST_CONTRACT_EXT_PP_KEYWORD_IS_{1}(tokens) \\
    BOOST_CONTRACT_EXT_PP_KEYWORD_UTILITY_IS(tokens, \\
            BOOST_CONTRACT_EXT_PP_KEYWORD_{1}_IS_)

#define BOOST_CONTRACT_EXT_PP_KEYWORD_{1}_REM(tokens) \\
    BOOST_CONTRACT_EXT_PP_KEYWORD_UTILITY_REM(tokens, \\
            BOOST_CONTRACT_EXT_PP_KEYWORD_{1}_REM_)

#endif // #include guard
        '''.format(script, keyword.upper(), keyword.lower()))

        file.close()
        print "Written:", path

