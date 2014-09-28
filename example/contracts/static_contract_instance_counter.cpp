
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#include <contract.hpp>
#include <boost/detail/lightweight_test.hpp>

//[static_contract_instance_counter
CONTRACT_CLASS(
    template( typename T )
    class (instance_counter)
) {
    CONTRACT_CLASS_INVARIANT_TPL(
        object(), // Non-static class invariants.
        static class( // Static class invariants.
            count() >= 0
            // ...
        )
    )

    CONTRACT_CONSTRUCTOR_TPL(
        public explicit (instance_counter) ( (T*) the_object )
            precondition( the_object )
            postcondition(
                auto old_count = CONTRACT_OLDOF count(),
                count() == old_count + 1,
                object() == the_object
            )
            initialize( object_(the_object) )
    ) {
        count_++;
    }

    CONTRACT_DESTRUCTOR_TPL(
        public virtual (~instance_counter) ( void )
            // FUTURE: Destructors could have static postconditions.
            // postcondition: count() = oldof count() - 1
    ) {
        delete object_;
        count_--;
    }

    CONTRACT_FUNCTION_TPL(
        public (T const* const) (object) ( void ) const
    ) {
        return object_;
    }

    CONTRACT_FUNCTION_TPL( // Contract static member function.
        public static int (count) ( void )
            // No preconditions nor postconditions for this example but when
            // present no object can be accessed by assertions (i.e., `static`).
    ) {
        return count_;
    }

    private: static int count_;
    private: T* object_;
};

template< typename T >
int instance_counter<T>::count_ = 0;
//]

int main ( void )
{
    instance_counter<int> i(new int(123)), j(new int(456));
    BOOST_TEST(i.count() == 2);
    BOOST_TEST(j.count() == 2);
    BOOST_TEST(*(i.object()) == 123);
    BOOST_TEST(*(j.object()) == 456);
    return boost::report_errors();
}

