
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#include <contract.hpp>
#include <boost/concept_check.hpp>
#include <boost/detail/lightweight_test.hpp>

//[friend_counter
CONTRACT_CLASS( // Not even necessary to contract this class.
    template( typename T ) requires( boost::CopyConstructible<T> )
    class (counter)
) {
    CONTRACT_CLASS_INVARIANT_TPL( value() >= 0 );

    CONTRACT_FUNCTION_TPL( // Friend (contracted declaration and definition).
        public friend (counter) operator(/)(div) ( (counter const&) left,
                (T const&) right )
            precondition( right > 0 ) // Strictly positive, cannot be zero.
            postcondition(
                auto result = return,
                result.value() * right == left.value()
            )
    ) {
        return counter(left.value() / right);
    }
    
    // Friend forward declaration (contracted declaration and definition below).
    public: template< typename U >
    friend bool CONTRACT_FREE_BODY(operator(==)(equal)) ( // Use BODY.
            counter<U> const& left, U const& right ) ;

// NOTE: Forward friend template instantiations give internal MSVC error.
#if defined(BOOST_MSVC) && !defined(CONTRACT_CONFIG_NO_POSTCONDITIONS)
    // Friend definition (contracted declaration below).
    public: friend counter CONTRACT_FREE_BODY(operator(*)(mult)) ( // Use BODY.
            counter const& left, T const& right )
    {
        return counter(left.value() * right); // Contract checked `right >=0` .
    }
#endif
    
    CONTRACT_CONSTRUCTOR_TPL( // Public constructor gets next counter value.
        public explicit (counter) ( void )
            initialize( value_(next_value_++) )
    ) {}
    
    CONTRACT_CONSTRUCTOR_TPL( // Private constructor.
        private explicit (counter) ( (T const&) a_value )
            precondition( a_value >= 0 )
            postcondition( value() == a_value )
            initialize( value_(a_value) )
    ) {}

    CONTRACT_FUNCTION_TPL(
        public (T) (value) ( void ) const
            postcondition( auto result = return,  result >= 0 )
    ) {
        return value_;
    }

    private: T value_;
    private: static T next_value_;
};

template<typename T>
T counter<T>::next_value_ = T();

CONTRACT_FUNCTION(
    template( typename U )
    bool operator(==)(equal) ( (counter<U> const&) left, (U const&) right )
        precondition( right >= 0 )
        postcondition(
            auto result = return,
            result == (left.value() == right)
        )
) {
    return left.value() == right;
}

#if defined(BOOST_MSVC) && !defined(CONTRACT_CONFIG_NO_POSTCONDITIONS)
CONTRACT_FUNCTION(
    (counter<int>) operator(*)(mult) ( (counter<int> const&) left,
            (int const&) right )
        precondition( right >= 0 )
        postcondition(
            auto result = return,
            result.value() == left.value() * right
        )
) ;
#endif
//]

int main ( void )
{
    counter<int> i0, i1, i2, i3, i4;
    BOOST_TEST(i4 / 2 == 2);
#if defined(BOOST_MSVC) && !defined(CONTRACT_CONFIG_NO_POSTCONDITIONS)
    BOOST_TEST(i3 * 2 == 6);
#endif
    return boost::report_errors();
}

