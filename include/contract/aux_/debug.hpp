
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_AUX_DEBUG_HPP_
#define CONTRACT_AUX_DEBUG_HPP_

#include <contract/aux_/config.hpp>

#if CONTRACT_AUX_CONFIG_DEBUG_01

#include <boost/preprocessor/stringize.hpp>
#include <typeinfo>
#include <sstream>
#include <iostream>

// IMPORTANT: In order to remove *any* logging overhead when debug
// is turned off, *all* code used to generate the debug message must
// be passed as the 'code' param of the macro below (because that
// code is executed by the macro expansion only when debug is on).
#define CONTRACT_AUX_DEBUG(file, line, code) \
    { \
        std::ostringstream dbg; /* decl special stream named `dbg` */ \
        { code; } /* code shall set dbg stream */ \
        std::clog << file << ":" << line << " " << dbg.str() << std::endl; \
    }

#define CONTRACT_AUX_DEBUGN(file, line, name, code) \
    CONTRACT_AUX_DEBUG(file, line, \
        dbg << "[" << BOOST_PP_STRINGIZE(name) << "] "; \
        code; \
    )

#define CONTRACT_AUX_DEBUGT(file, line, type, code) \
    CONTRACT_AUX_DEBUG(file, line, \
        dbg << "[" << typeid(type).name() << "] "; \
        code; \
    )

#else // debug

#define CONTRACT_AUX_DEBUG(file, line, code) /* nothing */
#define CONTRACT_AUX_DEBUGN(file, line, name, code) /* nothing */
#define CONTRACT_AUX_DEBUGT(file, line, type, code) /* nothing */

#endif // debug

#endif // #include guard

