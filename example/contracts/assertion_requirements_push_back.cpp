
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#include <contract.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <vector>

//[assertion_requirements_push_back
#include <boost/type_traits/has_equal_to.hpp>

CONTRACT_CLASS(
    template( typename T )
    class (vector)
) {
    CONTRACT_CLASS_INVARIANT_TPL(
        size() <= capacity(),
        capacity() <= max_size()
        // ...
    )

    CONTRACT_FUNCTION_TPL(
        public void (push_back) ( (T const&) value )
            precondition( size() < max_size() )
            postcondition(
                auto old_size = CONTRACT_OLDOF size(),
                auto old_capacity = CONTRACT_OLDOF capacity(),
                size() == old_size + 1,
                capacity() >= old_capacity,
                // Requirements disable assertion if `T` has no `operator==`.
                back() == value, requires boost::has_equal_to<T>::value
            )
    ) {
        vector_.push_back(value);
    }

    // ...
//]

    public: typedef typename std::vector<T>::size_type size_type;
    public: typedef typename std::vector<T>::const_reference const_reference;
    
    public: size_type size ( void ) const { return vector_.size(); } 
    public: size_type max_size ( void ) const { return vector_.max_size(); } 
    public: size_type capacity ( void ) const { return vector_.capacity(); } 
    public: const_reference back ( void ) const { return vector_.back(); } 

    private: std::vector<T> vector_;
};

//[assertion_requirements_push_back_call
struct num // Not equality comparable.
{
    int value;
    explicit num ( int a_value ) : value(a_value) {}
};

int main ( void )
{
    vector<int> i;
    i.push_back(123);

    vector<num> n;
    n.push_back(num(123));
    BOOST_TEST(not boost::has_equal_to<num>::value);

    // ...
//]
    
    BOOST_TEST(i.size() == 1);
    BOOST_TEST(n.size() == 1);
    return boost::report_errors();
}

