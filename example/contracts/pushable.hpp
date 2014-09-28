
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef PUSHABLE_HPP_
#define PUSHABLE_HPP_

#include <contract.hpp>
#include <boost/type_traits/has_equal_to.hpp>
#include <vector>

//[pushable
CONTRACT_CLASS(
    template( typename T )
    class (pushable)
) {
    // Subcontracting: In `and` with derived class invariants.
    CONTRACT_CLASS_INVARIANT_TPL( void )

    public: typedef typename std::vector<T>::const_reference const_reference;

    CONTRACT_FUNCTION_TPL(
        public virtual void (push_back) ( (T const&) value ) new
            // Subcontracting: In `or` with overriding function preconditions.
            precondition( false ) // Force check to overriding preconditions.
            // Subcontracting: In `and` with overriding function postconditions.
            postcondition(
                back() == value, requires boost::has_equal_to<T>::value
            )
    ) = 0; // Contract for pure virtual function.

    public: virtual const_reference back ( void ) const = 0;
};
//]

#endif // #include guard

