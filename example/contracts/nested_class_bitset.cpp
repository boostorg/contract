
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#include <contract.hpp>
#include <boost/concept_check.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/detail/lightweight_test.hpp>

//[nested_class_bitset
CONTRACT_CLASS( // Enclosing class.
    template( size_t N )
    class (bitset)
) {
    CONTRACT_CLASS_INVARIANT_TPL(
        static class( size() == N )
    )

    CONTRACT_CLASS_TPL( // Nested class.
        public class (reference)
    ) {
        CONTRACT_CLASS_INVARIANT_TPL( bitptr_ )

        friend class bitset;

        CONTRACT_CLASS_TPL( // Nested (twice) class template with concepts.
            private template( typename T )
                requires( boost::DefaultConstructible<T> )
            class (bit)
        ) {
            CONTRACT_CLASS_INVARIANT_TPL( void )

            CONTRACT_CONSTRUCTOR_TPL(
                public (bit) ( void )
                    initialize( value_() )
            ) {}

            CONTRACT_FUNCTION_TPL(
                public void (from_bool) ( bool value )
                    postcondition( to_bool() == value )
            ) {
                value_ = value;
            }
            
            CONTRACT_FUNCTION_TPL(
                public bool (to_bool) ( void ) const
            ) {
                return value_;
            }
            
            private: T value_;
        };

        CONTRACT_CONSTRUCTOR_TPL(
            private (reference) ( void )
                postcondition( bitptr_->to_bool() == int() )
                initialize(
                    bitptr_(boost::shared_ptr<bit<int> >(new bit<int>()))
                )
        ) {}
        
        CONTRACT_DESTRUCTOR_TPL(
            public (~reference) ( void )
        ) {}
        
        CONTRACT_FUNCTION_TPL(
            public operator bool ( void ) const
        ) {
            return bitptr_->to_bool();
        }
        
        CONTRACT_FUNCTION_TPL(
            public (reference&) operator(=)(assign) ( bool const bit_value )
                postcondition( auto result = return, result == *this )
        ) { 
            bitptr_->from_bool(bit_value);
            return *this;
        }
        
        private: boost::shared_ptr<bit<int> > bitptr_;
    };

    CONTRACT_FUNCTION_TPL(
        public (reference) operator([])(at) ( size_t index )
            precondition( index < N )
    ) {
        return bitset_[index];
    }
    
    CONTRACT_FUNCTION_TPL(
        public static size_t (size) ( void )
    ) {
        return N;
    }

    private: reference bitset_[N];
};
//]

int main ( void )
{
    bitset<2> b;
    b[0] = true;
    BOOST_TEST(b[0]);
    b[1] = false;
    BOOST_TEST(not b[1]);
    return boost::report_errors();
}

