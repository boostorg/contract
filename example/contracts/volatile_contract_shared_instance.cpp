
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#include <contract.hpp>
#include <boost/detail/lightweight_test.hpp>

//[volatile_contract_shared_instance
CONTRACT_CLASS(
    template( typename T )
    class (shared_instance)
) {
    CONTRACT_CLASS_INVARIANT_TPL(
        queries() >= 0, // Non-volatile class invariants.
        volatile class( // Volatile class invariants.
            object()
            // ...
        )
    )

    CONTRACT_CONSTRUCTOR_TPL(
        public explicit (shared_instance) ( (T*) the_object )
            precondition( the_object )
            postcondition( object() == the_object )
            initialize( object_(the_object), queries_(0) )
    ) {}

    CONTRACT_DESTRUCTOR_TPL(
        public virtual (~shared_instance) ( void )
    ) {
        delete object_;
    }

    CONTRACT_FUNCTION_TPL( // Contracts for volatile member function.
        public (T const volatile* const) (object) ( void ) const volatile
            // No preconditions nor postconditions for this example but when
            // present object is `const volatile` within assertions.
    ) {
        queries_++;
        return object_;
    }

    CONTRACT_FUNCTION_TPL(
        public int (queries) ( void ) const
    ) {
        return queries_;
    }

    private: T volatile* object_;
    private: mutable int queries_;
};
//]

int main ( void )
{
    shared_instance<int> volatile i(new int(123));
    BOOST_TEST(*(i.object()) == 123);
    return boost::report_errors();
}

