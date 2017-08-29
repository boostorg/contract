
// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#ifndef CONTRACT_AUX_DEBUG_HPP_
#define CONTRACT_AUX_DEBUG_HPP_

#include "../config.hpp"

// IMPORTANT: In order to remove *any* logging overhead when debug
// is turned off, *all* code used to generate the debug message must
// be passed as the 'code' param of the macro below (because that
// code is executed by the macro expansion only when debug is on).

#if CONTRACT_CONFIG_DEBUG_
#   include <iostream>
#   include <sstream>
#   include <typeinfo>

#   define CONTRACT_AUX_DEBUG(code) \
        { \
            std::ostringstream dbg; \
            { code; } \
            std::clog << dbg.str() << " at " << __FILE__ << ":" \
                    << __LINE__ << std::endl; \
        }

#   define CONTRACT_AUX_DEBUGT(type, code) \
        CONTRACT_AUX_DEBUG(dbg << typeid(type).name() << ": "; code)

#else
#   define CONTRACT_AUX_DEBUG(code) /* expand to nothing */
#   define CONTRACT_AUX_DEBUGT(type, code) /* expand to nothing */
#endif // debug

#endif // #include guard

