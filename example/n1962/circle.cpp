
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

//[n1962_circle
// File: circle.cpp
#include <contract.hpp>
#include <boost/detail/lightweight_test.hpp>

CONTRACT_CLASS(
    class (shape)
) {
    CONTRACT_CLASS_INVARIANT( void ) // Must always specify class invariants.

    CONTRACT_DESTRUCTOR(
        public virtual (~shape) ( void )
    ) {}

    CONTRACT_FUNCTION(
        public virtual int (compute_area) ( void ) const
            // No base preconditions so all derived preconditions true.
            postcondition( auto result = return, result > 0 )
    ) = 0; // Contract for pure virtual function.
};

CONTRACT_CLASS(
    class (circle) extends( public shape ) // Subcontract from base `shape`.
) {
    CONTRACT_CLASS_INVARIANT( void ) // In AND with base class invariants.

    public: int radius() const { return 2; }

    CONTRACT_FUNCTION( // Also using `override` specifier (optional).
        public virtual int (compute_area) ( void ) const override
            // Eventual preconditions in OR with base function preconditions.
            postcondition( // In AND with base function postconditions.
                auto result = return,
                result == pi * radius() * radius()
            )
    ) {
        return pi * radius() * radius();
    }

    private: static const int pi = 3; // Truncated from 3.14...
};

int main ( void )
{
    circle c;
    BOOST_TEST(c.compute_area() == 12);
    return boost::report_errors();
}
//]

