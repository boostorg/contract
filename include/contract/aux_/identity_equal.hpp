
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef CONTRACT_AUX_IDENTITY_EQUAL_HPP_
#define CONTRACT_AUX_IDENTITY_EQUAL_HPP_

namespace contract { namespace aux {

// Used to internally deal with old-of value assignment symbol `var =`.
struct identity_equal {};

template< typename Left >
Left const& operator== ( Left const& left, identity_equal const& ) {
    return left;
}

} } // namespace

#endif // #include guard

