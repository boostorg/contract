
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_AUX_SYMBOL_HPP_
#define CONTRACT_AUX_SYMBOL_HPP_

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/seq/cat.hpp>
#include <boost/preprocessor/seq/transform.hpp>

// PRIVATE //

#define CONTRACT_AUX_SYMBOL_POSTFIX_(s, unused, tokens) \
    BOOST_PP_CAT(tokens, CONTRACT_AUX_SYMBOL_INFIX)

// PUBLIC //

// All these macros cannot use `_` because if (user) symbols have leading or
// trailing `_`, cat symbol might have double `__` which is reserved by C++.
#define CONTRACT_AUX_SYMBOL_INFIX X

#define CONTRACT_AUX_SYMBOL(seq) \
    BOOST_PP_SEQ_CAT(BOOST_PP_SEQ_TRANSFORM(CONTRACT_AUX_SYMBOL_POSTFIX_, ~, \
            (contract_aux) seq))

#endif // #include guard

