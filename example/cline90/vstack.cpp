
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

//[cline90_vstack
// File: vstack.cpp
#include "vector.hpp"
#include <contract.hpp>
#include <boost/detail/lightweight_test.hpp>

CONTRACT_CLASS( // Stack Abstract Data Type (ADT).
    template( typename T )
    class (stack_adt)
) {
    // NOTE: Incomplete set of assertions addressing only empty/full issues.

    CONTRACT_CLASS_INVARIANT_TPL( void ) // no invariants

    CONTRACT_CONSTRUCTOR_TPL(
        public (stack_adt) ( void )
            // postcondition:
            //  empty (cannot be checked because empty's postcondition uses
            //  length which is pure virtual during construction)
    ) {}

    CONTRACT_DESTRUCTOR_TPL(
        public (~stack_adt) ( void )
    ) {}

    CONTRACT_FUNCTION_TPL(
        public bool (full) ( void ) const
            postcondition(
                auto result = return,
                result == (length() == capacity())
            )
    ) {
        return length() == capacity();
    }

    CONTRACT_FUNCTION_TPL(
        public bool (empty) ( void ) const
            postcondition( auto result = return, result == (length() == 0) )
    ) {
        return length() == 0;
    }

    CONTRACT_FUNCTION_TPL(
        public virtual int (length) ( void ) const
            postcondition( auto result = return, result >= 0 )
    ) = 0;

    CONTRACT_FUNCTION_TPL(
        public virtual int (capacity) ( void ) const
            postcondition( auto result = return, result >= 0 )
    ) = 0;

    CONTRACT_FUNCTION_TPL(
        public virtual void (push) ( (T) value )
            precondition( not full() )
            postcondition( not empty() )
    ) = 0; // Contract for pure virtual function.

    CONTRACT_FUNCTION_TPL(
        public virtual (T) (pop) ( void )
            precondition( not empty() )
            postcondition( not full() )
    ) = 0;

    CONTRACT_FUNCTION_TPL(
        public virtual void (clear) ( void )
            postcondition( empty() )
    ) = 0;
};

CONTRACT_CLASS( // Vector-based stack.
    template( typename T )
    class (vstack) extends( public stack_adt<T> )
) {
    CONTRACT_CLASS_INVARIANT_TPL(
        length() >= 0,
        length() < capacity()
    )

    CONTRACT_CONSTRUCTOR_TPL(
        public explicit (vstack) ( int count, default 10 )
            precondition( count >= 0 )
            postcondition( length() == 0, capacity() == count )
            initialize( vect_(count), length_(0) ) // OK, after preconditions.
    ) {}

    CONTRACT_DESTRUCTOR_TPL(
        public virtual (~vstack) ( void )
    ) {}

    // NOTE: All following inherit contracts from `stack_adt`.

    CONTRACT_FUNCTION_TPL(
        public int (length) ( void ) const override final
    ) {
        return length_;
    }

    CONTRACT_FUNCTION_TPL(
        public int (capacity) ( void ) const
    ) {
        return vect_.size();
    }

    CONTRACT_FUNCTION_TPL(
        public void (push) ( (T) value ) override final
    ) {
        vect_[length_++] = value;
    }

    CONTRACT_FUNCTION_TPL(
        public (T) (pop) ( void ) override final
    ) {
        return vect_[--length_];
    }

    CONTRACT_FUNCTION_TPL(
        public void (clear) ( void ) override final
    ) {
        length_ = 0;
    }

    private: vector<T> vect_;
    private: int length_;
};

int main ( void )
{
    vstack<int> s(3);
    BOOST_TEST(s.capacity() == 3);
    s.push(123);
    BOOST_TEST(s.length() == 1);
    BOOST_TEST(s.pop() == 123);
    return boost::report_errors();
}
//]

