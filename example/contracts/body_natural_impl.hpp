
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#include "body_natural.hpp"

//[body_natural_impl
// Deferred body definitions, separated from their declarations and contracts.

template< typename T >
bool CONTRACT_FREE_BODY(greater) (
        natural<T> const& left, natural<T> const& right )
{
    return left.get() > right.get();
}

template< typename T, T Default >
CONTRACT_CONSTRUCTOR_BODY((natural<T, Default>), natural) ( T const& value )
{
    value_ = value;
}

template< typename T, T Default >
CONTRACT_DESTRUCTOR_BODY((natural<T, Default>), ~natural) ( void )
{
    // Do nothing.
}

template< typename T, T Default >
bool natural<T, Default>::CONTRACT_MEMBER_BODY(equal) ( natural const& right )
        const
{
    return not less(*this, right) && not greater(*this, right);
}
//]

