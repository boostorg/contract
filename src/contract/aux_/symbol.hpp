// Copyright (C) 2009-2010 Lorenzo Caminiti.
// Use, modification, and distribution is subject to the
// Contract++ Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt.)

#ifndef CONTRACT_AUX_PP_SYMBOL_HPP_
#define CONTRACT_AUX_PP_SYMBOL_HPP_

#include <boost/preprocessor.hpp>

// Prefixes contract_ for library specific name.
#define CONTRACT_AUX_SYMBOL(name) BOOST_PP_CAT(contract_, name)

// Prefixes contract_ and postfixes _ for library internal name.
#define CONTRACT_AUX_INTERNAL_SYMBOL(name) \
    BOOST_PP_CAT(CONTRACT_AUX_SYMBOL(name), _)

#endif // #include guard

