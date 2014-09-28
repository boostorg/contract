
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#ifndef BODY_NATURAL_HPP_
#define BODY_NATURAL_HPP_

#include <contract.hpp>

//[body_natural
template< typename T, T Default = T() > // Class forward declaration.
class natural ;

template< typename T > // Function forward declaration.
bool less ( natural<T> const& left, natural<T> const& right ) ;

CONTRACT_FUNCTION(
    template( typename T )
    bool (greater) ( (natural<T> const&) left, (natural<T> const&) right )
        postcondition(
            auto result = return,
            result ? not less(left, right) : true
        )
) ; // Deferred free function body definition, use `;`.

CONTRACT_CLASS( // Class declaration (with contracts).
    template( typename T, (T) Default )
    class (natural)
) {
    CONTRACT_CLASS_INVARIANT_TPL( get() >= 0 )

    CONTRACT_CONSTRUCTOR_TPL(
        public explicit (natural) ( (T const&) value, default Default )
            precondition( value >= 0 )
            postcondition( get() == value )
            // Unfortunately, no member initializers when body deferred.
    ) ; // Deferred constructor body definition, use `;`.

    CONTRACT_DESTRUCTOR_TPL(
        public (~natural) ( void )
    ) ; // Deferred destructor body definition, use `;`.

    CONTRACT_FUNCTION_TPL(
        public bool (equal) ( (natural const&) right ) const
            postcondition(
                auto result = return,
                result == not less(*this, right) && not greater(*this, right)
            )
    ) ; // Deferred member function body definition, use `;`.

    CONTRACT_FUNCTION_TPL(
        public (T) (get) ( void ) const
    ) {
        return value_;
    }

    private: T value_;
};

CONTRACT_FUNCTION( // Function declaration (with contracts).
    template( typename T )
    bool (less) ( (natural<T> const&) left, (natural<T> const&) right )
        postcondition(
            auto result = return,
            result ? not greater(left, right) : true
        )
) {
    return left.get() < right.get();
}
//]

#include "body_natural_impl.hpp"

#endif // #include guard

