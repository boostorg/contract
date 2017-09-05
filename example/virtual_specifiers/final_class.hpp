
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef FINCAL_CLASS_HPP_
#define FINCAL_CLASS_HPP_

#include <contract.hpp>

//[final_class
CONTRACT_CLASS(
    class (x) final // A final class.
) {
    CONTRACT_CLASS_INVARIANT( void )
};
//]

#endif // #include guard

