
// Copyright (C) 2008-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://sourceforge.net/projects/contractpp

#include <contract.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <boost/algorithm/cxx11/all_of.hpp>
#include <iterator>
#include <vector>

//[class_template_vector
#include "pushable.hpp"

CONTRACT_CLASS(
    template( typename T )
    class (vector) extends( public pushable<T> ) // Subcontract.
) {
    // Within templates, use contract macros postfixed by `_TPL`.

    CONTRACT_CLASS_INVARIANT_TPL(
        empty() == (size() == 0),
        size() <= capacity(),
        capacity() <= max_size(),
        std::distance(begin(), end()) == int(size())
    )

    public: typedef typename std::vector<T>::size_type size_type;
    public: typedef typename std::vector<T>::const_reference const_reference;
    public: typedef typename std::vector<T>::const_iterator const_iterator;

    CONTRACT_CONSTRUCTOR_TPL(
        public explicit (vector) ( (size_type) count )
            precondition( count >= 0 )
            postcondition(
                size() == count,
                boost::algorithm::all_of_equal(begin(), end(), T())
            )
            initialize( vector_(count) )
    ) {}

    CONTRACT_DESTRUCTOR_TPL(
        public virtual (~vector) ( void )
    ) {}

    CONTRACT_FUNCTION_TPL(
        public void (push_back) ( (T const&) value )
            precondition( size() < max_size() )
            postcondition(
                auto old_size = CONTRACT_OLDOF size(),
                auto old_capacity = CONTRACT_OLDOF capacity(),
                size() == old_size + 1,
                capacity() >= old_capacity
                // Overridden postconditions also check `back() == value`.
            )
    ) {
        vector_.push_back(value);
    }

    // ...
//]
    
    public: bool empty ( void ) const { return vector_.empty(); }
    public: size_type size ( void ) const { return vector_.size(); }
    public: size_type max_size ( void ) const { return vector_.max_size(); }
    public: size_type capacity ( void ) const { return vector_.capacity(); }
    public: const_reference back ( void ) const { return vector_.back(); }
    public: const_iterator begin ( void ) const { return vector_.begin(); }
    public: const_iterator end ( void ) const { return vector_.end(); }

    private: std::vector<T> vector_;
};

int main ( void )
{
    vector<int> v(1);
    BOOST_TEST(v.size() == 1);
    BOOST_TEST(v.back() == 0);
    
    v.push_back(123);
    BOOST_TEST(v.size() == 2);
    BOOST_TEST(v.back() == 123);

    return boost::report_errors();
}

