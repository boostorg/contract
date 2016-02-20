
#ifndef BOOST_CONTRACT_AUX_CONFIG_HPP_
#define BOOST_CONTRACT_AUX_CONFIG_HPP_

// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

// Turn off assert(...) in lib's implementation.
// BOOST_CONTRACT_AUX_CONFIG_NDEBUG

// Export symbols when compiling as shared lib (for internal use only).
// BOOST_CONTRACT_AUX_CONFIG_SOURCE

#ifndef BOOST_CONTRACT_AUX_CONFIG_NAME_PREFIX
    #define BOOST_CONTRACT_AUX_CONFIG_NAME_PREFIX boost_contract_auxX
#endif

#endif // #include guard

